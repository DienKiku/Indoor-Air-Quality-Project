#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h> 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <Adafruit_INA219.h>

// --- 1. CẤU HÌNH CHÂN MÀN HÌNH TFT ---
#define TFT_CS   21  
#define TFT_DC   20  
#define TFT_RST  10  
#define TFT_MOSI 9   
#define TFT_SCLK 8   
#define TFT_BL   5   

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// --- 2. CẤU HÌNH I2C (BME680 & INA219) ---
#define I2C_SDA  6
#define I2C_SCL  7

Adafruit_BME680 bme; 
Adafruit_INA219 ina219;

// --- 3. CẤU HÌNH CẢM BIẾN BỤI PM2.5 & LOA BÍP ---
#define DUST_LED_PIN  3  
#define DUST_VO_PIN   4  
#define BUZZER_PIN    2  

// --- MÀU SẮC GIAO DIỆN (RGB565) ---
#define COLOR_BG      0x0000 
#define COLOR_PANEL   0x18E3 
#define COLOR_TEXT    0xFFFF 
#define COLOR_ACCENT  0x03EF 
#define COLOR_WARN    0xF800 

void setup() {
  Serial.begin(115200);
  delay(500);

  Wire.begin(I2C_SDA, I2C_SCL);

  pinMode(DUST_LED_PIN, OUTPUT);
  digitalWrite(DUST_LED_PIN, HIGH);
  analogSetAttenuation(ADC_11db);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); 

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1); // Màn hình nằm ngang
  tft.fillScreen(COLOR_BG);

  drawSplashScreen();

  if (!bme.begin()) {
    tft.fillScreen(COLOR_BG);
    tft.setCursor(10, 50); tft.setTextColor(ST7735_RED);
    tft.println("Loi: Khong thay BME680!");
    while (1);
  }
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);

  if (!ina219.begin()) {
    tft.fillScreen(COLOR_BG);
    tft.setCursor(10, 50); tft.setTextColor(ST7735_RED);
    tft.println("Loi: Khong thay INA219!");
    while (1);
  }

  // Âm thanh khởi động (bíp 2 tiếng)
  digitalWrite(BUZZER_PIN, HIGH); delay(100);
  digitalWrite(BUZZER_PIN, LOW);  delay(100);
  digitalWrite(BUZZER_PIN, HIGH); delay(100);
  digitalWrite(BUZZER_PIN, LOW);

  drawDashboardLayout();
}

void loop() {
  // 1. Đọc BME680
  float temp = 0, humi = 0, gas = 0;
  if (bme.performReading()) {
    temp = bme.temperature;
    humi = bme.humidity;
    gas = bme.gas_resistance ? bme.gas_resistance / 1000.0 : 0;
  }

  // 2. Đọc Bụi PM2.5 (Bộ lọc mượt 5 mẫu)
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
  float dustDensity = (0.17 * avgVoltage - 0.1);
  if (dustDensity < 0) dustDensity = 0.0;

  // 3. Đọc thông số Nguồn từ INA219 (Điện áp, Dòng điện)
  float busvoltage = ina219.getBusVoltage_V(); 
  float current_mA = ina219.getCurrent_mA();   // Lấy dòng điện tiêu thụ (mA)
  
  // Tính % dung lượng pin 2S (Dải đo 2S: 6.0V đến 8.4V)
  float batteryPct = (busvoltage - 6.0) / (8.4 - 6.0) * 100.0;
  if (batteryPct > 100) batteryPct = 100;
  if (batteryPct < 0) batteryPct = 0;

  // 4. Kiểm tra điều kiện cảnh báo loa bíp
  if (dustDensity > 0.15 || batteryPct < 20.0) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200); 
    digitalWrite(BUZZER_PIN, LOW);
  }

  // 5. Cập nhật màn hình
  updateSensorData(temp, humi, dustDensity, gas, busvoltage, current_mA, batteryPct);

  delay(2000); 
}

// ================= CÁC HÀM VẼ GIAO DIỆN =================

void drawSplashScreen() {
  tft.fillScreen(COLOR_BG);
  tft.drawRect(5, 5, tft.width() - 10, tft.height() - 10, COLOR_ACCENT);
  tft.setTextSize(1); tft.setTextColor(ST7735_YELLOW);
  tft.setCursor(20, 30); tft.println("DANH GIA CHAT LUONG");
  tft.setCursor(45, 45); tft.println("KHONG KHI");
  tft.setTextColor(ST7735_CYAN);
  tft.setCursor(35, 75); tft.println("System Starting...");
  delay(1500);
}

