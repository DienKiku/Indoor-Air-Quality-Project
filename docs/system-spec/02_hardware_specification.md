# 02. Hardware Specification

## 1. Component Breakdown

This document provides a comprehensive technical breakdown of all physical hardware components utilized in the Indoor Air Quality (IAQ) and Energy Monitoring System.

---

## 2. Microcontroller Unit (MCU): ESP32-C3 Super Mini

- **Architecture:** 32-bit RISC-V Single-Core processor (RV32IMC instruction set).
- **Clock Frequency:** Up to 160 MHz.
- **Memory:** 400 KB SRAM, 384 KB ROM, and 4 MB on-board SPI Flash memory.
- **Wireless Connectivity:**
  - Wi-Fi 802.11 b/g/n (2.4 GHz) with up to 150 Mbps throughput.
  - Bluetooth 5 (LE - Low Energy) and Bluetooth Mesh.
- **Peripherals:** 11 GPIO pins, 4-channel 12-bit ADC (up to 2.5 MHz sampling rate), SPI, I2C, UART, PWM.
- **Form Factor:** Ultra-compact module (22.5 mm x 18 mm) with ceramic antenna and onboard 3.3V LDO regulator.
- **Power Input:** 3.3V (VCC pin) or 5.0V (VIN pin).

---

## 3. Environmental Sensors

### 3.1. Bosch BME680 (4-in-1 Environmental Sensor)
- **Parameters Measured:** Ambient Temperature, Relative Humidity, Barometric Pressure, and Volatile Organic Compounds (VOC) Gas Resistance.
- **Operating Range:**
  - Temperature: -40°C to +85°C (Accuracy: ±1.0°C).
  - Humidity: 0% to 100% RH (Accuracy: ±3% RH).
  - Barometric Pressure: 300 hPa to 1100 hPa (Accuracy: ±0.6 hPa).
  - Gas Sensor: Metal oxide (MOX) sensor sensitive to broad-spectrum volatile organic compounds (VOCs), sulfides, and carbon monoxide.
- **Communication Protocol:** I2C (Default address: `0x77` or `0x76`).
- **Operating Voltage:** 1.71V - 3.6V (Supplied via 3.3V rail).

### 3.2. Sharp GP2Y1010AU0F (Optical Dust Sensor)
- **Target Pollutant:** Suspended particulate matter (PM2.5 / PM10).
- **Operating Principle:** Optical laser/infrared scattering. An infrared emitting diode (IRED) and phototransistor are diagonally arranged inside an air chamber. Scattered light from dust particles generates a proportional analog voltage.
- **Sensitivity:** 0.5V per 100 $\mu g/m^3$.
- **Detection Range:** 0 to 500 $\mu g/m^3$.
- **Operating Voltage:** 4.5V - 5.5V (Supplied via regulated 5.0V rail).
- **Control Signal:** Active-low pulse ($0.32 ms$ duration, period $10 ms$) applied to the I-LED pin.
- **Output:** Analog DC voltage ($V_o$).

---

## 4. Energy Monitoring: INA219 High-Side Power Sensor

- **Function:** Real-time continuous monitoring of 2S battery pack bus voltage, shunt current, and total system power consumption.
- **Shunt Resistor:** 0.1 $\Omega$ (1% precision).
- **Voltage Measurement Range:** 0V to 26V DC (Bus Voltage).
- **Current Measurement Range:** ±3.2A with 0.8mA resolution.
- **ADC Resolution:** 12-bit programmable internal analog-to-digital converter.
- **Communication Protocol:** I2C (Address: `0x40`).
- **Operating Voltage:** 3.0V - 5.5V (Connected to 3.3V logic).

---

## 5. Visual Display: 1.8-inch TFT LCD (ST7735)

- **Display Controller:** Sitronix ST7735.
- **Resolution:** 128 x 160 pixels.
- **Color Depth:** 65K Full RGB (16-bit color, 5-6-5 format).
- **Interface:** 4-wire Serial Peripheral Interface (SPI: SCL, SDA, CS, DC, RES).
- **Backlight:** LED backlight controlled via 3.3V / PWM.
- **Operating Voltage:** 3.3V / 5.0V (Logic pins operating at 3.3V).

---

## 6. Acoustic Indicator: TMB09A05 5V Active Buzzer

- **Type:** Active electromagnetic buzzer with internal oscillation circuit.
- **Dimensions:** 9 mm diameter x 5.5 mm height.
- **Rated Voltage:** 5.0V DC (Operating: 4.0V - 7.0V).
- **Sound Pressure Level (SPL):** $\ge 85 dB$ at 10 cm distance.
- **Resonant Frequency:** 2700 ± 300 Hz.
- **Driving Method:** Switched through an NPN BJT (e.g., 2N2222 / SS8050) driven by an ESP32-C3 GPIO pin.

---

## 7. Power Supply & Battery Subsystem (2S Configuration)

```
[2x 18650 Li-ion Cells in Series (2S1P)]
               |
               v
 [2S 5A BMS Protection Board (Overcharge / Overdischarge)]
               |
        +------+---------------------------------+
        |                                        |
        v                                        v
[Type-C 2S Boost Charger]                [INA219 Power Monitor]
(Charges 2S from 5V Type-C)                      |
                                                 v
                                        [AMS1117-5.0V LDO]
                                                 |
                               +-----------------+-----------------+
                               | 5.0V                              | 5.0V
                               v                                   v
                      [ESP32-C3 VIN pin]                 [Sharp GP2Y1010AU0F & Buzzer]
                               | (Internal 3.3V LDO)
                               v
                      [BME680, ST7735, INA219 Logic]
```

### 7.1. Battery Cells
- **Model:** 18650 Cylindrical Lithium-ion.
- **Configuration:** 2S1P (2 cells in series).
- **Capacity:** 2600 mAh per cell (Total energy: $7.4V \times 2.6Ah \approx 19.24 Wh$).
- **Voltage Range:**
  - Fully Charged: 8.4V (4.2V/cell).
  - Nominal: 7.4V (3.7V/cell).
  - Cutoff / Depleted: 6.0V (3.0V/cell).
- **Enclosure:** 2-slot 18650 battery holder with spring contacts.

### 7.2. Battery Management System (BMS): 2S 5A Protection Board
- **Overcharge Protection Voltage:** 4.25V ± 0.05V per cell.
- **Over-discharge Protection Voltage:** 2.50V ± 0.08V per cell.
- **Continuous Discharge Current:** 5A.
- **Overcurrent Protection Current:** 10A.
- **Protection Features:** Short-circuit recovery, overcharge release, over-discharge cutoff.

### 7.3. Battery Charger: Type-C 3-6V to 2S 2A (8.4V) Boost Charger
- **Input:** 3.0V - 6.0V DC via standard USB Type-C port (compatible with standard 5V mobile chargers and power banks).
- **Output:** 8.4V constant current / constant voltage (CC/CV) charging profile.
- **Charging Current:** 2.0A peak.
- **Indicator LEDs:** Red (Charging), Blue/Green (Charge Complete).

### 7.4. Voltage Regulation: AMS1117-5.0V LDO Module
- **Input Voltage:** 7.4V - 8.4V from the 2S battery pack.
- **Regulated Output Voltage:** 5.0V DC (±1%).
- **Maximum Output Current:** 800 mA - 1.0 A.
- **Dropout Voltage:** ~1.1V at full load.
- **Thermal Management:** Compact PCB heatsink tab.
