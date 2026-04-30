# ESP32 DC Motor Controller (BTS7960)

DC motor control system using **ESP32 + BTS7960 motor driver** with dual digital inputs.

This project demonstrates a simple multi-speed motor controller using PWM and state-based input reading.

---

## 🚀 Features

- BTS7960 high-current motor driver control
- Dual digital input control (2 switches / ignition lines)
- PWM speed control (low / high)
- Change-detection input reading (software debounce style)
- Clean OOP Arduino structure
- Serial status monitoring

---

## 🧠 System Overview

Input Switches → ESP32 → BTS7960 → DC Motor

The ESP32 reads two digital inputs and determines the motor speed using PWM.

---

## 🔧 Hardware Used

| Component | Description |
|---|---|
| ESP32 | Main microcontroller |
| BTS7960 | High current motor driver |
| DC Motor 555 | 12V brushed DC motor |
| Step-down module (MP1584 / MP1548) | 12V → 5V converter |
| 2x Switch / Ignition Lines | Digital input control |
| 12V Power Supply | Motor power source |

---

## ⚡ Power Architecture

12V Supply powers:
- DC Motor directly via BTS7960
- Step-down module → 5V → ESP32 VIN

⚠️ **Do NOT power ESP32 directly from 12V**

---

## 🔌 Wiring

### BTS7960 → ESP32

| BTS7960 | ESP32 |
|---|---|
| RPWM | GPIO 25 |
| LPWM | GPIO 33 |
| VCC | 5V |
| GND | GND |

### Input Switches → ESP32

| Input | ESP32 |
|---|---|
| Blue Line | GPIO 14 |
| Yellow Line | GPIO 26 |
| Other side | GND |

Pins use **INPUT_PULLUP** configuration.

---

## 🎮 Control Logic

| Blue | Yellow | Motor State |
|---|---|---|
| OFF | OFF | Motor OFF |
| ON | OFF | Low Speed |
| ON | ON | High Speed |

---

## 🧪 Serial Output Example
```text
Motor OFF
Motor LOW SPEED
Motor HIGH SPEED
```


---

## ▶️ How to Use

1. Open project in Arduino IDE / PlatformIO  
2. Select ESP32 board  
3. Upload the sketch  
4. Open Serial Monitor (115200 baud)  
5. Toggle input switches to control motor speed

---

## 📚 Learning Goals

This project demonstrates:
- PWM motor control on ESP32
- Digital input change detection
- Basic embedded OOP design
- Safe power distribution for motors

---

## 📄 License

MIT License