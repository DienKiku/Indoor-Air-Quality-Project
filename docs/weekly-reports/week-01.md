# Weekly Progress Report: Week 01

**Reporting Period:** 2026-09-01 to 2026-09-07  
**Project Name:** Indoor Air Quality (IAQ) & Energy Monitoring IoT System  
**Phase:** Phase 1: Inception & Technical Specification  

---

## 1. Executive Summary
Week 01 focused on project inception, problem formulation, and establishing theoretical foundations. Comprehensive research was conducted on indoor airborne contaminants (PM2.5, VOCs, CO2) and international air quality standards (WHO, US-EPA). The project scope, engineering requirements, and **Chapter 1: Introduction** were authored and finalized.

---

## 2. Objectives for the Week
- [x] **Objective 1:** Define the core problem statement, research motivation, and target scope for an indoor environmental monitoring station.
- [x] **Objective 2:** Conduct a comprehensive literature survey on indoor air contaminants and health implications.
- [x] **Objective 3:** Author and finalize **Chapter 1: Introduction** of the project report.
- [x] **Objective 4:** Establish the initial project repository structure and documentation standards.

---

## 3. Accomplishments & Key Deliverables

### 3.1. Problem Formulation & Scope Definition
- Analyzed indoor environmental data indicating that humans spend over 85% of their daily time indoors, where pollutant concentrations can exceed outdoor levels by 2 to 5 times.
- Identified target pollutants for the monitoring station: Fine Particulate Matter ($PM_{2.5}$), Volatile Organic Compounds (VOCs), ambient Temperature, Relative Humidity, and Barometric Pressure.
- Established the need for self-contained, portable power management with real-time energy telemetry.

### 3.2. Technical Documentation
- Authored **[Chapter 1: Introduction](../reports/chapter_1_introduction.md)** covering:
  - Background & Problem Statement.
  - Research Objectives & Targeted Capabilities.
  - Scope & Delimitations.
  - Scientific and Practical Significance.
  - Overall Report Organization.
- Established the project directory layout and version control conventions on GitHub.

---

## 4. Key Metrics & Deliverables Table

| Deliverable | Target Deadline | Actual Completion | Status |
| :--- | :--- | :--- | :---: |
| Project Charter & Requirements | 2026-09-03 | 2026-09-03 | PASS |
| Literature Review on IAQ & PM2.5 | 2026-09-05 | 2026-09-05 | PASS |
| Chapter 1: Introduction Draft | 2026-09-07 | 2026-09-07 | PASS |

---

## 5. Challenges, Impediments & Mitigations

| Challenge / Issue | Root Cause | Impact | Mitigation / Solution |
| :--- | :--- | :--- | :--- |
| Narrowing target pollutants | Broad variety of indoor gases (CO, CO2, Formaldehyde, Ozone, VOCs) | Medium | Selected the Bosch BME680 sensor which provides multi-gas / VOC resistance alongside full climate parameters, paired with a dedicated optical PM2.5 sensor. |
| Power supply constraints | Continuous Wi-Fi and sensor heating demands significant power | High | Decided to adopt a 2S Li-ion battery pack with autonomous BMS and INA219 energy monitoring to evaluate battery lifetime accurately. |

---

## 6. Objectives for Next Week (Week 02)
- [ ] **Objective 1:** Select exact physical components (MCU, sensors, display, battery subsystem).
- [ ] **Objective 2:** Design the 3-tier system architecture and pinout allocation.
- [ ] **Objective 3:** Author and complete **Chapter 2: Theoretical Background & System Design**.
- [ ] **Objective 4:** Compile technical specifications in `docs/system-spec/`.
