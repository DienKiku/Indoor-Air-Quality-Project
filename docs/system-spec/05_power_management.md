# 05. Power Management & Battery Subsystem

## 1. Overview

The Indoor Air Quality (IAQ) monitoring station incorporates an autonomous, portable 2S Lithium-Ion power architecture. The system integrates charging, protection, voltage regulation, and active energy telemetry.

---

## 2. Power Architecture & Component Specifications

```
                       [USB Type-C 5V Input]
                                 |
                                 v
          +----------------------------------------------+
          | Type-C to 2S (8.4V, 2A) Boost Charger Module |
          +----------------------+-----------------------+
                                 |
                                 v
          +----------------------------------------------+
          | 2x 18650 Li-ion Cells (2S1P, 2600mAh, 7.4V)  |
          |       Protected by 2S 5A BMS Board           |
          +----------------------+-----------------------+
                                 | Pack Output (6.0V - 8.4V)
                                 v
          +----------------------------------------------+
          | INA219 High-Side Current & Power Sensor      |
          +----------------------+-----------------------+
                                 |
                                 v
          +----------------------------------------------+
          | AMS1117-5.0V LDO Voltage Regulator           |
          +----------------------+-----------------------+
                                 | Regulated 5.0V Rail
                 +---------------+---------------+
                 |                               |
                 v                               v
        [ESP32-C3 Super Mini]          [Sensors & Peripherals]
         - Onboard 3.3V LDO             - Sharp GP2Y1010AU0F (5V)
         - 3.3V Logic to BME680,        - TMB09A05 Buzzer (5V)
           TFT ST7735, INA219
```

---

## 3. Battery Subsystem Analysis

### 3.1. Cell Characteristics (2S1P)
- **Cell Chemistry:** Lithium Cobalt Oxide / Nickel Manganese Cobalt (Li-ion 18650).
- **Nominal Cell Voltage:** 3.7V per cell ($7.4V$ total for 2S pack).
- **Full Charge Voltage:** 4.2V per cell ($8.4V$ total for 2S pack).
- **Discharge Cut-off Voltage:** 3.0V per cell ($6.0V$ total for 2S pack).
- **Rated Capacity:** 2600 mAh ($2.6 Ah$).
- **Total Energy Storage:**
  $$E_{total} = V_{nominal} \times C = 7.4V \times 2.6Ah \approx 19.24 \, \text{Wh}$$

### 3.2. 2S 5A Battery Management System (BMS)
- **Overcharge Protection:** Disconnects charging if any cell exceeds $4.25V \pm 0.05V$.
- **Over-discharge Protection:** Cuts off output if any cell falls below $2.50V \pm 0.08V$.
- **Overcurrent Cutoff:** Triggers if load exceeds $10A$ peak or $5A$ continuous.
- **Short-circuit Protection:** Instantaneous electronic disconnection with automatic recovery once the fault is cleared.

### 3.3. Type-C 2S Boost Charger
- **Input:** Standard USB Type-C 5V/2A input from any standard wall adapter or power bank.
- **Boost Topology:** Boosts 5V input to 8.4V constant current / constant voltage (CC/CV) algorithm.
- **Charging Current:** 2.0A maximum.
- **Charging Duration:**
  $$T_{charge} \approx \frac{2600 \, \text{mAh}}{2000 \, \text{mA}} \times 1.2 \approx 1.5 - 1.8 \, \text{hours}$$

---

## 4. System Power Budget & Operational Autonomy

| Subsystem / Component | Operating Voltage | Average Current Draw | Peak Current Draw | Average Power |
| :--- | :--- | :--- | :--- | :--- |
| **ESP32-C3 (Active Wi-Fi)** | 3.3V (via internal LDO) | 85 mA | 240 mA (Wi-Fi TX burst) | 280 mW |
| **1.8" TFT LCD (ST7735)** | 3.3V Logic / 5V BL | 30 mA | 45 mA | 150 mW |
| **Bosch BME680** | 3.3V (MOX heater pulsed) | 12 mA | 18 mA (during 150ms heat) | 40 mW |
| **Sharp GP2Y1010AU0F** | 5.0V (0.32ms IRED pulse) | 11 mA | 20 mA (during pulse) | 55 mW |
| **INA219 Sensor** | 3.3V | 1 mA | 1 mA | 3.3 mW |
| **TMB09A05 Buzzer** | 5.0V (Only during alarm) | 0 mA (idle) | 35 mA (alarm state) | 0 mW (nominal) |
| **AMS1117-5.0 Quiescent** | 7.4V - 8.4V | 5 mA | 10 mA | 40 mW |
| **Total Steady-State Load** | **Regulated 5.0V Rail** | **~144 mA** | **~369 mA** | **~568 mW** |

### 4.1. Estimated Continuous Operating Time
Because a linear regulator (AMS1117-5.0V) is used, the input current drawn from the 2S battery pack equals the total load current plus quiescent current:
$$I_{battery} \approx 144 \, \text{mA} + 5 \, \text{mA} \approx 149 \, \text{mA} \approx 150 \, \text{mA}$$

Assuming an $85\%$ usable battery discharge window before reaching the cutoff threshold:
$$T_{run} = \frac{2600 \, \text{mAh} \times 0.85}{150 \, \text{mA}} \approx 14.7 \, \text{hours of continuous active operation}$$

### 4.2. Power Optimization Strategies
1. **Dynamic Wi-Fi Sleep:** Switching the ESP32-C3 Wi-Fi subsystem into Modem-Sleep mode between 5-second cloud sync intervals reduces the average MCU current from 85 mA to under 25 mA.
2. **Display Timeout:** Dimming the ST7735 backlight after 60 seconds of inactivity saves an additional 25 mA.
3. **With Power Optimizations:** Total average current drops to $\approx 65 \, \text{mA}$, extending battery autonomy to over **34 hours**.
