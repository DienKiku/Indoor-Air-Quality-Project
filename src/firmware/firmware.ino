#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h> 
#include <SPI.h>
#include <Wire.h>
#include "esp_wifi.h" 
#include <Adafruit_Sensor.h>
#include <bsec2.h>          
#include <Adafruit_INA219.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// File cấu hình thông tin Wi-Fi và Google Firebase Realtime Database
#include "firebase_config.h"

// ==========================================
// 1. CẤU HÌNH CHÂN MÀN HÌNH TFT (ST7735 1.8")
// ==========================================
#define TFT_CS   21  
#define TFT_DC   20  
#define TFT_RST  10  
#define TFT_MOSI 9   
#define TFT_SCLK 8   
#define TFT_BL   5   

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// ==========================================
// 2. CẤU HÌNH I2C & BSEC2 (BME680 & INA219)
// ==========================================
#define I2C_SDA  6
#define I2C_SCL  7

Bsec2 bsecClient; 
Adafruit_INA219 ina219;

// ==========================================
// 3. CẤU HÌNH CẢM BIẾN BỤI PM2.5 & CÒI BÍP
// ==========================================
#define DUST_LED_PIN  3  
#define DUST_VO_PIN   4  
#define BUZZER_PIN    2  

// ==========================================
// 4. MÀU SẮC GIAO DIỆN (RGB565)
// ==========================================
#define COLOR_BG      0x0000 
#define COLOR_PANEL   0x18E3 
#define COLOR_TEXT    0xFFFF 
#define COLOR_ACCENT  0x03EF 
#define COLOR_WARN    0xF800 

// ==========================================
// 5. CẤU HÌNH CHU KỲ CẬP NHẬT & TIẾT KIỆM PIN
// ==========================================
unsigned long lastUpdate      = 0;
unsigned long lastHistoryPush = 0;

const unsigned long UPDATE_INTERVAL  = 5000;    // 30 giây
const unsigned long HISTORY_INTERVAL = 1800000;  // 30 phút

bool wifiConnected = false;

// Biến lưu trữ giá trị đo
float curTemp = 25.0, curHumi = 50.0, curPres = 1013.0, curGas = 50.0, curDust = 0.0, curIAQ = 25.0;
float curCo2Eq = 400.0, curVocPct = 100.0;
uint8_t curIaqAccuracy = 0; // 0 = dang hieu chuan, 1-2 = tam on, 3 = da hieu chuan day du
float curBatVolt = 7.4, curCurrent_mA = 0.0, curBatPct = 50.0;

WiFiClientSecure *sslClient = nullptr;

// ==========================================
// PROTOTYPES
// ==========================================
void drawSplashScreen();
void drawDashboardLayout();
void updateSensorData();
void checkBsecStatus(Bsec2 bsec);
// Khai báo hàm callback đúng chuẩn prototype của bsec2.h
void myBsecCallback(const bme68xData data, const bsecOutputs outputs, const Bsec2 bsec);
void pushCurrentToFirebase();
void pushHistoryToFirebase();

// ==========================================
// BSEC2 CALLBACK CHUẨN TỪ BOSCH LIBRARY
// ==========================================
void myBsecCallback(const bme68xData data, const bsecOutputs outputs, const Bsec2 bsec) {
  for (uint8_t i = 0; i < outputs.nOutputs; i++) {
    const bsecData output = outputs.output[i];
    switch (output.sensor_id) {
      case BSEC_OUTPUT_IAQ:
        curIAQ = output.signal;
        curIaqAccuracy = output.accuracy; // 0-3, dung de biet gia tri IAQ da dang tin chua
        break;
      case BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE:
        curTemp = output.signal;
        break;
      case BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY:
        curHumi = output.signal;
        break;
      case BSEC_OUTPUT_CO2_EQUIVALENT:
        curCo2Eq = output.signal;
        break;
      case BSEC_OUTPUT_BREATH_VOC_EQUIVALENT:
        curVocPct = constrain(100.0 - (output.signal / 5.0), 0.0, 100.0);
        break;
      case BSEC_OUTPUT_GAS_ESTIMATE_1:
        curGas = output.signal / 1000.0; // Ohm sang kOhm
        break;
      case BSEC_OUTPUT_RAW_PRESSURE:
        Serial.println("[DEBUG] RAW_PRESSURE signal goc: " + String(output.signal)); // TAM THOI de kiem tra don vi that
        curPres = output.signal; // output.signal cua BSEC_OUTPUT_RAW_PRESSURE da la hPa, khong chia lai
        break;
      default:
        break;
    }
  }
}

