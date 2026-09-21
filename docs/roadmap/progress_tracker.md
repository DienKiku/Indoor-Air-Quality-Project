# Project Progress Tracker & Checklist

## 1. Overall Progress Summary

| Period | Description | Status | Completion Rate |
| :--- | :--- | :---: | :---: |
| **Weeks 1 – 2** | Inception & System Specification | **Completed** | 100% |
| **Weeks 3 – 4** | BOM Procurement & Component Preparation | **Completed** | 100% |
| **Week 5** | Raw PCB Fabrication (Board Trắng) | **Completed** | 100% |
| **Week 6** | PCB Assembly, Test Firmware & Web UI | **Completed** | 100% |
| **Weeks 7 – 8** | Embedded Firmware, Firebase & Acoustic Alerting | **In Progress** | 20% |
| **Week 9** | Enclosure, Verification & Final Reporting | **Pending** | 0% |

---

## 2. Detailed Task Checklist

### Week 1: Inception & Component Selection
- [x] Define project scope, indoor air quality target parameters, and motivation.
- [x] Research WHO and US-EPA IAQ standards and particulate exposure thresholds.
- [x] Author and finalize **Chapter 1: Introduction**.
- [x] Select core components (ESP32-C3 Super Mini, BME680, GP2Y1010AU0F, INA219, ST7735).

### Week 2: System Design & Architecture
- [x] Design 2S Li-ion battery power subsystem (18650 cells, 2S 5A BMS, Type-C boost charger, AMS1117-5.0V).
- [x] Formulate 3-Tier System Architecture and data flow diagrams.
- [x] Author and finalize **Chapter 2: Theoretical Background & System Design**.
- [x] Compile Technical System Specifications (`docs/system-spec/01` to `05`).
- [x] Establish GitHub repository structure and version control workflow.

### Week 3: BOM Procurement & Schematic Capture
- [x] Procure all physical Bill of Materials (BOM) components.
- [x] Draw full circuit schematic in KiCad connecting ESP32-C3 with power management and all sensors (`hardware/schematics/1.kicad_sch`).
- [x] Export visual SVG circuit diagram (`hardware/schematics/circuit_schematic.svg`).
- [x] Check footprint dimensions for PCB prototyping.

### Week 4: Component Preparation & Code Setup
- [x] Burn-in BME680 MOX gas sensor hotplate for baseline resistance calculation.
- [x] Construct external RC driving circuit for Sharp GP2Y1010AU0F ($150\Omega$ / $240\Omega$ resistor and $220\mu F$ capacitor).
- [x] Set up PlatformIO project with ESP32-C3 Arduino framework to prepare for hardware tests.

### Week 5: Raw PCB Fabrication (Board Trắng)
- [x] Complete prototype board layout design based on verified schematic.
- [x] Fabricate prototype PCB (board trắng), drill mounting holes, and inspect copper traces.
- [x] Perform continuity/short-circuit checks on power rails ($V_{CC}$, $GND$, $3.3V$, $5.0V$) before assembly.

### Week 6: PCB Assembly, Test Firmware & Web UI
- [x] Solder power subsystem (2S BMS, AMS1117), ESP32-C3, and passive components onto the board.
- [x] Mount external sensors and display (BME680, INA219, GP2Y1010AU0F, ST7735) onto the board.
- [x] Flash hardware bring-up firmware (`src/test/offline_display_test.ino`) to validate populated connections.
- [x] Verify on-device 4-panel graphical UI, buzzer acoustics, and real-time battery monitoring on ST7735.
- [x] Develop responsive web interface using HTML5, CSS3, and JavaScript (`src/frontend/index.html`).
- [x] Implement interactive time-series telemetry charts using Chart.js (`src/frontend/js/app.js`).

### Week 7: Embedded Firmware & Local Display
- [x] Implement non-blocking task scheduler for sensor acquisition, UI refresh, and cloud sync.
- [x] Implement microsecond pulse driver for GP2Y1010AU0F with hardware 1.5x scaling and 5-sample smoothing.
- [x] Integrate INA219 driver to read bus voltage, shunt current, and calculate remaining battery %.
- [x] Initialize hardware SPI on ST7735 1.8" TFT display and implement graphical dashboard layout.

### Week 8: Firebase Integration & Acoustic Alerting
- [x] Author Google Firebase Setup Guide (`docs/system-spec/06_firebase_setup_guide.md`).
- [ ] Configure Google Firebase project, Realtime Database (RTDB), and security access rules.
- [ ] Establish secure Wi-Fi connectivity and synchronize live telemetry to Firebase every 5 seconds.
- [ ] Integrate Firebase Web SDK (v9/v10) for real-time WebSocket data updates.
- [ ] Assemble NPN transistor driver circuit for the TMB09A05 5V active buzzer.
- [ ] Implement audible alarm logic for hazardous PM2.5, elevated VOCs, and low battery voltage.

### Week 9: Verification, Packaging & Final Documentation
- [ ] Perform continuous 24-hour stability and cloud synchronization reliability test.
- [ ] Measure actual power draw across different operating states and validate battery autonomy.
- [ ] Design and 3D print protective enclosure with dedicated air intake and ventilation channels.
- [ ] Complete **Chapter 3: Detailed Hardware & Software Design**.
- [ ] Complete **Chapter 4: Implementation & Experimental Evaluation**.
- [ ] Complete **Chapter 5: Conclusion & Future Work**.
- [ ] Final code audit, documentation review, and presentation slide preparation.
