# Team Task Assignment

## 1. Role-Based Technical Responsibilities

| Member | Assigned Role | Primary Technical Scope |
| :--- | :--- | :--- |
| **Điền** | Hardware, PCB & Mechanical Engineer | KiCad schematic capture, PCB layout and trace routing, board fabrication and component soldering, 3D CAD enclosure modeling, and 3D printing packaging with airflow channels. |
| **Vũ** | Embedded Firmware Engineer | PlatformIO project configuration, peripheral sensor drivers (GP2Y1010AU0F, BME680, INA219), ST7735 TFT display driver, active acoustic buzzer alarm logic, and Firebase client integration on ESP32-C3. |
| **Dũng** | Software & Cloud Engineer | Responsive Web Dashboard development (HTML5, CSS3, JavaScript, Chart.js), Google Firebase Realtime Database setup and security rules, WebSocket real-time telemetry streaming, and frontend UI optimization. |
| **All Members** | Testing & Academic Documentation | System requirements specification, 24-hour stability testing, technical report authoring (Chapters 1 to 5), presentation slide preparation, and final project defense. |

---

## 2. Weekly Milestone Task Breakdown (9 Weeks)

| Week | Detailed Tasks & Deliverables | Responsible Member | Status |
| :---: | :--- | :---: | :---: |
| **Week 1** | - Define project scope, target IAQ parameters (WHO, US-EPA)<br>- Select core components (ESP32-C3, BME680, GP2Y1010, INA219)<br>- Author Chapter 1: Introduction | All Members | **Completed** |
| **Week 2** | - Formulate 3-Tier IoT System Architecture & 2S Li-ion battery subsystem<br>- Compile Technical System Specifications<br>- Author Chapter 2: Theoretical Background & System Design | All Members | **Completed** |
| **Week 3** | - Procure physical BOM components<br>- Verify ESP32-C3 pinout mapping and breadboard power rails | **Điền** (Hardware) | **Completed** |
| **Week 4** | - Test I2C bus with BME680 and INA219 on breadboard<br>- Assemble RC driving circuit for GP2Y1010, burn-in MOX gas sensor<br>- Set up baseline PlatformIO project repository | **Điền** (RC Filter / I2C Bus)<br>**Vũ** (Test Code & Framework) | **Completed** |
| **Week 5** | - Interconnect complete system prototype on breadboard<br>- Flash bring-up test code for sensors and ST7735 display<br>- Develop responsive Web Dashboard UI (HTML/CSS/JS, Chart.js) | **Điền** (System Breadboard)<br>**Vũ** (Firmware Display Test)<br>**Dũng** (Web Dashboard UI) | **Completed** |
| **Week 6** *(Current)* | - Finalize KiCad schematic capture (`.kicad_sch`) and run ERC checks<br>- Complete PCB trace routing, export Gerber files, and prep fabrication<br>- Preliminary 3D enclosure dimensions draft<br>- Implement telemetry visualization charts on Web Dashboard | **Điền** (KiCad, PCB & 3D Concept)<br>**Dũng** (Web Charts & Telemetry) | **In Progress** |
| **Week 7** | - Etch/mill and solder physical PCB assembly with all components<br>- Calibrate sensor drivers (GP2Y1010 pulse timing, BME680, INA219)<br>- Configure Google Firebase Realtime Database project & security rules | **Điền** (PCB Soldering & Bring-Up)<br>**Vũ** (Sensor Firmware & UI)<br>**Dũng** (Firebase RTDB Setup) | **Pending** |
| **Week 8** | - Implement Wi-Fi connectivity and push periodic JSON telemetry to Firebase<br>- Connect Web Dashboard to Firebase via WebSocket for live streaming<br>- Integrate NPN transistor active buzzer driver and threshold alerts<br>- Detail 3D CAD design, print enclosure, and assemble final hardware | **Vũ** (Wi-Fi, Firebase Sync, Buzzer)<br>**Dũng** (Web WebSocket Integration)<br>**Điền** (3D Print & Final Packaging) | **Pending** |
| **Week 9** | - Conduct continuous 24-hour stability bench test and power profiling<br>- Author complete technical report (Chapters 3, 4, and 5)<br>- Finalize slide deck, record demo video, and deliver project defense | All Members | **Pending** |

---

## 3. Workload Contribution Matrix

| Member | Contribution Rate | Signature |
| :--- | :---: | :---: |
| **Điền** | 33.3% | |
| **Vũ** | 33.3% | |
| **Dũng** | 33.3% | |
