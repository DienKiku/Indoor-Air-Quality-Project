# 03. Circuit Schematics & Pinout Mapping

## 1. Pin Assignment Table

The ESP32-C3 Super Mini features 11 exposed GPIO pins. Below is the optimized pin mapping designed to avoid bus conflicts and ensure stable high-speed SPI and I2C operations:

| ESP32-C3 Pin | Connected Component | Component Pin | Function / Protocol | Description |
| :--- | :--- | :--- | :--- | :--- |
| **GPIO 8** | BME680 & INA219 | SDA | I2C Data (SDA) | Shared I2C data line (with 4.7k$\Omega$ pull-ups) |
| **GPIO 9** | BME680 & INA219 | SCL | I2C Clock (SCL) | Shared I2C clock line (with 4.7k$\Omega$ pull-ups) |
| **GPIO 6** | 1.8" ST7735 TFT | SDA / MOSI | Hardware SPI MOSI | Display data transmission |
| **GPIO 4** | 1.8" ST7735 TFT | SCL / SCK | Hardware SPI Clock | Display clock signal |
| **GPIO 7** | 1.8" ST7735 TFT | CS | SPI Chip Select | Display active-low selection |
| **GPIO 10** | 1.8" ST7735 TFT | DC / A0 | Data / Command | Selects display command vs display data |
| **GPIO 3** | 1.8" ST7735 TFT | RES / RST | Reset | Display hardware reset line |
| **GPIO 5** | 1.8" ST7735 TFT | BL / LED | Backlight Control | Backlight enable / PWM dimming |
| **GPIO 1** | Sharp GP2Y1010AU0F | Pin 3 (LED) | Digital Output | Pulses infrared emitter diode (IRED) |
| **GPIO 0** | Sharp GP2Y1010AU0F | Pin 5 ($V_o$) | Analog Input (ADC1_CH0) | Reads scattered light analog voltage |
| **GPIO 2** | TMB09A05 Buzzer | Base of NPN BJT | Digital / PWM Output | Triggers acoustic alarm |
| **5V (VIN)** | AMS1117-5.0V | VOUT | Power Input | Supplies regulated 5V to MCU board |
| **3.3V** | BME680, INA219, TFT | VCC / VDD | Power Output | 3.3V rail from on-board LDO |
| **GND** | All Modules | GND | Common Ground | System-wide reference ground |

---

## 2. Sensor Interfacing Schematics

### 2.1. Sharp GP2Y1010AU0F Wiring
The Sharp GP2Y1010AU0F requires an external RC circuit to drive its internal infrared LED:
- **Pin 1 ($V_{LED}$):** Connected to +5V through a $150 \Omega$ resistor (1/2W). A $220 \mu F$ capacitor is placed between Pin 1 and GND to buffer high-current pulses.
- **Pin 2 ($LED\text{-}GND$):** Connected to Common GND.
- **Pin 3 ($LED$):** Connected to ESP32-C3 **GPIO 1**. When driven LOW, the internal IRED is activated.
- **Pin 4 ($S\text{-}GND$):** Connected to Common GND.
- **Pin 5 ($V_o$):** Analog output voltage, connected directly to ESP32-C3 **GPIO 0** (ADC1_CH0).
- **Pin 6 ($V_{cc}$):** Connected to +5V regulated rail.

```
       +5V Rail -------------------+
                                   |
                                 [150R]
                                   |
                                   +------- Pin 1 (V_LED)
                                   |
                                 [220uF]
                                   |
       GND ------------------------+------- Pin 2 (LED-GND)
                                   |
       ESP32-C3 GPIO 1 -------------------- Pin 3 (LED Drive)
       GND -------------------------------- Pin 4 (S-GND)
       ESP32-C3 GPIO 0 (ADC) -------------- Pin 5 (V_o Output)
       +5V Rail --------------------------- Pin 6 (V_cc)
```

### 2.2. INA219 Power Sense Wiring
- **VIN+:** Connected to the positive terminal of the 2S 5A BMS output ($7.4V - 8.4V$).
- **VIN-:** Connected to the input of the AMS1117-5.0V voltage regulator.
- **VCC:** Connected to 3.3V rail.
- **GND:** Connected to Common GND.
- **SDA:** Connected to ESP32-C3 **GPIO 8**.
- **SCL:** Connected to ESP32-C3 **GPIO 9**.

### 2.3. Active Buzzer Circuit (TMB09A05)
Because the ESP32-C3 GPIO pins supply up to ~20 mA at 3.3V and the TMB09A05 requires 5V with ~30-40 mA peak current, an NPN switching transistor (2N2222 or SS8050) is used:
- **Collector:** Connected to Buzzer negative pin (-).
- **Buzzer positive pin (+):** Connected to +5V rail.
- **Emitter:** Connected to Common GND.
- **Base:** Connected to ESP32-C3 **GPIO 2** through a $1 k\Omega$ current-limiting resistor.
- A flyback diode (1N4148) is placed in anti-parallel across the buzzer terminals to suppress inductive voltage spikes.

---

## 3. Power Distribution Diagram

```
[USB Type-C 5V Input]
         |
         v
[Type-C to 2S 8.4V Boost Charger]
         |
         v
[2x 18650 Li-ion Cells (2S1P)] <---> [2S 5A BMS Board]
                                              |
                                              v  Pack Output (7.4V - 8.4V)
                                       [INA219 Sense (VIN+ -> VIN-)]
                                              |
                                              v
                                      [AMS1117-5.0V Module]
                                              |
                      +-----------------------+-----------------------+
                      | 5.0V Rail                                     | 5.0V Rail
                      v                                               v
            [ESP32-C3 VIN pin]                             [GP2Y1010AU0F & Buzzer]
                      |
                      v (On-board LDO)
                 3.3V Logic Rail
                      |
        +-------------+-------------+
        |                           |
        v                           v
  [Bosch BME680]          [ST7735 1.8" TFT]
```