// Kiểm tra lỗi trạng thái của BSEC2
void checkBsecStatus(Bsec2 bsec) {
  if (bsec.status < BSEC_OK) {
    Serial.println("[BSEC ERROR] Mã lỗi thuật toán BSEC: " + String(bsec.status));
  } else if (bsec.status > BSEC_OK) {
    Serial.println("[BSEC WARN] Cảnh báo BSEC: " + String(bsec.status));
  }
  // Mã lỗi tầng cảm biến/I2C (BME68X) - đây mới thường là nguyên nhân thật
  // khi begin() thất bại (sai địa chỉ I2C, dây SDA/SCL, cảm biến không ACK...)
  if (bsec.sensor.status < BME68X_OK) {
    Serial.println("[BME68X ERROR] Mã lỗi cảm biến/I2C: " + String(bsec.sensor.status));
  } else if (bsec.sensor.status > BME68X_OK) {
    Serial.println("[BME68X WARN] Cảnh báo cảm biến: " + String(bsec.sensor.status));
  }
}

// ==========================================
// SETUP
// ==========================================
void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  btStop();  
  delay(100);
  esp_wifi_set_max_tx_power(WIFI_POWER_8_5dBm); 
  delay(1500); 

  Serial.println(F("\n\n========================================"));
  Serial.println(F("[BOOT] IAQ Monitor (BSEC2) - Starting..."));
  Serial.printf("[BOOT] Free heap: %u bytes\n", ESP.getFreeHeap());
  Serial.println(F("========================================"));

  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(50000);
  Wire.setTimeOut(100);

  pinMode(DUST_LED_PIN, OUTPUT);
  digitalWrite(DUST_LED_PIN, HIGH);
  analogSetAttenuation(ADC_11db);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); 

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(COLOR_BG);
  drawSplashScreen();

  // Khởi tạo BSEC2 với Wire và địa chỉ I2C thực tế đo được qua I2C scanner: 0x77
  if (!bsecClient.begin(BME68X_I2C_ADDR_HIGH, Wire)) {
    checkBsecStatus(bsecClient);
    tft.fillScreen(COLOR_BG);
    tft.setCursor(10, 50); tft.setTextColor(ST7735_RED);
    tft.println("Loi: Khoi tao BSEC2 that bai!");
    while (1) { delay(1000); }
  }

  // Đăng ký các thông số ảo cần trích xuất từ thư viện BSEC2
  bsec_virtual_sensor_t sensorList[] = {
    BSEC_OUTPUT_IAQ,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
    BSEC_OUTPUT_RAW_PRESSURE,
    BSEC_OUTPUT_CO2_EQUIVALENT,
    BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
    BSEC_OUTPUT_GAS_ESTIMATE_1,
    BSEC_OUTPUT_RUN_IN_STATUS,
    BSEC_OUTPUT_STABILIZATION_STATUS
  };

  bsecClient.updateSubscription(sensorList, ARRAY_LEN(sensorList), BSEC_SAMPLE_RATE_LP);
  bsecClient.attachCallback(myBsecCallback);

  // Khởi tạo INA219
  if (!ina219.begin()) {
    tft.fillScreen(COLOR_BG);
    tft.setCursor(10, 50); tft.setTextColor(ST7735_RED);
    tft.println("Loi: Khong thay INA219!");
    while (1) { delay(1000); }
  }

  digitalWrite(BUZZER_PIN, HIGH); delay(100);
  digitalWrite(BUZZER_PIN, LOW);  delay(100);

  drawDashboardLayout();

  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  unsigned long wifiStart = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - wifiStart) < 10000) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected = true;
    configTime(7 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  }

  sslClient = new WiFiClientSecure;
  if (sslClient) {
    sslClient->setInsecure();
    sslClient->setTimeout(5);
  }

  drawDashboardLayout();
  lastUpdate      = millis();
  lastHistoryPush = millis();
  
  Serial.println(F("[SYSTEM] ===== HE THONG SAN SANG (BSEC2 ACTIVE) =====\n"));
}

