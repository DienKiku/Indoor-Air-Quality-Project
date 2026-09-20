# Weekly Progress Report: Week 02

**Reporting Period:** 2026-09-08 to 2026-09-14  
**Project Name:** Indoor Air Quality (IAQ) & Energy Monitoring IoT System  
**Phase:** Phase 1: Inception & Technical Specification  

---

## 1. Executive Summary
Week 02 successfully finalized all hardware selections and system architecture design. The core processor was designated as the ESP32-C3 Super Mini (RISC-V architecture), paired with the Bosch BME680, Sharp GP2Y1010AU0F optical dust sensor, and INA219 power telemetry module. A rechargeable 2S Li-ion battery management subsystem was architected with USB Type-C charging and AMS1117-5.0V regulation. Technical specifications (`docs/system-spec/01` through `05`) and **Chapter 2: Theoretical Background & System Design** were authored and completed.

---

## 2. Objectives for the Week
- [x] **Objective 1:** Finalize hardware component selection and compile the complete Bill of Materials (BOM).
- [x] **Objective 2:** Design the 3-Tier IoT System Architecture (Edge Node, Firebase Cloud, Web Dashboard).
- [x] **Objective 3:** Author **Chapter 2: Theoretical Background & System Design**.
- [x] **Objective 4:** Author detailed technical specifications for system architecture, hardware, pinout, software, and power management.

---

## 3. Accomplishments & Key Deliverables

### 3.1. Hardware Component Selection & BOM
- Selected **ESP32-C3 Super Mini** (32-bit RISC-V @ 160MHz, 4MB Flash) for its ultra-compact form factor, built-in Wi-Fi/BLE, and low power consumption.
- Selected **Bosch BME680** for 4-in-1 climate and VOC gas sensing via I2C.
- Selected **Sharp GP2Y1010AU0F** for optical infrared PM2.5 dust detection.
- Selected **INA219** for high-side current and voltage sensing on the 2S battery bus.
- Selected **1.8" ST7735 TFT LCD** (SPI) for on-device graphical visual feedback.
- Designed **2S Li-ion Power Subsystem:**
  - 2x 18650 2600mAh cells (7.4V nominal, 8.4V full).
  - 2S 5A BMS protection board.
  - Type-C 3-6V to 2S 2A boost charger module.
  - AMS1117-5.0V LDO regulator.
  - TMB09A05 5V active buzzer.

### 3.2. Technical Documentation
- Authored **[Chapter 2: Theoretical Background & System Design](../reports/chapter_2_theoretical_background.md)**:
  - IAQ metrics, health standards (WHO, US-EPA), and particulate classification.
  - Optical dust detection principles ($0.32ms$ pulse timing and ADC transfer curve).
  - Metal oxide (MOX) gas sensing principles and VOC resistance behavior.
  - Shunt resistor current measurement theory and I2C telemetry via INA219.
  - Google Firebase Realtime Database architecture and synchronization mechanisms.
- Produced technical specifications:
  - `docs/system-spec/01_system_architecture.md`
  - `docs/system-spec/02_hardware_specification.md`
  - `docs/system-spec/03_circuit_and_pinout.md`
  - `docs/system-spec/04_software_and_cloud_spec.md`
  - `docs/system-spec/05_power_management.md`

---

## 4. Key Metrics & Deliverables Table

| Deliverable | Target Deadline | Actual Completion | Status |
| :--- | :--- | :--- | :---: |
| Complete Bill of Materials (BOM) | 2026-09-10 | 2026-09-10 | PASS |
| System Specification Documents (01-05) | 2026-09-12 | 2026-09-12 | PASS |
| Chapter 2: Theoretical Background | 2026-09-14 | 2026-09-14 | PASS |

---

## 5. Challenges, Impediments & Mitigations

| Challenge / Issue | Root Cause | Impact | Mitigation / Solution |
| :--- | :--- | :--- | :--- |
| Limited GPIO on ESP32-C3 | ESP32-C3 Super Mini breaks out only 11 GPIO pins | High | Carefully allocated buses: shared I2C bus (SDA: GPIO8, SCL: GPIO9) for BME680 and INA219; dedicated hardware SPI pins for ST7735; remaining GPIO for dust pulse (GPIO1), ADC (GPIO0), and buzzer (GPIO2). |
| 5V requirement for GP2Y1010AU0F & Buzzer | ESP32-C3 operates at 3.3V logic | Medium | Added AMS1117-5.0V to step down 2S battery pack (7.4V-8.4V) to stable 5.0V. Used NPN transistor for buzzer driving and confirmed GP2Y1010AU0F analog output stays within ESP32-C3 ADC limits. |

---

## 6. Objectives for Next Week (Week 03)
- [ ] **Objective 1:** Procure physical components and test individual modules on breadboard.
- [ ] **Objective 2:** Construct and verify the Sharp GP2Y1010AU0F RC pulse driving circuit ($150\Omega$, $220\mu F$).
- [ ] **Objective 3:** Validate 2S BMS protection board cutoff and Type-C boost charger.
- [ ] **Objective 4:** Develop preliminary sensor acquisition drivers in PlatformIO C/C++.
