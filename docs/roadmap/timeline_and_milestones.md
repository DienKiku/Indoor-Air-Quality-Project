# Project Roadmap: Weekly Milestones

## Phase 1: Inception & Technical Specification (Weeks 1–2)

### Week 1: Problem Formulation & Requirements Analysis

* Define the project scope for indoor air quality monitoring.
* Identify monitored parameters:

  * PM2.5
  * Temperature
  * Humidity
  * Gas/VOC indicators
  * Battery status
* Review relevant air-quality guidelines and monitoring requirements.
* Define the initial hardware Bill of Materials (BOM).
* Complete **Chapter 1: Introduction**.

### Week 2: System Architecture & Technical Specifications

* Define the 3-Tier IoT architecture:
  **Sensor Node → Firebase → Web Dashboard**.
* Select the main hardware:

  * ESP32-C3 Super Mini
  * BME680
  * GP2Y1010AU0F
  * INA219
  * ST7735 TFT
* Design the battery and power subsystem.
* Define communication interfaces and GPIO assignments.
* Prepare the technical system specifications.
* Complete **Chapter 2: Theoretical Background & System Design**.

## Phase 2: Breadboard Prototyping & Circuit Design (Weeks 3–5)

### Week 3: Breadboard Prototype

* Assemble the main components on a breadboard.
* Verify power distribution and voltage levels.
* Connect and test the ESP32-C3, BME680, GP2Y1010AU0F, INA219, and ST7735 TFT.
* Test basic sensor communication.
* Verify sensor readings and display output.
* Identify and correct initial hardware connection problems.

### Week 4: Local Firmware Development

* Develop the initial ESP32-C3 firmware.
* Implement sensor data acquisition.
* Display temperature, humidity, PM2.5, gas information, and battery status on the TFT.
* Implement basic buzzer/alarm functionality.
* Test the firmware using the breadboard prototype.
* Verify stable operation of the main hardware modules.

### Week 5: KiCad Schematic Development

* Transfer the verified breadboard circuit into KiCad.
* Create the complete electrical schematic.
* Define component symbols, power rails, GPIO connections, sensor interfaces, display interface, and battery monitoring circuit.
* Perform Electrical Rules Check (ERC).
* Compare the KiCad schematic with the working breadboard circuit.
* Prepare the schematic for PCB layout.

## Phase 3: PCB Development & Hardware Finalization (Week 6)

### Week 6: PCB Layout & Hardware Preparation — Current Week

* Complete and verify the KiCad schematic.
* Import the schematic into KiCad PCB Editor.
* Assign and verify component footprints.
* Define PCB board dimensions and mounting holes.
* Arrange components according to functional and mechanical requirements.
* Route power and signal traces.
* Pay particular attention to:

  * Power distribution
  * Sensor signal integrity
  * ESP32-C3 antenna clearance
  * Ground connections
  * Display and sensor interfaces
* Run Design Rules Check (DRC).
* Generate Gerber files for PCB fabrication.
* Prepare the PCB for manufacturing.

**Current Progress:**

* KiCad schematic: **Completed**
* Breadboard prototype: **Completed and tested**
* PCB design: **In progress**
* PCB fabrication: **Not yet completed**

## Phase 4: Cloud Integration & System Testing (Weeks 7–8)

### Week 7: Wi-Fi, Firebase & Web Dashboard Integration

* Implement Wi-Fi connectivity on the ESP32-C3.
* Connect the ESP32-C3 to Firebase Realtime Database.
* Implement periodic sensor telemetry transmission.
* Send temperature, humidity, PM2.5, gas/VOC, battery voltage, and battery current data.
* Develop and test the Web Dashboard.
* Display real-time sensor data using charts.
* Implement automatic Wi-Fi reconnection.
* Verify the complete communication chain:
  **Sensor → ESP32-C3 → Wi-Fi → Firebase → Web Dashboard**.

### Week 8: System Testing, Calibration & Power Evaluation

* Assemble and test the fabricated PCB.
* Compare PCB operation with the original breadboard prototype.
* Perform sensor calibration.
* Configure PM2.5 and low-battery alarm thresholds.
* Test buzzer warning and critical alarm patterns.
* Measure active and idle current consumption using INA219.
* Conduct a long-duration stability test.
* Evaluate battery operating time under different Wi-Fi transmission intervals.

## Phase 5: Packaging, Field Evaluation & Final Defense (Week 9)

### Week 9: Enclosure, Field Testing & Final Defense

**Hardware & Packaging**

* Design and fabricate the protective enclosure.
* Install the PCB, ESP32-C3, sensors, TFT display, and battery pack.
* Verify appropriate airflow around the environmental sensors.
* Perform final electrical and mechanical inspection.

**Experimental Evaluation**

* Deploy the system in different indoor environments:

  * Office
  * Kitchen
  * Laboratory
* Record sensor responses to cooking fumes, dust disturbance, and ventilation changes.
* Evaluate system stability and communication reliability.
* Record battery discharge behavior.
* Compare experimental results with theoretical expectations.

**Final Documentation**

* Complete **Chapter 3: Detailed Hardware & Software Design**.
* Complete **Chapter 4: Implementation, Testing & Experimental Evaluation**.
* Complete **Chapter 5: Conclusion & Future Work**.
* Perform final code and hardware audit.
* Organize project files and documentation.

**Defense Preparation**

* Prepare presentation slides.
* Prepare system block diagrams and circuit diagrams.
* Prepare experimental results and graphs.
* Record the end-to-end demonstration:
  **Sensors → ESP32-C3 → Firebase → Web Dashboard**.
* Complete final submission and defense preparation.
