# Chapter 5: Conclusion & Future Work

## 5.1. Summary of Contributions
- Successful development of a low-cost, portable, edge-enabled Indoor Air Quality (IAQ) and Energy Monitoring IoT station powered by the ESP32-C3 Super Mini (RISC-V).
- Accurate multi-parameter environmental sensing integrating fine particulates (PM2.5), volatile organic compounds (VOCs), ambient temperature, relative humidity, and barometric pressure.
- Implementation of an autonomous 2S Li-ion battery subsystem featuring USB Type-C boost charging, 2S BMS protection, and real-time power telemetry via the INA219 sensor.
- Seamless real-time cloud data synchronization with Google Firebase Realtime Database and an intuitive, responsive Web Dashboard for end-user visualization.

## 5.2. Limitations of Current Design
- Optical dust sensing with the Sharp GP2Y1010AU0F is sensitive to ambient air velocity and lacks a laser-driven active fan intake (found in higher-cost laser scattering units like PMS7003).
- Linear voltage regulation (AMS1117-5.0V) exhibits lower efficiency (~67%) compared to synchronous buck switching regulators, generating minor thermal dissipation.
- BME680 VOC reading requires regular baseline adaptation to account for long-term sensor aging.

## 5.3. Recommendations for Future Work
- **Hardware Enhancements:** Upgrade the linear regulator to a high-efficiency buck DC-DC converter (e.g., MP2307 / TPS62160) to boost battery runtime by 25-35%.
- **Sensor Upgrades:** Integrate a laser scattering particulate sensor (e.g., Plantower PMS7003) for precise binning of PM1.0, PM2.5, and PM10.
- **Edge AI & Anomaly Detection:** Implement lightweight TinyML anomaly detection algorithms on the ESP32-C3 to forecast air quality degradation trends locally before cloud upload.
- **Enclosure & Industrial Design:** Fabricate an injection-molded or SLA 3D-printed enclosure with optimized aerodynamic inlet/outlet vents.
