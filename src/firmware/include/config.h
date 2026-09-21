#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ==========================================
// 1. PIN DEFINITIONS (ESP32-C3 Super Mini)
// ==========================================

// I2C Bus (BME680: 0x77 / INA219: 0x40)
#define I2C_SDA_PIN         6
#define I2C_SCL_PIN         7

// SPI Bus (1.8" ST7735 TFT LCD: 128x160)
#define TFT_CS_PIN          21
#define TFT_DC_PIN          20
#define TFT_RST_PIN         10
#define TFT_MOSI_PIN        9
#define TFT_SCLK_PIN        8
#define TFT_BL_PIN          5

// Sharp GP2Y1010AU0F Optical Dust Sensor
#define DUST_LED_PIN        3   // Digital output to drive IRED (active LOW)
#define DUST_ANALOG_PIN     4   // Analog input Vo (scaled via voltage divider)
#define DUST_VOLTAGE_RATIO  1.5f// Scaling multiplier for hardware resistor divider

// Acoustic Alert (TMB09A05 5V Active Buzzer via 2SC1815)
#define BUZZER_PIN          2   // Digital output to NPN transistor base

// ==========================================
// 2. TIMING CONSTANTS & INTERVALS
// ==========================================
#define DUST_PULSE_WAIT_US  280  // Time before ADC sampling (280 us)
#define DUST_SAMPLE_WAIT_US 40   // ADC sampling duration (40 us)
#define DUST_SLEEP_WAIT_US  9680 // Remainder of 10ms period (9680 us)

#define INTERVAL_SENSOR_MS  1000 // Sample sensors every 1 second
#define INTERVAL_TFT_MS     1000 // Refresh TFT display every 1 second
#define INTERVAL_CLOUD_MS   5000 // Push to Firebase every 5 seconds

// ==========================================
// 3. THRESHOLDS & ALARM LIMITS
// ==========================================
#define PM25_WARN_MGM3      0.15f   // Warning threshold for PM2.5 (0.15 mg/m3 = 150 ug/m3)
#define BATTERY_WARN_PCT    20.0f   // Low battery threshold (20% SoC)
#define TEMP_WARN_C         35.0f   // High temperature threshold (35 deg C)

#define BATTERY_MIN_VOLTS   6.0f    // 2S Cutoff voltage (3.0V/cell)
#define BATTERY_MAX_VOLTS   8.4f    // 2S Fully charged voltage (4.2V/cell)

#endif // CONFIG_H
