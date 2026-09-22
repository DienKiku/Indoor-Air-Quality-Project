# Project Progress Tracker & Checklist

## 1. Overall Progress Summary

| Week / Milestone | Core Engineering Objectives | Status | Progress |
| :--- | :--- | :---: | :---: |
| **Week 1** | Inception, IAQ Standards & Chapter 1 Report | **Completed** | 100% |
| **Week 2** | System Architecture, Tech Specs & Chapter 2 Report | **Completed** | 100% |
| **Weeks 3 – 4** | Component Sourcing & Breadboard Peripheral Testing | **Completed** | 100% |
| **Week 5** | Full Breadboard Integration & Web Dashboard Layout | **Completed** | 100% |
| **Week 6** *(Current)* | KiCad Schematic Capture & PCB Fabrication Prep | **In Progress** | 80% |
| **Week 7** | PCB Assembly, Hardware Bring-Up & Cloud Setup | **Pending** | 0% |
| **Week 8** | Firebase Realtime Sync, Acoustic Alerting & 3D Box | **Pending** | 0% |
| **Week 9** | 24h Stability, Final Documentation & Project Defense | **Pending** | 0% |

---

## 2. Detailed Task Checklist

### Week 1: Project Inception & Requirements Analysis
- [x] Define project scope, target indoor air quality parameters, and problem statement.
- [x] Research WHO and US-EPA IAQ standards (PM2.5 limits, VOC exposure, thermal comfort).
- [x] Select core hardware components (ESP32-C3 Super Mini, BME680, GP2Y1010AU0F, INA219, ST7735).
- [x] Author and finalize **Chapter 1: Introduction**.

### Week 2: System Architecture & Technical Specifications
- [x] Formulate 3-Tier IoT System Architecture (Sensor Node -> Google Firebase -> Web Dashboard).
- [x] Design 2S Li-ion battery power subsystem (18650 cells, 2S 5A BMS, Type-C boost charger, AMS1117-5.0V).
- [x] Author and finalize **Chapter 2: Theoretical Background & System Design**.
- [x] Compile Technical System Specifications (`docs/system-spec/01` to `05`).
- [x] Establish GitHub repository structure and version control workflow.

### Weeks 3 – 4: Hardware Procurement & Breadboard Subsystem Testing
- [x] Procure all physical Bill of Materials (BOM) components.
- [x] Verify ESP32-C3 Super Mini GPIO breakout pinout and power rails on breadboard.
- [x] Assemble and validate Sharp GP2Y1010AU0F RC pulse driver circuit (150 ohm resistor, 220 uF capacitor) on breadboard.
- [x] Wire I2C bus with BME680 and INA219 using pull-up resistors and verify basic address communication.
- [x] Test 2S 18650 battery holder, BMS protection board, and AMS1117-5.0V output voltage stability.

### Week 5: Full Breadboard Integration & Web App Frontend
- [x] Interconnect all modules on breadboard (ESP32-C3, sensors, 1.8" ST7735 TFT, power rails).
- [x] Flash initial firmware to test local screen rendering and sensor data acquisition.
- [x] Develop responsive Web Dashboard layout (`src/frontend/index.html`, `app.js`, CSS) using Chart.js for data visualization.
- [x] Define Firebase Realtime Database payload schema and draft configuration file (`firebase_config.h`).

### Week 6: KiCad Schematic Capture & PCB Preparation (Current Week)
- [x] Author full electronic circuit schematic in KiCad (`hardware/schematics/1.kicad_sch`, `circuit_schematic.png`).
- [x] Assign footprints and verify design rules (ERC) based on the breadboard prototype.
- [x] Lay out PCB traces and prepare Gerber/manufacturing files.
- [ ] Etch/order raw PCB (board trắng) and inspect traces for continuity and short-circuits.

### Week 7: PCB Soldering, Hardware Bring-Up & Cloud Configuration
- [ ] Solder power components (2S BMS, AMS1117-5.0V), ESP32-C3 Super Mini, and passive filters onto PCB.
- [ ] Mount external sensors (BME680, INA219, GP2Y1010AU0F) and ST7735 display onto the board.
- [ ] Measure voltage rails to verify stable operation under battery load.
- [ ] Flash bring-up firmware to validate PCB pinouts, I2C bus addressing, and SPI screen.
- [ ] Configure Google Firebase project, Realtime Database (RTDB), and security access rules.

### Week 8: Firebase Realtime Sync, Acoustic Alerting & 3D Packaging
- [ ] Connect ESP32-C3 to local Wi-Fi and push JSON telemetry to Firebase RTDB every 5 seconds.
- [ ] Connect Web Dashboard to Firebase via WebSocket for live graph updates.
- [ ] Assemble NPN transistor circuit for 5V active buzzer and implement threshold alarm logic (PM2.5/VOC/Battery).
- [ ] 3D print enclosure body and faceplate with airflow channels for sensors.
- [ ] Fit assembled board, battery pack, and display securely inside the enclosure.

### Week 9: Verification, Final Academic Report & Project Defense
- [ ] Run continuous 24-hour stability bench test without disconnection or memory leaks.
- [ ] Measure operating current draw across active Wi-Fi states and evaluate battery autonomy.
- [ ] Complete **Chapter 3: Detailed Hardware & Software Design**.
- [ ] Complete **Chapter 4: Implementation, Testing & Experimental Evaluation**.
- [ ] Complete **Chapter 5: Conclusion & Future Work**.
- [ ] Conduct final codebase audit, prepare presentation slide deck, record product video demo, and deliver project defense.
