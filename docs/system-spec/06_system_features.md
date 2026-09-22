# System Features Specification

## 1. Indoor Air Quality (IAQ) Sensing Features
* **Real-time PM2.5 Fine Particulate Monitoring:**
  * Uses the Sharp GP2Y1010AU0F optical dust sensor[cite: 1].
  * Microsecond-accurate pulse driving circuit triggering an internal infrared LED with a $0.28\text{ ms}$ sampling window over a $0.32\text{ ms}$ cycle[cite: 1].
  * Internal analog-to-digital conversion (ADC) paired with a 10-sample moving average filter to suppress high-frequency noise and output dust density in $\mu\text{g/m}^3$.
* **Volatile Organic Compounds (VOC) & Gas Resistance Detection:**
  * Uses the Bosch BME680 sensor via standard I2C communication[cite: 1].
  * Dynamic metal-oxide (MOX) heated plate resistance measurement ($k\Omega$) for identifying smoke, solvent vapors, and gaseous pollutants[cite: 1].
* **Indoor Climate Telemetry (Temperature, Humidity, Pressure):**
  * Factory-calibrated ambient environmental acquisition via BME680 with high-precision outputs: temperature ($^\circ\text{C}$), relative humidity ($\%RH$), and barometric pressure ($\text{hPa}$)[cite: 1].

---

## 2. Power Subsystem & Energy Monitoring Features
* **Autonomous 2S Li-ion Battery Architecture:**
  * Powered by dual 18650 lithium-ion cells integrated with a 2S 5A BMS protection module against overcharge, over-discharge, and short circuits[cite: 1].
  * On-board Type-C 2S boost charging circuit supporting mobile charging up to $8.4\text{ V}$[cite: 1].
  * Regulated system bus powered via an AMS1117-5.0V low-dropout voltage regulator[cite: 1].
* **Real-time Battery Fuel Gauge & Power Profiling:**
  * High-side energy monitoring using the INA219 sensor via I2C (`0x40`)[cite: 1].
  * Real-time acquisition of bus voltage ($V$), shunt drop, and instantaneous discharge current ($mA$)[cite: 1].
  * Software-calculated battery State-of-Charge (SoC \%) and operating power consumption ($mW$)[cite: 1].

---

## 3. Local Graphical Display & Acoustic Alerting Features
* **Local Telemetry Dashboard (ST7735 1.8" TFT):**
  * Hardware 4-wire SPI graphical interface with dynamic UI partitioning[cite: 1].
  * 4-quadrant layout displaying: Temperature, Humidity, PM2.5 Dust Level, and VOC/Gas Index.
  * Real-time battery status icon with dynamic color coding based on charge level[cite: 1].
* **Multi-stage Acoustic Alarm System:**
  * Driven by a 5V active buzzer triggered via an NPN transistor switching circuit[cite: 1].
  * System startup and initialization feedback chirp[cite: 1].
  * Configurable acoustic alarm thresholds for dangerous PM2.5 concentrations, critical VOC levels, and low battery voltage[cite: 1].

---

## 4. Cloud Integration & Web Dashboard Features
* **Cloud Telemetry Streaming (Google Firebase):**
  * Automatic 2.4 GHz Wi-Fi connectivity on the ESP32-C3 with resilient auto-reconnect handling[cite: 1].
  * Structured JSON payload synchronization to Google Firebase Realtime Database (RTDB) every 5 seconds[cite: 1].
* **Interactive Responsive Web Dashboard:**
  * Browser-based user interface engineered using HTML5, CSS3, and modern vanilla JavaScript[cite: 1].
  * WebSocket real-time data streaming via the Firebase Web SDK for zero-refresh telemetry updates[cite: 1].
  * Dynamic time-series telemetry visualization utilizing Chart.js[cite: 1].
  * Historical trend analysis for ambient temperature, humidity, particulate density, and battery discharge curves.
