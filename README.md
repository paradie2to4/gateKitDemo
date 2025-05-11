# 🚪 Ultrasonic Sensor-Based Automatic Door System

This Arduino project demonstrates an **automatic door mechanism** using an ultrasonic sensor, servo motor, LEDs, and a buzzer. When an object is detected within a specific range, the door opens, lights switch, and a "bump bump" buzzer sound is triggered. If no object is detected after a delay, the door closes.

---

## 🛠️ Components Used
- Arduino board
- Ultrasonic sensor (HC-SR04)
- Servo motor
- Red LED (anode + cathode)
- Blue LED (with cathode)
- Buzzer
- Resistors
- Jumper wires

---

## 🔌 Pin Configuration

| Component           | Arduino Pin |
|---------------------|-------------|
| Ultrasonic Trigger  | 2           |
| Ultrasonic Echo     | 3           |
| Red LED Anode       | 4           |
| Red LED Cathode     | 8           |
| Blue LED Cathode    | 7           |
| Blue LED Pin        | 5           |
| Servo Motor         | 6           |
| Buzzer              | 12          |

---

## ⚙️ Features
- **Distance Detection**: Opens the door if an object is within 20 cm.
- **Servo Motor Control**: Rotates to open (90°) and close (0°).
- **LED Indication**:
  - Red LED ON when door is closed.
  - Blue LED ON when door is open.
- **Buzzer**: Emits a "bump bump" pattern when the door is open.
- **Auto-close**: After 2 seconds if no object is detected.

---

## 🧠 Code Logic Summary

- **Setup**:
  - Initializes all pins.
  - Closes the door and turns on the red LED.

- **Loop**:
  - Measures distance using the ultrasonic sensor.
  - If an object is within range:
    - Opens the door.
    - Turns on blue LED, turns off red LED.
    - Starts buzzer pattern.
  - If no object:
    - Waits 2 seconds.
    - Closes the door, switches back LEDs, and stops buzzer.

---

## 📦 How to Use
1. Connect all components as per the pin configuration.
2. Upload the code to the Arduino.
3. Power the system.
4. Move your hand or object near the ultrasonic sensor to trigger the door.

---

## 📝 Notes
- Adjust `thresholdDistance`, `openAngle`, or `closeDelay` as needed.
- Make sure your servo is powered adequately.
"""
