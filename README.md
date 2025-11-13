# 🚗 Smart Parking System — Arduino Project

A simple **IoT-based Smart Parking prototype** using **Arduino UNO**, **ultrasonic sensor**, **servo motor**, **LCD display**, **LED indicators**, and **buzzer**.  
This project simulates an **automated parking barrier system** that detects vehicles, opens/closes the gate automatically, and provides real-time feedback.

---

## 🧠 Project Overview

This project demonstrates how a **Smart Parking barrier** works by integrating sensors and actuators.  
When a vehicle is detected by the ultrasonic sensor, the system:
- Opens the barrier using a servo motor  
- Activates LEDs to indicate status  
- Displays messages on the LCD screen  
- Beeps using a buzzer during opening and closing  

It represents the core logic behind a **Smart Parking Management System**.

---

## ⚙️ Components Used

| Component | Quantity | Function |
|------------|-----------|-----------|
| Arduino UNO | 1 | Main controller |
| HC-SR04 Ultrasonic Sensor | 1 | Detects vehicle distance |
| Servo Motor (SG90) | 1 | Controls the barrier arm |
| LCD I2C (16x2) | 1 | Displays system status |
| Red LED | 1 | Barrier closed indicator |
| Yellow LED | 1 | Barrier in transition |
| Green LED | 1 | Car can pass indicator |
| Buzzer | 1 | Alerts at barrier opening/closing |
| White LED (optional) | 1 | General parking light |
| Jumper wires | — | Connections |
| Breadboard | 1 | Circuit assembly |

---

## 🧩 Circuit Description

- **Trigger pin (Ultrasonic)** → Arduino **D10**  
- **Echo pin (Ultrasonic)** → Arduino **D9**  
- **Servo motor** → Arduino **D3**  
- **LEDs** → Red (**D4**), Yellow (**D5**), Green (**D6**)  
- **Buzzer** → Arduino **D7**  
- **LCD I2C** → SDA/SCL pins (A4/A5 on UNO)  
- **White LED (optional)** → D11  

---

## 💻 Code Description

### Main Features:
- Reads the distance from the ultrasonic sensor.
- If a car is detected (<30 cm):
  - Opens the barrier (servo 90°)
  - Updates the LCD display
  - Turns LEDs to yellow → green
  - Beeps twice to indicate opening
- If no car is detected:
  - Closes the barrier (servo 0°)
  - Turns LEDs to yellow → red
  - Displays “Barrier Closed”
  - Beeps twice to indicate closing

---

## 🧾 Example Output (LCD)

| Scenario | LCD Line 1 | LCD Line 2 |
|-----------|-------------|-------------|
| No car detected | Barrier Closed | Waiting for Car |
| Car detected | Car Detected! | Opening Barrier |
| Barrier open | Barrier Open | Car Can Pass |
| Closing | No Car Detected | Closing Barrier |

---

## 🔊 Functional Flow

1. The **HC-SR04** sensor measures distance.
2. When distance < 30 cm, the system assumes a **vehicle presence**.
3. The **servo motor** opens the barrier.
4. LEDs and LCD update in real-time.
5. The **buzzer** beeps twice at each action.
6. When the vehicle leaves, the barrier closes automatically.

---

## 🧱 Installation & Usage

1. Open the `.ino` file in **Arduino IDE**.
2. Select your board: **Arduino UNO**.
3. Install the following libraries:
   - `Servo.h`
   - `Wire.h`
   - `LiquidCrystal_I2C.h`
4. Upload the sketch to your Arduino.
5. Observe the barrier behavior and LCD updates.

---

## 🧩 File Structure