// ==========================================
// LOOP
// ==========================================
void loop() {
  // BSEC2 bắt buộc phải chạy hàm run() liên tục trong vòng lặp
  if (!bsecClient.run()) {
    checkBsecStatus(bsecClient);
  }

  unsigned long now = millis();

  if (now - lastUpdate >= UPDATE_INTERVAL) {
    lastUpdate = now;
    
    // Đọc cảm biến bụi PM2.5
    float sumVoltage = 0;
    int sampleCount = 5;
    for (int i = 0; i < sampleCount; i++) {
      digitalWrite(DUST_LED_PIN, LOW);  
      delayMicroseconds(280);           
      int rawValue = analogRead(DUST_VO_PIN); 
      delayMicroseconds(40);            
      digitalWrite(DUST_LED_PIN, HIGH); 
      delayMicroseconds(9680);          
      sumVoltage += (rawValue * 3.3 / 4095.0) * 1.5; 
      delay(5);
    }
    float avgVoltage = sumVoltage / sampleCount;
    float calcDust = (0.17 * avgVoltage - 0.1);
    curDust = (calcDust < 0) ? 0.0 : calcDust;

    // Đọc INA219 nguồn pin
    float v = ina219.getBusVoltage_V(); 
    float c = ina219.getCurrent_mA();
    if (!isnan(v) && v > 0.1) {
      curBatVolt    = v;
      curCurrent_mA = c;
      if (curBatVolt >= 6.0) {
        curBatPct = constrain(((curBatVolt - 6.4) / (8.4 - 6.4)) * 100.0, 0.0, 100.0);
      } else {
        curBatPct = 0.0; 
      }
    }

    if (curDust > 0.075) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100); 
      digitalWrite(BUZZER_PIN, LOW);
    }

    updateSensorData();

    Serial.printf("[SENSOR] T:%.1fC | H:%.1f%% | P:%.1fhPa | PM25:%.3f | IAQ:%.0f | CO2:%.0fppm | Bat:%.2fV\n",
                  curTemp, curHumi, curPres, curDust, curIAQ, curCo2Eq, curBatVolt);

    if (WiFi.status() == WL_CONNECTED) {
      pushCurrentToFirebase();
    }
  }

  if (now - lastHistoryPush >= HISTORY_INTERVAL) {
    lastHistoryPush = now;
    if (WiFi.status() == WL_CONNECTED) {
      pushHistoryToFirebase();
    }
  }

  delay(10); 
}

// ==========================================
// ĐẨY DỮ LIỆU HIỆN TẠI (CURRENT) LÊN FIREBASE
// ==========================================
void pushCurrentToFirebase() {
  time_t epochTime = time(nullptr);
  
  const char* iaqStatus = "EXCELLENT";
  if      (curIAQ > 300) iaqStatus = "HAZARDOUS";
  else if (curIAQ > 200) iaqStatus = "MODERATELY_POLLUTED";
  else if (curIAQ > 100) iaqStatus = "LIGHTLY_POLLUTED";
  else if (curIAQ > 50)  iaqStatus = "GOOD";
  else                   iaqStatus = "EXCELLENT";

  bool isAlert = (curDust > 0.075 || curIAQ > 200 || (curBatVolt >= 6.0 && curBatPct < 20.0));
  const char* alertReason = "NONE";
  if (curDust > 0.075 && curIAQ > 200) alertReason = "HIGH_PM25_HIGH_IAQ";
  else if (curDust > 0.075)            alertReason = "HIGH_PM25";
  else if (curIAQ > 200)               alertReason = "HIGH_POLLUTION";
  else if (curBatVolt >= 6.0 && curBatPct < 20.0) alertReason = "LOW_BATTERY";
  
  char jsonBuf[512];
  snprintf(jsonBuf, sizeof(jsonBuf),
    "{\"device_id\":\"%s\",\"timestamp\":%ld,"
    "\"environment\":{\"temperature_c\":%.1f,\"humidity_pct\":%.1f,\"pressure_hpa\":%.1f,"
    "\"gas_resistance_kohm\":%.1f,\"voc_quality_pct\":%.0f,\"co2_equivalent_ppm\":%.0f,\"pm25_mg_m3\":%.3f,\"iaq_index\":%.0f,\"iaq_status\":\"%s\"},"
    "\"power\":{\"bus_voltage_v\":%.2f,\"current_ma\":%.1f,\"power_mw\":%.1f,\"battery_percentage\":%d},"
    "\"alerts\":{\"is_alert\":%s,\"alert_reason\":\"%s\"}}",
    DEVICE_ID, (long)epochTime,
    curTemp, curHumi, curPres, curGas, curVocPct, curCo2Eq, curDust, curIAQ, iaqStatus,
    curBatVolt, curCurrent_mA, curBatVolt * curCurrent_mA, (int)curBatPct,
    isAlert ? "true" : "false", alertReason
  );
  
  String url = String(FIREBASE_HOST) + "iaq_stations/" + DEVICE_ID + "/current.json?auth=" + FIREBASE_AUTH;
  
  if (sslClient) {
    HTTPClient http;
    http.setReuse(false); 
    http.setTimeout(5000);
    if (http.begin(*sslClient, url)) {
      http.addHeader("Content-Type", "application/json");
      http.PUT((uint8_t*)jsonBuf, strlen(jsonBuf));
      http.end();
    }
  }
}

