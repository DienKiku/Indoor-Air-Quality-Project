# 01. System Architecture Specification

## 1. Overview

The Indoor Air Quality (IAQ) and Energy Monitoring System is engineered as a distributed, edge-enabled IoT platform. It continuously measures indoor microclimate parameters and hazardous airborne pollutants while autonomously managing its own power reserves.

The system is architected in **Three Distinct Tiers**:
1. **Tier 1: Physical Sensing & Edge Node**
2. **Tier 2: Cloud Middleware & Data Synchronization (Google Firebase)**
3. **Tier 3: Client Application & Data Visualization Dashboard**

```
+-----------------------------------------------------------------------------------+
|                           TIER 1: SENSOR & EDGE NODE                              |
|                                                                                   |
|  +--------------------+  +----------------------+  +---------------------------+  |
|  |   Bosch BME680     |  | Sharp GP2Y1010AU0F   |  |     INA219 Power Sense    |  |
|  | (Temp/Hum/Press/Gas|  | (Optical PM2.5 Dust) |  | (2S Battery V, I, Power)  |  |
|  +---------+----------+  +----------+-----------+  +-------------+-------------+  |
|            | I2C                    | Analog ADC/GPIO            | I2C            |
|            +-------------------+    |    +-----------------------+                |
|                                |    |    |                                        |
|                                v    v    v                                        |
|                     +---------------------------+                                 |
|                     | ESP32-C3 Super Mini (MCU) |                                 |
|                     |  - 32-bit RISC-V @ 160MHz |                                 |
|                     |  - Moving Average Filter  |                                 |
|                     |  - Threshold Evaluation   |                                 |
|                     +-------------+-------------+                                 |
|                                   |                                               |
|                  +----------------+----------------+                              |
|                  | SPI                             | GPIO                         |
|                  v                                 v                              |
|     +-------------------------+       +-------------------------+                 |
|     | 1.8" ST7735 TFT Display |       | TMB09A05 Active Buzzer  |                 |
|     | (Real-time Edge UI)     |       | (Acoustic Danger Alarm) |                 |
|     +-------------------------+       +-------------------------+                 |
+-----------------------------------+-----------------------------------------------+
                                    | Wi-Fi 802.11 b/g/n (WSS / HTTPS)
                                    v
+-----------------------------------------------------------------------------------+
|                        TIER 2: GOOGLE FIREBASE CLOUD                              |
|                                                                                   |
|  +-------------------------------------+  +------------------------------------+  |
|  |     Firebase Realtime Database      |  |         Security & Auth            |  |
|  | - /iaq_monitor/{id}/current (Live)  |  | - Database Token / Secret          |  |
|  | - /iaq_monitor/{id}/history (Logs)  |  | - Granular Read/Write Access Rules |  |
|  +-------------------------------------+  +------------------------------------+  |
+-----------------------------------+-----------------------------------------------+
                                    | Real-time Data Stream (WebSockets)
                                    v
+-----------------------------------------------------------------------------------+
|                        TIER 3: USER DASHBOARD & CLIENT                            |
|                                                                                   |
|  +-------------------------------------+  +------------------------------------+  |
|  |       Responsive Web Dashboard      |  |         Alert Notification         |  |
|  | - Real-time Gauge Metrics           |  | - PM2.5 / VOC Spikes               |  |
|  | - Time-series Chart.js Visualizer   |  | - Low Battery State Warning        |  |
|  | - Battery & Power telemetry         |  | - Environmental Quality Index      |  |
|  +-------------------------------------+  +------------------------------------+  |
+-----------------------------------------------------------------------------------+
```

---

## 2. Tier Details

### 2.1. Tier 1: Sensor & Edge Node
- **Core Processor:** ESP32-C3 Super Mini (single-core 32-bit RISC-V processor clocked up to 160 MHz, with 400 KB SRAM and 4MB on-board Flash).
- **Sub-edge Processing:**
  - Performs local sensor data acquisition, digital calibration, and sensor heating cycles (BME680 MOX hotplate).
  - Drives high-precision microsecond pulse modulation for the Sharp GP2Y1010AU0F infrared emitting diode (IRED).
  - Executes moving-average digital filtering on analog ADC readings to eliminate high-frequency noise.
  - Controls an SPI-driven 1.8-inch TFT LCD (ST7735) for real-time visual output.
  - Triggers local acoustic buzzer warnings when air quality drops below predefined health thresholds or battery falls below critical voltage.

### 2.2. Tier 2: Cloud Middleware (Google Firebase)
- **Firebase Realtime Database (RTDB):** Provides low-latency, bi-directional data synchronization over WebSockets and HTTPS.
- **Data Model:**
  - Ephemeral state (`/current`): Stored for immediate dashboard consumption with minimal latency.
  - Persistent state (`/history`): Time-series records logged at regular intervals for historical trend analysis.
- **Security:** Managed via Firebase Realtime Database Security Rules, preventing unauthorized modification.

### 2.3. Tier 3: User Dashboard & Presentation
- **Frontend Technologies:** HTML5, CSS3, JavaScript (ES6+), Chart.js, and Firebase Web SDK.
- **Features:**
  - Real-time gauge dials for PM2.5, VOC Resistance, Temperature, Humidity, and Atmospheric Pressure.
  - Energy telemetry metrics: Battery Voltage, Discharge Current (mA), Power (mW), and Estimated Remaining Battery Percentage.
  - Dynamic alert banners reflecting air quality status (Good, Moderate, Unhealthy, Hazardous).
