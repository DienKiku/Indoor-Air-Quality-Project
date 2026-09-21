#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_BME680.h>
#include <Adafruit_INA219.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#include "config.h"

// Check if actual credentials file exists; otherwise use fallback definitions
#if __has_include("firebase_config.h")
    #include "firebase_config.h"
#else
    #define WIFI_SSID       "Aeduongso8"
    #define WIFI_PASSWORD   "20022003"
    #define FIREBASE_HOST   "https://iaq-project-57a4f-default-rtdb.asia-southeast1.firebasedatabase.app/"
    #define FIREBASE_AUTH   "CIX0VQNsdwG4iaeeTnJqAW9VH1q79wumwuPuUZ49"
    #define DEVICE_ID       "ESP32C3_STATION_01"
#endif

// ==========================================
// GLOBAL OBJECTS & DRIVERS
// ==========================================
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS_PIN, TFT_DC_PIN, TFT_MOSI_PIN, TFT_SCLK_PIN, TFT_RST_PIN);
Adafruit_BME680 bme;
Adafruit_INA219 ina219;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig fbConfig;

// ==========================================
// SENSOR TELEMETRY STATE
// ==========================================
struct TelemetryData {
    float temperature = 0.0f;
    float humidity = 0.0f;
    float pressure = 0.0f;
    float gas_resistance_kohm = 0.0f;
    float pm25_ugm3 = 0.0f;
    float bus_voltage_v = 0.0f;
    float current_ma = 0.0f;
    float power_mw = 0.0f;
    int   battery_pct = 0;
    bool  alarm_active = false;
} currentData;

// Moving average buffer for optical dust sensor
#define MA_SIZE 10
float dustBuffer[MA_SIZE] = {0.0f};
int   dustBufferIndex = 0;
bool  dustBufferFull = false;

// Task scheduler timestamps
unsigned long lastSensorReadTime = 0;
unsigned long lastTftUpdateTime = 0;
unsigned long lastCloudSyncTime = 0;

// ==========================================
// FUNCTION PROTOTYPES
// ==========================================
void initHardware();
void connectWiFi();
void initFirebase();
float readSharpDustSensor();
void readEnvironmentalSensors();
void readPowerSensors();
void updateTFTDisplay();
void syncToFirebase();
void evaluateAlerts();

// ==========================================
// SETUP & INITIALIZATION
// ==========================================
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println(F("\n=========================================="));
    Serial.println(F("  Indoor Air Quality & Energy IoT Station "));
    Serial.println(F("=========================================="));

    initHardware();
    connectWiFi();
    initFirebase();

    Serial.println(F("[SYSTEM] Initialization complete. Starting main loop..."));
}

// ==========================================
// MAIN LOOP (NON-BLOCKING SCHEDULER)
// ==========================================
void loop() {
    unsigned long now = millis();

    // 1. Periodic Sensor Acquisition
    if (now - lastSensorReadTime >= INTERVAL_SENSOR_MS) {
        lastSensorReadTime = now;
        readEnvironmentalSensors();
        readPowerSensors();
        evaluateAlerts();
    }

    // 2. Periodic Display Refresh
    if (now - lastTftUpdateTime >= INTERVAL_TFT_MS) {
        lastTftUpdateTime = now;
        updateTFTDisplay();
    }

    // 3. Periodic Cloud Telemetry Sync
    if (now - lastCloudSyncTime >= INTERVAL_CLOUD_MS) {
        lastCloudSyncTime = now;
        syncToFirebase();
    }
}