void drawDashboardLayout() {
  tft.fillScreen(COLOR_BG);

  // Thanh tiêu đề đề tài
  tft.fillRect(0, 0, tft.width(), 16, COLOR_ACCENT);
  tft.setTextSize(1); tft.setTextColor(ST7735_WHITE);
  tft.setCursor(12, 4); tft.println("DG CHAT LUONG KHONG KHI");

  // Khung 4 ô cảm biến môi trường
  tft.drawRoundRect(2, 18, 76, 42, 4, COLOR_PANEL); // Temp
  tft.drawRoundRect(82, 18, 76, 42, 4, COLOR_PANEL); // Humi
  tft.drawRoundRect(2, 62, 76, 42, 4, COLOR_PANEL); // PM2.5
  tft.drawRoundRect(82, 62, 76, 42, 4, COLOR_PANEL); // Gas

  // Khung thanh trạng thái nguồn điện ở đáy
  tft.drawRoundRect(2, 106, tft.width() - 4, 20, 4, COLOR_PANEL);
}

void updateSensorData(float temp, float humi, float dust, float gas, float batVolt, float current_mA, float batPct) {
  // 1. Nhiệt độ
  tft.fillRect(6, 26, 68, 30, COLOR_BG);
  tft.setTextSize(1); tft.setTextColor(ST7735_WHITE); tft.setCursor(6, 20); tft.print("TEMP");
  tft.setCursor(6, 34); tft.setTextColor(temp > 35.0 ? COLOR_WARN : ST7735_YELLOW);
  tft.print(temp, 1); tft.print(" C");

  // 2. Độ ẩm
  tft.fillRect(86, 26, 68, 30, COLOR_BG);
  tft.setTextColor(ST7735_WHITE); tft.setCursor(86, 20); tft.print("HUMI");
  tft.setCursor(86, 34); tft.setTextColor(ST7735_GREEN);
  tft.print(humi, 1); tft.print(" %");

  // 3. Bụi PM2.5
  tft.fillRect(6, 70, 68, 30, COLOR_BG);
  tft.setTextColor(ST7735_WHITE); tft.setCursor(6, 64); tft.print("PM2.5");
  tft.setCursor(6, 78); tft.setTextColor(dust > 0.15 ? COLOR_WARN : ST7735_CYAN);
  tft.print(dust, 2); tft.setTextSize(1); tft.setCursor(45, 78); tft.print("mg");

  // 4. Khí Gas
  tft.fillRect(86, 70, 68, 30, COLOR_BG);
  tft.setTextColor(ST7735_WHITE); tft.setCursor(86, 64); tft.print("GAS");
  tft.setCursor(86, 78); tft.setTextColor(ST7735_MAGENTA);
  tft.print(gas, 1); tft.setCursor(120, 78); tft.print("kO");

  // 5. Thanh trạng thái Nguồn ở đáy màn hình (Hiển thị V, mA và Icon Pin)
  tft.fillRect(6, 110, tft.width() - 12, 12, COLOR_BG);
  tft.setTextSize(1); tft.setTextColor(ST7735_WHITE);
  tft.setCursor(6, 112);
  
  // Hiển thị điện áp và dòng điện
  tft.print((int)(batVolt * 10) / 10.0); tft.print("V ");
  tft.setTextColor(ST7735_CYAN);
  tft.print((int)current_mA); tft.print("mA");

  // Vẽ Icon cục pin 2S tại góc phải thanh đáy
  int batX = 130, batY = 111, batW = 22, batH = 10;
  tft.drawRect(batX, batY, batW, batH, ST7735_WHITE); // Viền pin
  tft.fillRect(batX + batW, batY + 3, 2, 4, ST7735_WHITE); // Núm đầu pin
  
  // Tính chiều rộng ruột pin theo % của dải 2S (6.0V - 8.4V)
  int fillWidth = (int)((batPct / 100.0) * (batW - 4));
  uint16_t batColor = (batPct < 20) ? COLOR_WARN : ST7735_GREEN;
  
  tft.fillRect(batX + 2, batY + 2, batW - 4, batH - 4, COLOR_BG); // Xóa ruột cũ
  tft.fillRect(batX + 2, batY + 2, fillWidth, batH - 4, batColor); // Vẽ mức pin mới
}