// ==========================================
// GHI LỊCH SỬ (HISTORY) LÊN FIREBASE (30 PHÚT)
// ==========================================
void pushHistoryToFirebase() {
  time_t epochTime = time(nullptr);
  
  char histBuf[256];
  snprintf(histBuf, sizeof(histBuf),
    "{\"timestamp\":%ld,\"temperature_c\":%.1f,\"humidity_pct\":%.1f,\"pressure_hpa\":%.1f,"
    "\"pm25_mg_m3\":%.3f,\"gas_resistance_kohm\":%.1f,\"iaq_index\":%.0f,\"battery_percentage\":%d}",
    (long)epochTime, curTemp, curHumi, curPres, curGas, curIAQ, (int)curBatPct
  );
  
  String histUrl = String(FIREBASE_HOST) + "iaq_stations/" + DEVICE_ID + "/history.json?auth=" + FIREBASE_AUTH;
  
  if (sslClient) {
    HTTPClient http;
    http.setReuse(false);
    http.setTimeout(5000);
    if (http.begin(*sslClient, histUrl)) {
      http.addHeader("Content-Type", "application/json");
      http.POST((uint8_t*)histBuf, strlen(histBuf));
      http.end();
    }
  }
}

// ==========================================
// VẼ GIAO DIỆN MÀN HÌNH ST7735 (160x128)
// ==========================================
void drawSplashScreen() {
  tft.fillScreen(COLOR_BG);
  tft.drawRect(5, 5, tft.width() - 10, tft.height() - 10, COLOR_ACCENT);
  tft.setTextSize(1); tft.setTextColor(ST7735_YELLOW);
  tft.setCursor(20, 30); tft.println("DANH GIA CHAT LUONG");
  tft.setCursor(30, 45); tft.println("KHONG KHI (BSEC2)");
  tft.setTextColor(ST7735_CYAN);
  tft.setCursor(35, 75); tft.println("System Starting...");
  delay(1500);
}

void drawDashboardLayout() {
  tft.fillScreen(COLOR_BG);
  tft.fillRect(0, 0, tft.width(), 14, COLOR_ACCENT);
  tft.setTextSize(1); tft.setTextColor(ST7735_WHITE);
  tft.setCursor(14, 3); tft.println("DG CHAT LUONG KHONG KHI");

  tft.drawRoundRect(2,  16, 76, 28, 3, COLOR_PANEL); 
  tft.drawRoundRect(82, 16, 76, 28, 3, COLOR_PANEL); 
  tft.drawRoundRect(2,  46, 76, 28, 3, COLOR_PANEL); 
  tft.drawRoundRect(82, 46, 76, 28, 3, COLOR_PANEL); 
  tft.drawRoundRect(2,  76, 76, 28, 3, COLOR_PANEL); 
  tft.drawRoundRect(82, 76, 76, 28, 3, COLOR_PANEL); 
  tft.drawRoundRect(2, 106, tft.width() - 4, 20, 3, COLOR_PANEL);
}

