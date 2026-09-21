# Indoor Air Quality (IAQ) & Energy Monitoring IoT System

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Platform: ESP32-C3](https://img.shields.io/badge/Platform-ESP32--C3%20Super%20Mini-red.svg)](https://www.espressif.com/en/products/socs/esp32-c3)
[![Framework: C/C++ (PlatformIO/Arduino)](https://img.shields.io/badge/Framework-C%2FC%2B%2B%20Arduino-green.svg)](https://platformio.org/)
[![Cloud: Google Firebase](https://img.shields.io/badge/Cloud-Google%20Firebase-orange.svg)](https://firebase.google.com/)

An edge-computing Internet of Things (IoT) station designed for real-time indoor environmental quality monitoring and autonomous power management. Powered by an ultra-compact **ESP32-C3 Super Mini (RISC-V)** microcontroller, the device integrates multi-sensor environmental sensing (PM2.5, VOC, Temperature, Humidity, Pressure), on-device visual feedback (1.8" ST7735 TFT), local acoustic alerts, a rechargeable 2S Li-ion battery subsystem with real-time power telemetry (INA219), and cloud synchronization with **Google Firebase**.

---

## 1. System Architecture

The project follows a modular **Three-Tier IoT Architecture**:

```mermaid
flowchart TD
    subgraph Tier1["Tier 1: Sensor & Edge Node (ESP32-C3 Super Mini)"]
        Sensors["Sensors:<br/>- BME680 (Temp, Hum, Press, Gas/VOC via I2C)<br/>- Sharp GP2Y1010AU0F (PM2.5 Dust via ADC + I-LED)<br/>- INA219 (Battery V, I, P via I2C)"]
        MCU["ESP32-C3 Super Mini<br/>(32-bit RISC-V @ 160MHz, 4MB Flash)"]
        Display["1.8-inch ST7735 TFT Display (SPI)"]
        Alert["TMB09A05 5V Buzzer (GPIO)"]
        PowerSubsystem["2S Li-ion Battery (2x 18650 2600mAh)<br/>- 2S 5A BMS Protection<br/>- Type-C 2S Boost Charger (8.4V)<br/>- AMS1117-5.0V LDO Regulator"]
        
        PowerSubsystem -->|"7.4V - 8.4V"| INA219
        INA219 -->|"V_bus / I_shunt"| AMS1117
        AMS1117 -->|"5.0V"| MCU
        AMS1117 -->|"5.0V"| Alert
        AMS1117 -->|"5.0V"| Sensors
        Sensors -->|"Data"| MCU
        MCU -->|"Render UI"| Display
        MCU -->|"Acoustic Alarm"| Alert
    end

    subgraph Tier2["Tier 2: Cloud Middleware (Google Firebase)"]
        FirebaseRTDB[("Firebase Realtime Database<br/>(NoSQL JSON Tree)")]
        FirebaseAuth["Firebase Authentication<br/>(Token / Database Secret)"]
        FirebaseHosting["Firebase Hosting / CDN"]
        FirebaseRTDB --- FirebaseAuth
    end

    subgraph Tier3["Tier 3: User Dashboard & Presentation"]
        WebDashboard["Web Application Dashboard<br/>- Real-time Gauges & Charts<br/>- Battery Health & Power Draw<br/>- Pollution & Threshold Alerts"]
        MobileView["Responsive Mobile UI"]
    end

    MCU -->|"Wi-Fi 802.11 b/g/n / HTTPS / WSS"| FirebaseRTDB
    FirebaseRTDB -->|"WebSocket Real-time Stream"| WebDashboard
    FirebaseRTDB -->|"WebSocket Real-time Stream"| MobileView
```

---

## 2. Hardware Bill of Materials (BOM)

| Component | Specification / Model | Interface | Function / Purpose |
| :--- | :--- | :--- | :--- |
| **Microcontroller (MCU)** | ESP32-C3 Super Mini (4MB Flash, RISC-V @ 160MHz) | Wi-Fi / BLE | Core controller, sensor aggregation, cloud comms |
| **Environmental Sensor** | Bosch BME680 | I2C (0x77 / 0x76) | Ambient Temp, Relative Humidity, Pressure, Gas/VOC |
| **Particulate Sensor** | Sharp GP2Y1010AU0F | Analog ADC + Digital GPIO | PM2.5 Optical Dust Density detection |
| **Energy Monitor** | INA219 MCU-219 | I2C (0x40) | 2S Battery bus voltage, discharge current, power draw |
| **Display** | 1.8-inch TFT LCD (ST7735 controller, 128x160) | SPI | Local graphical dashboard and status readouts |
| **Acoustic Indicator** | TMB09A05 5V Active Buzzer (9x5.5mm) | GPIO (via Transistor) | Audible alarms for hazardous IAQ and low battery |
| **Battery Cells** | 2x 18650 Li-ion Cells (2600 mAh each in 2S1P) | Battery Holder | Portable power source (Nominal: 7.4V, Full: 8.4V) |
| **Battery Management** | 2S 5A Lithium Protection Board (BMS) | Direct Battery | Overcharge, over-discharge, overcurrent & short-circuit protection |
| **Charger Board** | Type-C 3-6V to 2S-2A (8.4V) Boost Charger | USB Type-C | Fast, universal USB-C charging for 2S pack |
| **Voltage Regulator** | AMS1117-5.0V LDO Module | Power Rail | Steps down 7.4-8.4V battery output to stable 5.0V |

---

## 3. Hardware Circuit Schematic

The circuit schematic has been designed in KiCad and verified on physical prototype board:

![Hardware Circuit Schematic](hardware/schematics/circuit_schematic.png)

> **KiCad Design Source Files:** Available in [`hardware/schematics/`](hardware/schematics/) (`1.kicad_sch`, `1.kicad_pro`, `New_Library_1.kicad_sym`).

---

## 4. Repository Structure & Documentation

This repository is organized into distinct functional directories:

```text
├── hardware/
│   └── schematics/                # KiCad CAD schematic & visual diagram
│       ├── 1.kicad_sch            # KiCad schematic source file
│       ├── 1.kicad_pro            # KiCad project file
│       └── circuit_schematic.png  # Rendered KiCad schematic image
├── docs/
│   ├── system-spec/               # Technical system specifications
│   │   ├── 01_system_architecture.md
│   │   ├── 02_hardware_specification.md
│   │   ├── 03_circuit_and_pinout.md
│   │   ├── 04_software_and_cloud_spec.md
│   │   └── 05_power_management.md
│   ├── roadmap/                   # Project planning, Gantt, and RACI
│   │   ├── timeline_and_milestones.md
│   │   ├── task_assignment_raci.md
│   │   └── progress_tracker.md
│   ├── weekly-reports/            # Weekly progress tracking
│   │   ├── week-01.md
│   │   ├── week-02.md
│   │   └── week-03.md
│   └── reports/                   # Academic & Engineering Project Reports
│       ├── chapter_1_introduction.md
│       ├── chapter_2_theoretical_background.md
│       ├── chapter_3_hardware_software_design.md
│       ├── chapter_4_implementation_testing.md
│       └── chapter_5_conclusion_future_work.md
└── src/
    ├── firmware/                  # ESP32-C3 Arduino firmware (firmware.ino, firebase_config.h)
    ├── cloud-firebase/            # Firebase RTDB rules and sample telemetry schemas
    └── frontend/                  # Web Dashboard application (HTML5/CSS3/JS, Chart.js)
```

---

## 5. Software & Cloud Subsystems

- **ESP32-C3 Firmware ([`src/firmware/`](src/firmware/)):** The core firmware sketch ([`firmware.ino`](src/firmware/firmware.ino)) coordinates sensor acquisitions, ST7735 TFT graphical rendering (4-panel UI), 2S battery gauge monitoring, acoustic alarm triggering, and configured credentials ([`firebase_config.h`](src/firmware/firebase_config.h)). Can be edited and flashed using Arduino IDE or PlatformIO.
- **Cloud Backend ([`src/cloud-firebase/`](src/cloud-firebase/)):** Google Firebase Realtime Database schema and security rules for real-time station telemetry streaming.
- **User Web Dashboard ([`src/frontend/`](src/frontend/)):** Real-time monitoring dashboard ([`index.html`](src/frontend/index.html)) with live Chart.js trend visualization directly synced via Firebase WebSocket.

---

## 6. License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
