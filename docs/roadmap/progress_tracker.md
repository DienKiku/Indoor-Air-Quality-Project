# Project Progress Tracker & Checklist

## 1. Overall Progress Summary

| Phase | Description | Timeline | Status | Completion Rate |
| :--- | :--- | :--- | :---: | :---: |
| **Phase 1** | Inception & System Specification | Weeks 1 – 2 | **Completed** | 100% |
| **Phase 2** | Hardware Prototyping & Sensor Calibration | Weeks 3 – 4 | **In Progress** | 30% |
| **Phase 3** | Embedded Firmware & Cloud Integration | Weeks 5 – 7 | **Pending** | 0% |
| **Phase 4** | Web Dashboard & Acoustic Alerting | Weeks 8 – 9 | **Pending** | 0% |
| **Phase 5** | Verification, Enclosure & Final Reporting | Weeks 10 – 12 | **Pending** | 0% |

---

## 2. Detailed Task Checklist

### Phase 1: Inception & System Specification (Weeks 1 – 2)
- [x] **Task 1.1:** Define project scope, indoor air quality target parameters, and motivation.
- [x] **Task 1.2:** Research WHO and US-EPA IAQ standards and particulate exposure thresholds.
- [x] **Task 1.3:** Author and finalize **Chapter 1: Introduction**.
- [x] **Task 1.4:** Select core components (ESP32-C3 Super Mini, BME680, GP2Y1010AU0F, INA219, ST7735).
- [x] **Task 1.5:** Design 2S Li-ion battery power subsystem (18650 cells, 2S 5A BMS, Type-C boost charger, AMS1117-5.0V).
- [x] **Task 1.6:** Formulate 3-Tier System Architecture and data flow diagrams.
- [x] **Task 1.7:** Author and finalize **Chapter 2: Theoretical Background & System Design**.
- [x] **Task 1.8:** Compile Technical System Specifications (`docs/system-spec/01` to `05`).
- [x] **Task 1.9:** Establish GitHub repository structure and version control workflow.

### Phase 2: Hardware Prototyping & Sensor Validation (Weeks 3 – 4)
- [x] **Task 2.1:** Procure all physical Bill of Materials (BOM) components.
- [ ] **Task 2.2:** Verify ESP32-C3 Super Mini GPIO breakout pinout and power rails.
- [ ] **Task 2.3:** Wire the I2C bus with BME680 (`0x77`) and INA219 (`0x40`) with 4.7k$\Omega$ pull-up resistors.
- [ ] **Task 2.4:** Construct external RC driving circuit for Sharp GP2Y1010AU0F ($150\Omega$ resistor and $220\mu F$ capacitor).
- [ ] **Task 2.5:** Assemble 2S 18650 battery holder, BMS protection board, and Type-C boost charger.
- [ ] **Task 2.6:** Measure AMS1117-5.0V voltage output under varying battery pack voltages ($6.0V$ to $8.4V$).
- [ ] **Task 2.7:** Implement microsecond pulse driver for GP2Y1010AU0F and calibrate ADC transfer function.
- [ ] **Task 2.8:** Burn-in BME680 MOX gas sensor hotplate for baseline resistance calculation.

### Phase 3: Embedded Firmware & Cloud Integration (Weeks 5 – 7)
- [ ] **Task 3.1:** Set up PlatformIO project with ESP32-C3 Arduino framework.
- [ ] **Task 3.2:** Implement non-blocking task scheduler for sensor acquisition, UI refresh, and cloud sync.
- [ ] **Task 3.3:** Integrate INA219 driver to read bus voltage, shunt current, and calculate remaining battery %.
- [ ] **Task 3.4:** Configure Google Firebase project, Realtime Database (RTDB), and security access rules.
- [ ] **Task 3.5:** Establish secure Wi-Fi connectivity and synchronize live telemetry to Firebase every 5 seconds.
- [ ] **Task 3.6:** Initialize hardware SPI on ST7735 1.8" TFT display and implement graphical dashboard layout.

### Phase 4: Web Dashboard & Acoustic Alerting (Weeks 8 – 9)
- [ ] **Task 4.1:** Develop responsive web interface using HTML5, CSS3, and JavaScript.
- [ ] **Task 4.2:** Integrate Firebase Web SDK (v9/v10) for real-time WebSocket data updates.
- [ ] **Task 4.3:** Implement interactive time-series telemetry charts using Chart.js.
- [ ] **Task 4.4:** Assemble NPN transistor driver circuit for the TMB09A05 5V active buzzer.
- [ ] **Task 4.5:** Implement audible alarm logic for hazardous PM2.5, elevated VOCs, and low battery voltage.

### Phase 5: Verification, Packaging & Final Documentation (Weeks 10 – 12)
- [ ] **Task 5.1:** Perform continuous 24-hour stability and cloud synchronization reliability test.
- [ ] **Task 5.2:** Measure actual power draw across different operating states and validate battery autonomy.
- [ ] **Task 5.3:** Design and 3D print protective enclosure with dedicated air intake and ventilation channels.
- [ ] **Task 5.4:** Complete **Chapter 3: Detailed Hardware & Software Design**.
- [ ] **Task 5.5:** Complete **Chapter 4: Implementation & Experimental Evaluation**.
- [ ] **Task 5.6:** Complete **Chapter 5: Conclusion & Future Work**.
- [ ] **Task 5.7:** Final code audit, documentation review, and presentation slide preparation.
