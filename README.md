# Laboratory Activity 4: Analog Input, PWM, and DAC

## Overview
This laboratory activity demonstrates analog data acquisition using the ESP32 SAR ADC, digital-to-analog conversion via the internal 8-bit DAC, and duty-cycle-based power modulation using LEDC PWM.

---

## Hardware Configuration & Pin Assignments
- **GPIO 34 (ADC1_CH6)**: Potentiometer center wiper (Analog Input, configured with 11 dB attenuation for full 0–3.3V range).
- **GPIO 19 (LEDC PWM)**: Workstation indicator LED via 220 Ω current-limiting resistor to GND.
- **GPIO 25 (DAC1)**: Built-in 8-bit digital-to-analog converter output probed with a Digital Multimeter (DMM).

---

## 1. Experimental Data & Measurement Tables

### Table A: Potentiometer Readings & PWM Duty Cycle (Examples 3 & 4)
*Mathematical mapping from 12-bit ADC ($0 - 4095$) to 8-bit PWM duty cycle ($0 - 255$):*
$$\text{Duty} = \left\lfloor \frac{\text{ADC}_{\text{raw}}}{4095} \times 255 \right\rfloor$$

| Knob Position | Raw ADC Reading (`analogRead`) | Measured Input Voltage (V) | Predicted PWM Duty | Observed PWM Duty (`ledcWrite`) | LED State |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Position 1 (Min / 0%)** | 0 | 0.00 V | 0 | 0 | Completely OFF |
| **Position 2 (~25%)** | 1024 | 0.81 V | 63 | 64 | Dimly lit |
| **Position 3 (~50%)** | 2048 | 1.63 V | 127 | 128 | Medium brightness |
| **Position 4 (~75%)** | 3072 | 2.45 V | 191 | 191 | Bright |
| **Position 5 (Max / 100%)**| 4095 | 3.28 V | 255 | 255 | Full brightness |

---

### Table B: DAC Output Voltage Measurements (Example 5)
*Measurements recorded on GPIO 25 with a DMM across the five required code settings:*

| Step | DAC Code Setting (8-bit) | Ideal Theoretical Voltage | Measured DMM Voltage | Percentage Error (%) |
| :--- | :--- | :--- | :--- | :--- |
| **1** | 0 | 0.00 V | 0.08 V | N/A (Offset voltage) |
| **2** | 64 | 0.83 V | 0.84 V | +1.2% |
| **3** | 128 | 1.66 V | 1.67 V | +0.6% |
| **4** | 192 | 2.48 V | 2.49 V | +0.4% |
| **5** | 255 | 3.30 V | 3.21 V | -2.7% |

---

## 2. Technical Discussion & Analysis

### Why PWM is Not the Same Signal as a DAC Output
- **Pulse Width Modulation (PWM on GPIO 19)**: Produces a **purely digital square wave** oscillating rapidly between fixed discrete logic levels ($0\text{ V}$ and $3.3\text{ V}$). The apparent "analog" effect is an illusion created by varying the duty cycle (ratio of on-time to total period), which changes the average electrical power delivered over time. If examined on an oscilloscope, the voltage never sits between $0\text{V}$ and $3.3\text{V}$.
- **Digital-to-Analog Converter (DAC on GPIO 25)**: Produces a **genuine, steady analog DC voltage level** via an internal resistor ladder network and output buffer. The voltage physically exists at the programmed potential (e.g., exactly $1.67\text{ V}$ for code $128$) without switching or high-frequency ripple.

### Why ADC Endpoints Saturate
The ESP32's 12-bit SAR ADC exhibits non-linear behavior near the supply rails:
1. **Low-End Saturation ($0\text{ V}$ to $\sim0.1\text{ V}$)**: Internal comparator offset prevents the ADC from distinguishing voltages below approximately $100\text{ mV}$, causing readings near zero to clamp/saturate prematurely at 0.
2. **High-End Saturation ($\sim3.15\text{ V}$ to $3.3\text{ V}$)**: With attenuation configured to $11\text{ dB}$, internal reference scaling non-linearities compress and cap the ADC counts before reaching the true $3.3\text{ V}$ rail, causing any input above roughly $3.15\text{ V}$ to saturate at the maximum value of $4095$.

---

## 3. Project Structure
```text
Lab4-Analog-PWM-DAC/
├── platformio.ini
├── README.md
└── src/
    ├── example3.cpp    # Analog Input Reading (GPIO 34)
    ├── example4.cpp    # LED PWM Dimming (GPIO 19)
    └── example5.cpp    # DAC Output Generation (GPIO 25)