// ==========================================
// HARDWARE INITIALIZATION
// ==========================================
void initHardware() {
    // 1. Configure GPIOs
    pinMode(DUST_LED_PIN, OUTPUT);
    digitalWrite(DUST_LED_PIN, HIGH); // Active LOW for IRED
    analogSetAttenuation(ADC_11db);   // Full scale ADC ~3.3V

    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);

    pinMode(TFT_BL_PIN, OUTPUT);
    digitalWrite(TFT_BL_PIN, HIGH); // Backlight ON

    // 2. Initialize I2C Bus
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

    // 3. Initialize BME680
    if (!bme.begin(0x77)) {
        if (!bme.begin(0x76)) {
            Serial.println(F("[WARN] BME680 sensor not found on 0x77 or 0x76!"));
        } else {
            Serial.println(F("[OK] BME680 initialized on 0x76"));
        }
    } else {
        Serial.println(F("[OK] BME680 initialized on 0x77"));
    }

    // Configure BME680 oversampling and filter
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320°C for 150 ms

    // 4. Initialize INA219
    if (!ina219.begin()) {
        Serial.println(F("[WARN] INA219 current sensor not found at 0x40!"));
    } else {
        Serial.println(F("[OK] INA219 initialized successfully."));
    }

    // 5. Initialize 1.8" ST7735 TFT
    tft.initR(INITR_BLACKTAB);
    tft.setRotation(1); // Landscape mode (160x128)
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);
    tft.setCursor(10, 20);
    tft.println("IAQ Station Booting...");
}

// ==========================================
// NETWORK & CLOUD SETUP
// ==========================================
void connectWiFi() {
    Serial.printf("[WIFI] Connecting to %s", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("\n[WIFI] Connected! IP: %s\n", WiFi.localIP().toString().c_str());
    } else {
        Serial.println(F("\n[WIFI] Failed to connect. Operating in offline edge mode."));
    }
}

void initFirebase() {
    if (WiFi.status() != WL_CONNECTED) return;

    Serial.println(F("[FIREBASE] Initializing Firebase client..."));
    fbConfig.host = FIREBASE_HOST;
    fbConfig.signer.tokens.legacy_token = FIREBASE_AUTH;

    Firebase.begin(&fbConfig, &auth);
    Firebase.reconnectWiFi(true);
    Serial.println(F("[FIREBASE] Configuration established."));
}

// ==========================================
// SENSOR READING IMPLEMENTATIONS
// ==========================================
float readSharpDustSensor() {
    float sumVoltage = 0.0f;
    int sampleCount = 5;
    for (int i = 0; i < sampleCount; i++) {
        digitalWrite(DUST_LED_PIN, LOW);
        delayMicroseconds(DUST_PULSE_WAIT_US);
        int rawValue = analogRead(DUST_ANALOG_PIN);
        delayMicroseconds(DUST_SAMPLE_WAIT_US);
        digitalWrite(DUST_LED_PIN, HIGH);
        delayMicroseconds(DUST_SLEEP_WAIT_US);
        sumVoltage += (rawValue * 3.3f / 4095.0f) * DUST_VOLTAGE_RATIO;
        delay(5);
    }
    float avgVoltage = sumVoltage / sampleCount;
    float dustDensity_mgm3 = (0.17f * avgVoltage - 0.1f);
    if (dustDensity_mgm3 < 0.0f) dustDensity_mgm3 = 0.0f;

    // Convert mg/m3 to ug/m3 for telemetry (1 mg/m3 = 1000 ug/m3)
    return dustDensity_mgm3 * 1000.0f;
}

void readEnvironmentalSensors() {
    // Optical PM2.5
    currentData.pm25_ugm3 = readSharpDustSensor();

    // BME680 Acquisition
    if (bme.performReading()) {
        currentData.temperature = bme.temperature;
        currentData.humidity = bme.humidity;
        currentData.pressure = bme.pressure / 100.0f; // hPa
        currentData.gas_resistance_kohm = bme.gas_resistance / 1000.0f; // kOhm
    }
}

void readPowerSensors() {
    // INA219 Acquisition
    currentData.bus_voltage_v = ina219.getBusVoltage_V();
    currentData.current_ma = ina219.getCurrent_mA();
    currentData.power_mw = ina219.getPower_mW();

    // Calculate remaining battery percentage for 2S pack (6.0V to 8.4V)
    float pct = (currentData.bus_voltage_v - BATTERY_MIN_VOLTS) / (BATTERY_MAX_VOLTS - BATTERY_MIN_VOLTS) * 100.0f;
    if (pct > 100.0f) pct = 100.0f;
    if (pct < 0.0f) pct = 0.0f;
    currentData.battery_pct = (int)pct;
}

