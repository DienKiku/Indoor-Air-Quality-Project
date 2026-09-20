# Chapter 4: Implementation & Experimental Evaluation

## 4.1. Physical Prototype Assembly & Construction
- **4.1.1. Breadboard & PCB Prototyping:** Step-by-step assembly of the sensor node and power subsystem.
- **4.1.2. Wiring Harness & Enclosure Integration:** Arrangement of 18650 battery holder, display bezel, and airflow channels for particulate ingress.

## 4.2. Sensor Calibration & Validation Procedures
- **4.2.1. Sharp GP2Y1010AU0F Baseline Zero-Dust Calibration:** Measuring zero-dust offset voltage $V_{clean}$ in a sealed HEPA chamber and evaluating transfer slope.
- **4.2.2. BME680 MOX Gas Sensor Burn-In:** 48-hour continuous burn-in procedure to stabilize baseline gas resistance ($R_{base}$).
- **4.2.3. Microclimate Sensor Cross-Verification:** Comparing temperature and humidity readings against calibrated reference hygrometers.

## 4.3. Experimental Results & Performance Analysis
- **4.3.1. Transient Pollution Response Testing:** Evaluating system response to indoor cooking smoke, incense combustion, and ethanol vapor exposure.
- **4.3.2. Optical Dust Sensor Response Time:** Measurement of detection latency and moving average filter smoothing performance.
- **4.3.3. Acoustic Alarm & Threshold Triggering:** Verification of active buzzer activation under hazardous PM2.5 and low battery voltage events.

## 4.4. Power Consumption & Battery Autonomy Profiling
- **4.4.1. Telemetry Data Logging with INA219:** Current draw profiles during active Wi-Fi transmission, display refresh, and idle states.
- **4.4.2. Battery Discharge Curve Validation:** Continuous runtime test of the 2S 2600mAh battery pack from 8.4V full charge to 6.0V cutoff.
- **4.4.3. Evaluation of Power-Saving Strategies:** Comparison of continuous active mode versus modem-sleep duty cycling.
