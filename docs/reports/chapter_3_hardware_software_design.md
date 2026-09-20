# Chapter 3: Detailed Hardware & Software Design

## 3.1. Hardware Schematic & Interfacing Design
- **3.1.1. Power Distribution Network:** Integration of 2S Li-ion pack, BMS protection, INA219 shunt sensing, AMS1117-5.0V LDO, and decoupling capacitor placement ($10\mu F$ and $0.1\mu F$ ceramic capacitors).
- **3.1.2. ESP32-C3 Super Mini Pin Allocation:** Detailed hardware pinout mapping, GPIO strapping pin constraints (GPIO2, GPIO8, GPIO9), and pull-up resistor values.
- **3.1.3. Optical Dust Sensor Interface:** Design of the external $150\Omega$ resistor and $220\mu F$ electrolytic capacitor pulse circuit for the Sharp GP2Y1010AU0F.
- **3.1.4. I2C Bus Topology:** Multi-device bus configuration accommodating Bosch BME680 (`0x77`) and INA219 (`0x40`) with 4.7k$\Omega$ bus pull-ups.
- **3.1.5. SPI Display Interface:** 4-wire hardware SPI connection for the 1.8-inch ST7735 TFT LCD.
- **3.1.6. Acoustic Alarm Circuit:** NPN switching transistor driver (2N2222 / SS8050) with base resistor and flyback suppression diode for the TMB09A05 active buzzer.

## 3.2. Embedded Firmware Architecture
- **3.2.1. Modular Firmware Structure:** Overview of PlatformIO project layout, header separation, and driver modularization.
- **3.2.2. Non-Blocking Cooperative Scheduler:** Timer-driven task scheduling using `millis()` for deterministic sensor sampling, display refresh, and cloud transmission without blocking delays.
- **3.2.3. Optical Pulse Timing Routine:** Implementation of microsecond-accurate timing (`delayMicroseconds()`) for the GP2Y1010AU0F IRED excitation.
- **3.2.4. Digital Filtering Algorithms:** Implementation of 10-sample moving average filter (MAF) for analog ADC stabilization.
- **3.2.5. Graphical User Interface Implementation:** Display layout, fonts, color palettes (RGB565), and screen refresh optimization on the ST7735.

## 3.3. Cloud Infrastructure & Web Dashboard
- **3.3.1. Google Firebase Realtime Database Provisioning:** Database structure, node hierarchy, and JSON payload definitions.
- **3.3.2. Security Rules & Token Authentication:** Enforcing read/write access control.
- **3.3.3. Web Application Architecture:** HTML5/CSS3/JavaScript responsive frontend architecture.
- **3.3.4. Real-time Telemetry Visualizer:** Dynamic charting with Chart.js and live gauge indicators.