void updateSensorData() {
  // 1. Ô Nhiệt độ
  tft.fillRect(4, 18, 72, 24, COLOR_BG);
  tft.setTextSize(1); tft.setTextColor(ST7735_WHITE); tft.setCursor(6, 18); tft.print("TEMP");
  tft.setCursor(6, 29); tft.setTextColor(curTemp > 35.0 ? COLOR_WARN : ST7735_YELLOW);
  tft.print(curTemp, 1); tft.print(" C");

  // 2. Ô Độ ẩm
  tft.fillRect(84, 18, 72, 24, COLOR_BG);
  tft.setTextColor(ST7735_WHITE); tft.setCursor(86, 18); tft.print("HUMI");
  tft.setCursor(86, 29); tft.setTextColor(ST7735_GREEN);
  tft.print(curHumi, 1); tft.print(" %");

  // 3. Ô Bụi PM2.5
  tft.fillRect(4, 48, 72, 24, COLOR_BG);
  tft.setTextColor(ST7735_WHITE); tft.setCursor(6, 48); tft.print("PM2.5");
  tft.setCursor(6, 59); tft.setTextColor(curDust > 0.075 ? COLOR_WARN : ST7735_CYAN);
  tft.print(curDust, 2); tft.print("mg");

  // 4. Ô Khí Gas VOC
  tft.fillRect(84, 48, 72, 24, COLOR_BG);
  tft.setTextColor(ST7735_WHITE); tft.setCursor(86, 48); tft.print("GAS");
  tft.setCursor(86, 59); tft.setTextColor(ST7735_MAGENTA);
  tft.print(curGas, 1); tft.print("kO");

  // 5. Ô Áp suất khí quyển
  tft.fillRect(4, 78, 72, 24, COLOR_BG);
  tft.setTextColor(ST7735_WHITE); tft.setCursor(6, 78); tft.print("PRES");
  tft.setCursor(6, 89); tft.setTextColor(0x9DFF); 
  tft.print((int)curPres); tft.print("hPa");

  // 6. Ô Chỉ số IAQ Index (Từ BSEC2)
  tft.fillRect(84, 78, 72, 24, COLOR_BG);
  tft.setTextColor(ST7735_WHITE); tft.setCursor(86, 78); tft.print("IAQ");
  tft.setCursor(86, 89);
  
  uint16_t iaqColor = ST7735_GREEN;
  const char* iaqLabel = "TUYET";
  if      (curIAQ > 300) { iaqColor = COLOR_WARN;    iaqLabel = "NGUY"; }
  else if (curIAQ > 200) { iaqColor = 0xFA20;        iaqLabel = "KEM";  }
  else if (curIAQ > 100) { iaqColor = 0xFD20;        iaqLabel = "TB";   }
  else if (curIAQ > 50)  { iaqColor = ST7735_YELLOW; iaqLabel = "TOT";  }
  else                   { iaqColor = ST7735_GREEN;  iaqLabel = "EXC";  }

  tft.setTextColor(iaqColor);
  tft.print((int)curIAQ); tft.print(" "); tft.print(iaqLabel);
  // Danh dau * khi cam bien chua hieu chuan day du (accuracy < 3) de biet so lieu con dang "chay"
  if (curIaqAccuracy < 3) { tft.print("*"); }

  // 7. Thanh nguồn pin dưới đáy
  tft.fillRect(4, 108, tft.width() - 8, 16, COLOR_BG);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(6, 112);
  
  tft.print(curBatVolt, 1); tft.print("V ");
  tft.setTextColor(ST7735_CYAN);
  tft.print((int)curCurrent_mA); tft.print("mA ");

  uint16_t batColor = ST7735_GREEN;
  if (curBatPct < 20) batColor = COLOR_WARN;
  else if (curBatPct < 50) batColor = ST7735_YELLOW;

  tft.setTextColor(batColor);
  tft.print((int)curBatPct); tft.print("%");

  int batX = 126, batY = 110, batW = 26, batH = 12;
  int innerW = batW - 4; 
  int innerH = batH - 4; 

  tft.drawRect(batX, batY, batW, batH, ST7735_WHITE);
  tft.fillRect(batX + batW, batY + 3, 2, 6, ST7735_WHITE);
  
  int fillWidth = constrain((int)round((curBatPct / 100.0) * innerW), 0, innerW);
  tft.fillRect(batX + 2, batY + 2, innerW, innerH, COLOR_BG);
  if (fillWidth > 0) {
    tft.fillRect(batX + 2, batY + 2, fillWidth, innerH, batColor);
  }
}