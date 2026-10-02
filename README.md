<<<<<<< HEAD
# Laboratory-Activity-3-GPIO-and-Button-Control
=======
# Laboratory Activity 5: Structured Workstation Light

An embedded firmware implementation on the ESP32 demonstrating a structured Read-Process-Write architecture to control a variable-brightness workstation light and status indicator using analog and digital inputs.

---

## Overview

This project implements an active workstation lighting system using an ESP32 microcontroller:
- **Momentary Safety Switch (Pushbutton):** Acts as an enable switch. Both outputs remain OFF when released.
- **Potentiometer Control:** When the system is enabled, the potentiometer controls the brightness of the workstation light via Pulse Width Modulation (PWM).
- **Status Indicator LED:** Provides immediate digital feedback showing whether the workstation light output is enabled or disabled.

The firmware follows a clean, single-pass **Read $\rightarrow$ Process $\rightarrow$ Write** execution pipeline inside the main loop, paced at 20 ms intervals.

---

## Hardware Specifications & Pin Configuration

| Component | ESP32 GPIO | Description / Mode |
| :--- | :--- | :--- |
| **Pushbutton** | GPIO 4 | Active-LOW input configured with internal pull-up (`INPUT_PULLUP`) |
| **Potentiometer** | GPIO 34 | Analog input (ADC1 Channel 6) reading 12-bit ADC values (0–4095) |
| **Status LED** | GPIO 2 | Discrete digital output indicator |
| **Dimming PWM LED** | GPIO 18 | PWM output running at 5 kHz, 8-bit resolution (0–255) |

> **Note:** The potentiometer supply leg must be tied to **3V3** (not 5V/VIN) to protect the ESP32 ADC from overvoltage.

---

## Software Architecture

The firmware separates input acquisition, state evaluation, and output application into dedicated functions:

1. **`readInputs()`**: Reads raw values from the momentary button (`digitalRead`) and potentiometer (`analogRead`).
2. **`processInputs()`**: Applies system logic. If enabled, it maps the 12-bit ADC reading (0–4095) to an 8-bit PWM duty cycle (0–255) and sets the status flag to active; if disabled, all outputs are set to zero/inactive.
3. **`updateOutputs()`**: Drives the hardware by updating the digital status LED state and writing the computed duty cycle to the PWM channel via `ledcWrite`.

---

## Circuit Schematic / Wiring Guide

- **Button:** One terminal to **GPIO 4**, opposite terminal to **GND**.
- **Potentiometer:** Outer terminal 1 to **3V3**, wiper (center) to **GPIO 34**, outer terminal 2 to **GND**.
- **Status LED:** Anode to **GPIO 2** through a 220Ω–330Ω resistor, cathode to **GND**.
- **PWM LED:** Anode to **GPIO 18** through a 220Ω–330Ω resistor, cathode to **GND**.

---

## Build & Upload Instructions (PlatformIO)

1. Clone this repository:
   ```bash
   git clone [https://github.com/GM-Mejos/Laboratory-Activity-5-Structured-Workstation-Light.git](https://github.com/GM-Mejos/Laboratory-Activity-5-Structured-Workstation-Light.git)
>>>>>>> effe9185cdaeaa71aca283fea64f265de9b76cd8
