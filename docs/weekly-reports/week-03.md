# Weekly Progress Report: Week 03

**Reporting Period:** 2026-09-15 to 2026-09-21  
**Project Name:** Indoor Air Quality (IAQ) & Energy Monitoring IoT System  
**Phase:** Phase 2: Hardware Prototyping & Sensor Validation  

---

## 1. Executive Summary
Week 03 achieved significant engineering milestones across hardware prototyping, electronic schematic capture, and offline firmware verification. A physical prototype test board ("board trắng") was assembled and wired. The complete system schematic was designed in KiCad (`1.kicad_sch`) with custom footprint and symbol definitions. Offline firmware was developed and successfully executed on the hardware (`src/test/offline_display_test.ino`), driving the 1.8-inch ST7735 TFT LCD with a custom 4-panel dashboard layout, active buzzer acoustics, and real-time telemetry from the Bosch BME680, Sharp GP2Y1010AU0F, and INA219 energy monitor.

---

## 2. Objectives for the Week
- [x] **Objective 1:** Assemble and wire the physical prototype test board ("board trắng").
- [x] **Objective 2:** Design and finalize the complete hardware schematic using KiCad.
- [x] **Objective 3:** Implement and validate standalone offline test firmware on the ESP32-C3.
- [x] **Objective 4:** Verify sensor data acquisition and graphical UI rendering on the 1.8" ST7735 TFT display.
- [x] **Objective 5:** Calibrate optical dust sensing with hardware scaling and validate INA219 power telemetry.
- [x] **Objective 6:** Prepare Google Firebase cloud schema and client configuration for Phase 3.

---

## 3. Accomplishments & Key Deliverables

### 3.1. Hardware Prototyping & KiCad Schematic
- Assembled the physical prototype board connecting:
  - ESP32-C3 Super Mini microcontroller.
  - Bosch BME680 (I2C: SDA on GPIO6, SCL on GPIO7).
  - INA219 Power Monitor (I2C: SDA on GPIO6, SCL on GPIO7).
  - Sharp GP2Y1010AU0F (IRED drive on GPIO3, Vo analog on GPIO4).
  - 1.8-inch ST7735 TFT LCD (SPI: CS on GPIO21, DC on GPIO20, RST on GPIO10, MOSI on GPIO9, SCLK on GPIO8, BL on GPIO5).
  - Acoustic Buzzer circuit driven by a 2SC1815 NPN transistor via GPIO2.
- Authored the complete electronic schematic in KiCad (`hardware/schematics/1.kicad_sch`, `1.kicad_pro`, `New_Library_1.kicad_sym`).
- Rendered high-resolution SVG visual diagram (`hardware/schematics/circuit_schematic.svg`) for repository inspection.

### 3.2. Offline Test Firmware & Graphical UI
- Developed and verified `src/test/offline_display_test.ino` on physical hardware:
  - Startup splash screen with system initialization check.
  - Acoustic double-chirp notification on boot (`BUZZER_PIN`).
  - 4-panel graphical layout on 128x160 TFT:
    - **TEMP Panel:** Displays temperature in °C; highlights RED (`COLOR_WARN`) when $> 35^\circ\text{C}$.
    - **HUMI Panel:** Displays relative humidity in %RH with green status.
    - **PM2.5 Panel:** Displays particulate mass concentration in $mg/m^3$; triggers alarm when $> 0.15 \, mg/m^3$.
    - **GAS Panel:** Displays BME680 gas resistance in $k\Omega$.
  - Bottom energy telemetry bar: Displays battery voltage (e.g., $7.9\text{V}$), discharge current (e.g., $88\text{mA}$), and dynamically draws a graphical 2S battery cell icon filled according to calculated SoC percentage.

### 3.3. Sensor Signal Calibration
- Integrated a $1.5\times$ scaling factor for the optical dust sensor analog output to account for the hardware resistor divider protecting the ESP32-C3 ADC.
- Implemented a 5-sample smoothing filter with $280\mu s$ pulse delay and $40\mu s$ sampling window.
- Formulated linear 2S State-of-Charge (SoC) calculation ($6.0\text{V} - 8.4\text{V}$).

---

## 4. Key Metrics & Test Results

| Test Scenario | Target Parameter | Measured Value | Result |
| :--- | :--- | :--- | :---: |
| **I2C Bus Scan** | BME680 & INA219 detection | Both devices acknowledged | **PASS** |
| **Display SPI Clock** | ST7735 rendering speed | Clean frame update @ 2s interval | **PASS** |
| **Optical Dust Sensor** | Baseline voltage in ambient air | $\approx 0.6V - 0.9V$ scaled | **PASS** |
| **Power Telemetry** | INA219 bus voltage reading | Matches multimeter within $\pm 0.02V$ | **PASS** |
| **Acoustic Alarm** | Buzzer trigger on $PM_{2.5} > 0.15$ | Sounds $200ms$ warning beep | **PASS** |

---

## 5. Challenges, Impediments & Mitigations

| Challenge / Issue | Root Cause | Mitigation / Solution |
| :--- | :--- | :--- |
| **Dust sensor Vo exceeding 3.3V** | Sharp GP2Y1010AU0F runs at 5V, outputting up to ~4.5V under heavy dust | Added a resistor voltage divider to step down the signal to $\le 3.3V$, and added a $1.5\times$ software correction factor in ADC calculation. |
| **LaTeX KaTeX error on GitHub** | MathJax parse conflict with unescaped `%` and multi-line `cases` in documentation | Re-formulated the SoC equation as a compact clamped piecewise formula, ensuring 100% flawless GitHub rendering. |

---

## 6. Objectives for Next Week (Week 04)
- [ ] **Objective 1:** Connect ESP32-C3 to local Wi-Fi and establish real-time link with Google Firebase Realtime Database.
- [ ] **Objective 2:** Configure Firebase project credentials (`FIREBASE_HOST`, `FIREBASE_AUTH`) and verify cloud JSON payload delivery.
- [ ] **Objective 3:** Merge offline display logic with Firebase synchronization tasks into the main PlatformIO firmware (`src/firmware/src/main.cpp`).
- [ ] **Objective 4:** Test initial Web Dashboard connection to Firebase Realtime Database stream.