void evaluateAlerts() {
    bool alarm = false;

    // Evaluate PM2.5 threshold (0.15 mg/m3 = 150 ug/m3)
    if (currentData.pm25_ugm3 >= (PM25_WARN_MGM3 * 1000.0f)) {
        alarm = true;
    }
    // Evaluate Critical Low Battery (< 20%)
    if (currentData.battery_pct > 0 && currentData.battery_pct < BATTERY_WARN_PCT) {
        alarm = true;
    }
    // Evaluate High Temperature (> 35°C)
    if (currentData.temperature > TEMP_WARN_C) {
        alarm = true;
    }

    currentData.alarm_active = alarm;

    // Trigger Buzzer
    if (alarm) {
        digitalWrite(BUZZER_PIN, HIGH);
    } else {
        digitalWrite(BUZZER_PIN, LOW);
    }
}

// ==========================================
// GRAPHICAL USER INTERFACE (ST7735)
// ==========================================
void updateTFTDisplay() {
    tft.fillScreen(ST77XX_BLACK);

    // 1. Status Bar Header
    uint16_t headerColor = currentData.alarm_active ? ST77XX_RED : ST77XX_BLUE;
    tft.fillRect(0, 0, 160, 18, headerColor);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);
    tft.setCursor(4, 5);
    tft.print("IAQ: ");
    if (currentData.alarm_active) {
        tft.print("WARNING / HAZARDOUS");
    } else if (currentData.pm25_ugm3 < PM25_WARN_UGM3) {
        tft.print("OPTIMAL (GOOD)");
    } else {
        tft.print("MODERATE");
    }

    // 2. PM2.5 Dust Density (Prominent Metric)
    tft.setCursor(4, 26);
    tft.setTextColor(ST77XX_YELLOW);
    tft.setTextSize(1);
    tft.print("PM2.5 Dust: ");
    tft.setTextSize(2);
    tft.setCursor(4, 38);
    tft.print(currentData.pm25_ugm3, 1);
    tft.setTextSize(1);
    tft.print(" ug/m3");

    // 3. Environmental Parameters (Temp / Hum / Press / VOC)
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(4, 60);
    tft.printf("Temp: %.1f C  Hum: %.1f %%", currentData.temperature, currentData.humidity);

    tft.setCursor(4, 74);
    tft.printf("Press: %.0f hPa", currentData.pressure);

    tft.setCursor(4, 88);
    tft.printf("VOC Gas: %.1f kOhm", currentData.gas_resistance_kohm);

    // 4. Power & Battery Status Footer
    tft.drawFastHLine(0, 104, 160, ST77XX_DARKGREY);
    tft.setCursor(4, 110);
    tft.setTextColor(currentData.battery_pct < 20 ? ST77XX_RED : ST77XX_GREEN);
    tft.printf("Bat: %.2fV (%d%%) | %.0fmA", currentData.bus_voltage_v, currentData.battery_pct, currentData.current_ma);
}

// ==========================================
// CLOUD SYNCHRONIZATION (GOOGLE FIREBASE)
// ==========================================
void syncToFirebase() {
    if (WiFi.status() != WL_CONNECTED || !Firebase.ready()) return;

    FirebaseJson json;
    json.set("timestamp", (int)time(nullptr));
    json.set("environment/temperature_c", currentData.temperature);
    json.set("environment/humidity_pct", currentData.humidity);
    json.set("environment/pressure_hpa", currentData.pressure);
    json.set("environment/gas_resistance_kohm", currentData.gas_resistance_kohm);
    json.set("environment/pm25_ug_m3", currentData.pm25_ugm3);
    json.set("environment/iaq_status", currentData.alarm_active ? "HAZARDOUS" : "GOOD");

    json.set("power/bus_voltage_v", currentData.bus_voltage_v);
    json.set("power/current_ma", currentData.current_ma);
    json.set("power/power_mw", currentData.power_mw);
    json.set("power/battery_percentage", currentData.battery_pct);

    json.set("alerts/is_alert", currentData.alarm_active);
    json.set("alerts/alert_reason", currentData.alarm_active ? "POLLUTION_OR_LOW_BATTERY" : "NONE");

    String nodePath = "/iaq_stations/" + String(DEVICE_ID) + "/current";
    if (Firebase.RTDB.setJSON(&fbdo, nodePath.c_str(), &json)) {
        Serial.printf("[FIREBASE] Telemetry synced to %s\n", nodePath.c_str());
    } else {
        Serial.printf("[FIREBASE] Sync error: %s\n", fbdo.errorReason().c_str());
    }
}
