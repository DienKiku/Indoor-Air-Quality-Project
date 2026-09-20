# Chapter 1: Introduction

## 1.1. Background & Problem Statement

In modern urbanized societies, humans spend approximately 85% to 90% of their daily lives inside enclosed environments—including residences, educational institutions, offices, and commercial spaces. Consequently, the quality of indoor air significantly dictates human health, respiratory well-being, cognitive performance, and overall quality of life.

Despite widespread public awareness regarding outdoor atmospheric smog and industrial emissions, empirical environmental studies consistently reveal that **indoor air pollutant concentrations can be two to five times—and in severe cases up to one hundred times—higher than outdoor levels**. Indoor environments accumulate diverse airborne pollutants emitted from:
- Cooking activities, biomass combustion, and tobacco smoke, which release hazardous **Fine Particulate Matter ($PM_{2.5}$ and $PM_{10}$)**.
- Building materials, synthetic paints, adhesives, varnishes, and cleaning detergents, which emit a wide spectrum of **Volatile Organic Compounds (VOCs)** such as formaldehyde, benzene, and toluene.
- Human respiration in inadequately ventilated spaces, resulting in elevated carbon dioxide ($CO_2$) and stagnant humidity, fostering microbial colonies and mold growth.

Inhalation of fine particles with aerodynamic diameters $\le 2.5 \, \mu m$ ($PM_{2.5}$) poses acute and chronic health risks. Due to their minute dimensions, $PM_{2.5}$ particles bypass upper respiratory filtration mechanisms, penetrating deep into the pulmonary alveoli and entering the systemic bloodstream. Long-term exposure correlates directly with chronic obstructive pulmonary disease (COPD), ischemic heart disease, stroke, and lung cancer. Concurrently, elevated concentrations of VOCs induce "Sick Building Syndrome" (SBS), characterized by headaches, mucous membrane irritation, fatigue, and impaired cognitive clarity.

---

## 1.2. Motivation & Significance

While commercial consumer air purifiers and standalone monitors exist on the market, they present several critical engineering and operational limitations:
1. **Proprietary Ecosystems & Data Silos:** Commercial units often restrict data access to proprietary cloud silos with closed communication protocols, precluding integration into open-source building management systems or customized analytical platforms.
2. **Limited Multi-Parameter Sensing:** Low-cost monitors typically detect only a single parameter (e.g., temperature and humidity, or dust alone), failing to deliver a holistic indoor air quality (IAQ) assessment that combines fine particulates, chemical gases (VOCs), and barometric microclimate variables.
3. **Lack of Autonomous Power Telemetry:** Portable monitoring nodes deployed in dynamic indoor environments require untethered battery operation. However, existing devices lack integrated high-precision power telemetry, leaving users unable to predict remaining runtime or manage energy consumption effectively.

To address these challenges, this project designs and implements an open, edge-computing **Indoor Air Quality (IAQ) and Energy Monitoring IoT System**. By combining an ultra-low-power 32-bit RISC-V microcontroller (ESP32-C3) with laboratory-grade multi-sensor instrumentation (Bosch BME680, Sharp GP2Y1010AU0F, INA219), a full-color graphical display (ST7735), an autonomous 2S Li-ion battery subsystem, and real-time cloud synchronization via **Google Firebase**, this system provides a comprehensive, cost-effective, and fully verifiable indoor environmental management solution.

---

## 1.3. Research Objectives & System Scope

### 1.3.1. Primary Objectives
The primary aim of this project is to develop, validate, and evaluate an autonomous, IoT-enabled indoor environmental monitoring station. Specific technical objectives include:
1. **Multi-Parameter Environmental Sensing:** Design and interface sensory circuits capable of measuring particulate matter ($PM_{2.5}$), total volatile organic compounds (VOC gas resistance), ambient temperature, relative humidity, and atmospheric pressure.
2. **Autonomous Power Management & Energy Telemetry:** Architect a self-contained 2S Li-ion battery power subsystem featuring overcharge/over-discharge protection (BMS), USB Type-C boost charging, linear voltage regulation, and real-time high-side current and voltage sensing via the INA219 transducer.
3. **Edge Signal Processing & Local Alerting:** Implement digital filtering algorithms (10-sample moving average) for analog optical dust sensing, dynamic baseline calibration for MOX gas resistance, on-device rendering on a 1.8-inch TFT LCD, and acoustic alarm generation for hazardous conditions.
4. **Real-time Cloud Integration & User Dashboard:** Establish secure Wi-Fi connectivity to synchronize telemetry data to Google Firebase Realtime Database and build a responsive Web Dashboard with live visual gauges, time-series charts, and historical analytics.

### 1.3.2. Scope and Delimitations
- **Deployment Domain:** The system is engineered for indoor domestic, office, and academic laboratory spaces (enclosed areas ranging from $15 \, m^2$ to $60 \, m^2$).
- **Target Particulate Range:** Optical detection of $PM_{2.5}$ dust concentrations between $0 \, \mu g/m^3$ and $500 \, \mu g/m^3$.
- **Target Microclimate Range:** Ambient temperature (-10°C to +60°C), relative humidity (10% to 90% RH), and barometric pressure (300 hPa to 1100 hPa).
- **Network Constraints:** Requires a standard 2.4 GHz IEEE 802.11 b/g/n Wi-Fi local access point with Internet connectivity for cloud synchronization.

---

## 1.4. Methodology & Engineering Approach

The project adheres to an iterative hardware-software co-design methodology:
1. **Theoretical Formulation:** Mathematical modeling of optical dust scattering, metal-oxide semiconductor gas reaction kinetics, and battery State-of-Charge (SoC) estimation.
2. **Hardware Design & Prototyping:** Breadboard assembly, verification of electrical signal integrity across SPI and I2C buses, design of the optical sensor RC pulse network, and validation of the 2S battery protection circuit.
3. **Firmware Engineering:** Modular C/C++ development utilizing PlatformIO, implementing non-blocking cooperative scheduling to coordinate sensor sampling, graphical rendering, and network synchronization.
4. **Cloud Infrastructure & Frontend Development:** Configuration of Google Firebase Realtime Database schema and security rules, paired with an asynchronous web dashboard developed using HTML5, CSS3, JavaScript, and Chart.js.
5. **Experimental Validation:** Comprehensive empirical testing including sensor baseline calibration, power consumption profiling across operational states, and battery autonomy benchmarking.

---

## 1.5. Report Organization

The remainder of this report is organized as follows:
- **Chapter 2: Theoretical Background & System Design** details the scientific principles of indoor air quality metrics, sensing transducer technologies, embedded RISC-V architectures, Firebase cloud mechanics, and the overall system design.
- **Chapter 3: Detailed Hardware & Software Design** describes the schematic design, PCB layout, pinout assignments, C/C++ firmware state machines, and web application architecture.
- **Chapter 4: Implementation & Experimental Evaluation** presents the physical assembly, calibration procedures, experimental results, power efficiency benchmarks, and system validation.
- **Chapter 5: Conclusion & Future Work** summarizes the major engineering contributions, discusses system limitations, and outlines future enhancements.
