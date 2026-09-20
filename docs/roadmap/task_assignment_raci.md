# Task Assignment & RACI Matrix

## 1. Work Breakdown Structure (WBS)

The development tasks are divided across five functional domains:

```
Indoor Air Quality IoT Project
├── 1.0 Hardware & Circuit Engineering
│   ├── 1.1 Schematic design & pinout allocation
│   ├── 1.2 2S Li-ion battery pack, BMS & Type-C boost charger integration
│   ├── 1.3 Sharp GP2Y1010AU0F pulse & filter circuit assembly
│   ├── 1.4 Sensor bus wiring (I2C: BME680, INA219; SPI: ST7735)
│   └── 1.5 Transistor driver circuit for TMB09A05 buzzer
├── 2.0 Embedded Firmware Development
│   ├── 2.1 Microcontroller initialization (ESP32-C3 RISC-V, PlatformIO)
│   ├── 2.2 Microsecond pulse timing & ADC sampling for PM2.5 dust sensor
│   ├── 2.3 I2C driver integration (Bosch BME680 & INA219 energy monitor)
│   ├── 2.4 SPI driver & graphical rendering on ST7735 1.8" TFT
│   └── 2.5 Non-blocking cooperative scheduler & power optimization
├── 3.0 Cloud & Middleware Infrastructure
│   ├── 3.1 Google Firebase project setup & Realtime Database provisioning
│   ├── 3.2 Firebase security rules & authentication token configuration
│   └── 3.3 Data schema design for live telemetry and historical logging
├── 4.0 Frontend & Visualization Dashboard
│   ├── 4.1 Responsive web interface (HTML5/CSS3)
│   ├── 4.2 Firebase JavaScript SDK integration (real-time data streaming)
│   ├── 4.3 Time-series chart visualization (Chart.js)
│   └── 4.4 Environmental alert banners and battery health indicators
└── 5.0 Verification & Technical Documentation
    ├── 5.1 Weekly progress reporting & milestone verification
    ├── 5.2 Technical specification documentation
    └── 5.3 Academic engineering project report (Chapters 1 to 5)
```

---

## 2. RACI Matrix

The RACI matrix defines role responsibilities:
- **R - Responsible:** The role that performs the activity to achieve the deliverable.
- **A - Accountable:** The sole role with final approval and ownership of the deliverable.
- **C - Consulted:** A subject matter expert whose input is sought during execution.
- **I - Informed:** An individual kept updated on progress and results.

### Role Definitions:
- **PM / Arch:** Project Lead & System Architect
- **HW:** Hardware & Circuit Engineer
- **FW:** Embedded Firmware Engineer
- **Cloud/Web:** Cloud & Web Frontend Developer
- **Doc:** Documentation & Verification Specialist

| WBS Code | Deliverable / Task Description | PM / Arch | HW | FW | Cloud/Web | Doc |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: |
| **1.1** | Pinout Allocation & Bus Topology | **A** | **R** | **C** | I | I |
| **1.2** | 2S Battery, BMS & Type-C Charger Integration | A | **R** | C | I | I |
| **1.3** | Sharp GP2Y1010AU0F Pulse Circuit Assembly | A | **R** | **R** | I | I |
| **1.4** | Sensor Bus Wiring (I2C & SPI) | A | **R** | C | I | I |
| **1.5** | Buzzer Driving Circuit & Audio Testing | A | **R** | C | I | I |
| **2.1** | ESP32-C3 PlatformIO Environment Setup | A | C | **R** | I | I |
| **2.2** | Sharp GP2Y1010AU0F Timing & Moving Average Filter | A | C | **R** | I | I |
| **2.3** | BME680 & INA219 I2C Drivers Implementation | A | I | **R** | I | I |
| **2.4** | ST7735 Graphical Dashboard UI Rendering | A | I | **R** | C | I |
| **2.5** | Power-Save Logic (Modem-Sleep & Display Dimming)| A | C | **R** | I | I |
| **3.1** | Firebase Realtime Database Provisioning | A | I | C | **R** | I |
| **3.2** | Firebase Security Rules & Authentication | **A** | I | C | **R** | I |
| **3.3** | JSON Payload Schema Definition | **A** | I | **R** | **R** | I |
| **4.1** | Web Dashboard UI Layout & Design | A | I | I | **R** | I |
| **4.2** | Firebase SDK WebSocket Data Stream | A | I | C | **R** | I |
| **4.3** | Chart.js Time-Series Telemetry Graphs | A | I | I | **R** | I |
| **4.4** | Threshold Alarms & Visual Indicators | A | I | C | **R** | I |
| **5.1** | Weekly Progress Reports (Weeks 1 to 12) | **A** | C | C | C | **R** |
| **5.2** | Technical Specifications (Docs 01 to 05) | **A** | **R** | **R** | **R** | **R** |
| **5.3** | Academic Engineering Report (Chapters 1 to 5) | **A** | C | C | C | **R** |
