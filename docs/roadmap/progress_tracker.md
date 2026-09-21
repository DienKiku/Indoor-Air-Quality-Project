# Project Progress Tracker & Checklist

## 1. Overall Progress Summary

| Week / Milestone | Core Engineering Objectives | Status | Progress |
| :--- | :--- | :---: | :---: |
| **Week 1** | Inception, IAQ Standards & Chapter 1 Report | **Completed** | 100% |
| **Week 2** | System Architecture, Tech Specs & Chapter 2 Report | **Completed** | 100% |
| **Week 3** *(Current)* | Hardware Prototype, KiCad Schematic & Display Firmware | **Completed** | 100% |
| **Week 4** | WiFi & Google Firebase Realtime Telemetry Sync | **Next Up** | 0% |
| **Week 5** | Multi-level Acoustic Alerting & Power Profiling | **Pending** | 0% |
| **Week 6** | 24-Hour Continuous Stability & Multi-sensor Calibration | **Pending** | 0% |
| **Week 7** | Custom Enclosure 3D CAD & Mechanical Packaging | **Pending** | 0% |
| **Week 8** | Indoor Field Testing & Battery Autonomy Evaluation | **Pending** | 0% |
| **Week 9** | Academic Project Reports (Chapters 3, 4, 5) | **Pending** | 0% |
| **Week 10** | Final Code Audit, Demonstration & Defense Preparation | **Pending** | 0% |

---

## 2. Detailed Task Checklist

### Week 1: Project Inception & Requirements Analysis
- [x] Define project scope, target indoor air quality parameters, and problem statement.
- [x] Research WHO and US-EPA IAQ standards (PM2.5 limits, VOC exposure, thermal comfort).
- [x] Select core hardware components (ESP32-C3 Super Mini, BME680, GP2Y1010AU0F, INA219, ST7735).
- [x] Author and finalize **Chapter 1: Introduction**.

### Week 2: System Architecture & Technical Specifications
- [x] Formulate 3-Tier IoT System Architecture (Sensor Node $\rightarrow$ Google Firebase $\rightarrow$ Web Dashboard).
- [x] Design 2S Li-ion battery power subsystem (18650 cells, 2S 5A BMS, Type-C boost charger, AMS1117-5.0V).
- [x] Author and finalize **Chapter 2: Theoretical Background & System Design**.
- [x] Compile Technical System Specifications (`docs/system-spec/01` to `05`).
- [x] Establish GitHub repository structure and version control workflow.

### Week 3: Hardware Prototyping, Schematic Capture & Local Firmware (Current)
- [x] Procure all physical Bill of Materials (BOM) components.
- [x] Author full electronic circuit schematic in KiCad (`hardware/schematics/1.kicad_sch`, `circuit_schematic.png`).
- [x] Assemble and wire physical prototype circuit board with sensors, display, and power distribution rails.
- [x] Implement and flash verified primary firmware (`src/firmware/firmware.ino`):
  - [x] ST7735 1.8" TFT 4-panel graphical layout (`TEMP`, `HUMI`, `PM2.5`, `GAS`).
  - [x] 2S Battery SoC gauge with voltage, discharge current, and color-coded icon.
  - [x] Optical dust sensor microsecond pulse driver with hardware $1.5\times$ divider scaling.
  - [x] Acoustic double-chirp startup notification and buzzer threshold alarm.
- [x] Construct Web Dashboard layout (`src/frontend/index.html`, `app.js`) and configure Firebase parameters (`src/firmware/firebase_config.h`).

### Week 4: Wi-Fi Connectivity & Firebase Realtime Cloud Sync
- [ ] Connect ESP32-C3 to local Wi-Fi access point using credentials in `firebase_config.h`.
- [ ] Implement periodic JSON telemetry push from `firmware.ino` to Firebase RTDB node `/iaq_stations/ESP32C3_STATION_01/current`.
- [ ] Validate live WebSocket streaming from Firebase to the Web Dashboard with dynamic Chart.js rendering.
- [ ] Implement automatic Wi-Fi reconnection handling for resilient edge operation.

### Week 5: Acoustic Alarm Thresholding & Power Profiling
- [ ] Calibrate dynamic acoustic alarm patterns (Warning vs. Critical alarm for PM2.5 and low battery).
- [ ] Measure active current draw vs. idle current draw across operating modes using INA219.
- [ ] Benchmark battery operating life under varying Wi-Fi transmission intervals (5s, 15s, 60s).

### Week 6: 24-Hour Continuous Testing & Multi-Sensor Calibration
- [ ] Conduct continuous 24-hour stability bench run without memory leaks or Wi-Fi drops.
- [ ] Calibrate Sharp GP2Y1010AU0F zero-dust baseline voltage in a sealed clean chamber.
- [ ] Evaluate Bosch BME680 gas resistance baseline stabilization and thermal compensation.
- [ ] Audit Firebase security rules and real-time database transmission efficiency.

### Week 7: Protective Enclosure Design & Mechanical Assembly
- [ ] 3D CAD design of compact station enclosure with isolated sensor airflow channels.
- [ ] 3D print enclosure body and faceplate for 1.8" ST7735 TFT and external Type-C port.
- [ ] Assemble sensor board, 2S 18650 battery pack, and BMS inside enclosure with secure standoffs.

### Week 8: Environmental Field Testing & Long-Term Evaluation
- [ ] Deploy assembled IoT station in distinct indoor environments (office, kitchen, laboratory).
- [ ] Log real-time air quality events (cooking fumes, dust disturbance, ventilation changes).
- [ ] Record empirical battery discharge curve and compare against theoretical 2S model.

### Week 9: Engineering Documentation & Report Writing
- [ ] Author **Chapter 3: Detailed Hardware & Software Design**.
- [ ] Author **Chapter 4: Implementation, Testing & Experimental Evaluation**.
- [ ] Author **Chapter 5: Conclusion & Future Work**.

### Week 10: Final System Audit & Project Defense
- [ ] Comprehensive codebase audit, repository polishing, and release tagging (`v1.0.0`).
- [ ] Record end-to-end video demonstration showcasing sensor detection, cloud streaming, and web graphs.
- [ ] Prepare technical defense presentation slides and final submission deliverables.
