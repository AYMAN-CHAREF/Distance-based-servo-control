// === SMART PARKING SYSTEM ===
// Ce programme contrôle une barrière automatique pour un système de parking intelligent
// Il utilise un capteur ultrasonique pour détecter les voitures, un servo moteur pour la barrière,
// un écran LCD pour afficher l’état, des LEDs pour indiquer les états, et un buzzer pour les alertes sonores.

#include <Servo.h>               // Bibliothèque pour contrôler le servo moteur
#include <Wire.h>                // Nécessaire pour la communication I2C
#include <LiquidCrystal_I2C.h>   // Bibliothèque pour l’écran LCD I2C

// === Initialisation de l’écran LCD ===
// Adresse 0x27 ou 0x3F selon le modèle (16 colonnes x 2 lignes)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// === Déclaration du servo moteur ===
Servo s1;

// === Définition des broches ===
const int trigPin = 10;          // Broche TRIG du capteur ultrason
const int echoPin = 9;           // Broche ECHO du capteur ultrason
const int redLED = 4;            // LED rouge → barrière fermée
const int yellowLED = 5;         // LED jaune → transition / détection
const int greenLED = 6;          // LED verte → barrière ouverte
const int buzzer = 7;            // Buzzer → signal sonore ouverture/fermeture

// === Variables globales ===
long duration;                   // Durée du signal ultrasonique
int distanceCm;                  // Distance mesurée en centimètres

void setup() {
  Serial.begin(9600);            // Démarrage du moniteur série (pour debug)

  // Configuration des broches
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Attacher le servo à la broche 3
  s1.attach(3);

  // Initialisation de l’écran LCD
  lcd.init();
  lcd.backlight();               // Allumer le rétroéclairage

  // === État initial ===
  s1.write(0);                   // Barrière fermée
  digitalWrite(redLED, HIGH);    // LED rouge allumée
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(buzzer, LOW);     // Buzzer éteint

  // Message de démarrage
  lcd.setCursor(0, 0);
  lcd.print("Parking System");
  lcd.setCursor(0, 1);
  lcd.print("Barrier Closed");
  delay(2000);
}

void loop() {
  // === Mesure de la distance ===
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);   // Envoi d’une impulsion ultrasonique
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 20000);  // Lecture du signal réfléchi (timeout 20 ms)
  distanceCm = duration * 0.034 / 2;         // Conversion du temps en distance (cm)

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  // === Si une voiture est détectée (moins de 30 cm) ===
  if (distanceCm > 0 && distanceCm < 30) {
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);   // LED jaune pendant ouverture
    digitalWrite(greenLED, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Car Detected!");
    lcd.setCursor(0, 1);
    lcd.print("Opening Barrier");

    // 🔊 2 bips courts à l’ouverture
    for (int i = 0; i < 2; i++) {
      tone(buzzer, 1000);       // Son de 1000 Hz
      delay(200);
      noTone(buzzer);
      delay(150);
    }

    s1.write(90);                // Ouvrir la barrière (servo à 90°)
    delay(1000);

    // Barrière ouverte
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Barrier Open");
    lcd.setCursor(0, 1);
    lcd.print("Car Can Pass");
  } 
  else {
    // === Aucune voiture → fermer la barrière ===
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Car Detected");
    lcd.setCursor(0, 1);
    lcd.print("Closing Barrier");

    // 🔊 2 bips courts à la fermeture
    for (int i = 0; i < 2; i++) {
      tone(buzzer, 1500);       // Son de 1500 Hz
      delay(200);
      noTone(buzzer);
      delay(150);
    }

    s1.write(0);                 // Fermer la barrière (servo à 0°)
    delay(1000);

    // Barrière fermée
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Barrier Closed");
    lcd.setCursor(0, 1);
    lcd.print("Waiting for Car");
  }

  delay(500); // Petite pause avant la prochaine mesure
}
