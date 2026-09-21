# Project Progress Tracker & Checklist

## 1. Overall Progress Summary

| Period | Description | Status | Completion Rate |
| :--- | :--- | :---: | :---: |
| **Weeks 1 – 2** | Inception & System Specification | **Completed** | 100% |
| **Weeks 3 – 4** | BOM Procurement & Component Preparation | **Completed** | 100% |
| **Week 5** | Full System Breadboard Validation | **Completed** | 100% |
| **Week 6** | PCB Fabrication & Soldering | **In Progress** | 0% |
| **Weeks 7 – 8** | Firmware, Firebase & Web Dashboard | **Pending** | 0% |
| **Week 9** | Enclosure, Verification & Final Reporting | **Pending** | 0% |

---

## 2. Detailed Task Checklist

### Week 1: Inception & Component Selection
- [x] Define project scope, indoor air quality target parameters, and motivation[cite: 1].
- [x] Research WHO and US-EPA IAQ standards and particulate exposure thresholds[cite: 1].
- [x] Author and finalize **Chapter 1: Introduction**[cite: 1].
- [x] Select core components (ESP32-C3 Super Mini, BME680, GP2Y1010AU0F, INA219, ST7735)[cite: 1].

### Week 2: System Design & Architecture
- [x] Design 2S Li-ion battery power subsystem (18650 cells, 2S 5A BMS, Type-C boost charger, AMS1117-5.0V)[cite: 1].
- [x] Formulate 3-Tier System Architecture and data flow diagrams[cite: 1].
- [x] Author and finalize **Chapter 2: Theoretical Background & System Design**[cite: 1].
- [x] Compile Technical System Specifications (`docs/system-spec/01` to `05`)[cite: 1].
- [x] Establish GitHub repository structure and version control workflow[cite: 1].

### Week 3: BOM Procurement & Schematic Capture
- [x] Procure all physical Bill of Materials (BOM) components[cite: 1].
- [x] Draw full circuit schematic connecting ESP32-C3 with power management and all sensors.
- [x] Check footprint dimensions for upcoming PCB design.

### Week 4: Component Preparation & Code Setup
- [x] Burn-in BME680 MOX gas sensor hotplate for baseline resistance calculation[cite: 1].
- [x] Construct external RC driving circuit for Sharp GP2Y1010AU0F ($150\Omega$ resistor and $220\mu F$ capacitor)[cite: 1].
- [x] Set up PlatformIO project with ESP32-C3 Arduino framework to prepare for hardware tests[cite: 1].

### Week 5: Full System Breadboard Validation
- [x] Verify ESP32-C3 Super Mini GPIO breakout pinout and power rails on breadboard[cite: 1].
- [x] Assemble 2S 18650 battery holder, BMS protection board, and Type-C boost charger[cite: 1].
- [x] Measure AMS1117-5.0V voltage output under varying battery pack voltages ($6.0V$ to $8.4V$)[cite: 1].
- [x] Wire the I2C bus with BME680 (`0x77`) and INA219 (`0x40`) with 4.7k$\Omega$ pull-up resistors on breadboard[cite: 1].
- [x] Wire ST7735 display via SPI and GP2Y1010AU0F via ADC to complete breadboard prototype.

### Week 6: PCB Fabrication & Assembly
- [ ] Complete PCB layout design based on verified breadboard schematic.
- [ ] Fabricate raw PCB, drill mounting holes, and inspect copper traces.
- [ ] Solder power subsystem (2S BMS, AMS1117), ESP32-C3, and passive components onto the PCB.
- [ ] Mount external sensors/display (BME680, INA219, GP2Y1010AU0F, ST7735) onto the PCB.
- [ ] Flash hardware bring-up firmware to validate populated PCB connections.

### Week 7: Embedded Firmware & Local Display
- [ ] Implement non-blocking task scheduler for sensor acquisition, UI refresh, and cloud sync[cite: 1].
- [ ] Implement microsecond pulse driver for GP2Y1010AU0F and calibrate ADC transfer function[cite: 1].
- [ ] Integrate INA219 driver to read bus voltage, shunt current, and calculate remaining battery %[cite: 1].
- [ ] Initialize hardware SPI on ST7735 1.8" TFT display and implement graphical dashboard layout[cite: 1].

### Week 8: Web Dashboard, Firebase & Acoustic Alerting
- [ ] Configure Google Firebase project, Realtime Database (RTDB), and security access rules[cite: 1].
- [ ] Establish secure Wi-Fi connectivity and synchronize live telemetry to Firebase every 5 seconds[cite: 1].
- [ ] Develop responsive web interface using HTML5, CSS3, and JavaScript[cite: 1].
- [ ] Integrate Firebase Web SDK (v9/v10) for real-time WebSocket data updates[cite: 1].
- [ ] Implement interactive time-series telemetry charts using Chart.js[cite: 1].
- [ ] Assemble NPN transistor driver circuit for the TMB09A05 5V active buzzer[cite: 1].
- [ ] Implement audible alarm logic for hazardous PM2.5, elevated VOCs, and low battery voltage[cite: 1].

### Week 9: Verification, Packaging & Final Documentation
- [ ] Perform continuous 24-hour stability and cloud synchronization reliability test[cite: 1].
- [ ] Measure actual power draw across different operating states and validate battery autonomy[cite: 1].
- [ ] Design and 3D print protective enclosure with dedicated air intake and ventilation channels[cite: 1].
- [ ] Complete **Chapter 3: Detailed Hardware & Software Design**[cite: 1].
- [ ] Complete **Chapter 4: Implementation & Experimental Evaluation**[cite: 1].
- [ ] Complete **Chapter 5: Conclusion & Future Work**[cite: 1].
- [ ] Final code audit, documentation review, and presentation slide preparation[cite: 1].
