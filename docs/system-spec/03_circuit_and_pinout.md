# 03. Circuit Schematics & Pinout Mapping

## 1. Visual Circuit Schematic Diagram

Below is the complete hardware schematic diagram generated from the verified KiCad engineering schematic (`hardware/schematics/1.kicad_sch`):

![Hardware Circuit Schematic](../../hardware/schematics/circuit_schematic.png)

---

## 2. Verified Pin Assignment Table

The hardware prototype board connects the ESP32-C3 Super Mini to all peripherals using the verified pin mapping below:

| ESP32-C3 Pin | Connected Peripheral | Peripheral Pin | Interface / Protocol | Functional Description |
| :--- | :--- | :--- | :--- | :--- |
| **GPIO 6** | BME680 & INA219 | SDA | Hardware I2C (SDA) | Shared bi-directional I2C serial data line |
| **GPIO 7** | BME680 & INA219 | SCL | Hardware I2C (SCL) | Shared I2C serial clock line |
| **GPIO 9** | 1.8" ST7735 TFT | SDA / MOSI | Hardware SPI (MOSI) | Serial display pixel data input |
| **GPIO 8** | 1.8" ST7735 TFT | SCL / SCK | Hardware SPI (SCK) | Serial display clock signal |
| **GPIO 21** | 1.8" ST7735 TFT | CS | Digital Output (SPI CS) | Display active-low chip select |
| **GPIO 20** | 1.8" ST7735 TFT | DC / A0 | Digital Output (Data/Cmd)| Data/Command selection pin |
| **GPIO 10** | 1.8" ST7735 TFT | RES / RST | Digital Output (Reset) | Display hardware reset line |
| **GPIO 5** | 1.8" ST7735 TFT | BLK / LED | Digital Output / PWM | Backlight enable & brightness control |
| **GPIO 3** | Sharp GP2Y1010AU0F | Pin 3 (LED) | Digital Output (Active LOW)| Pulses infrared emitting diode (IRED) |
| **GPIO 4** | Sharp GP2Y1010AU0F | Pin 5 ($V_o$) | Analog Input (ADC1_CH4) | Scaled analog voltage from optical dust chamber |
| **GPIO 2** | Acoustic Buzzer Circuit| Base of Q1 (2SC1815)| Digital Output (HIGH=ON)| Drives active buzzer via NPN transistor |
| **5V (VIN)** | AMS1117-5.0V LDO | VOUT | Power Input (+5.0V) | Main regulated power rail to MCU board |
| **3.3V** | BME680, INA219, TFT | VCC / VDD | Power Rail (+3.3V) | Logic supply rail from ESP32-C3 onboard LDO |
| **GND** | All Modules | GND | Common System Ground | Common 0V reference ground across all circuits |

---

## 3. Sensor Interfacing Schematics

### 3.1. Sharp GP2Y1010AU0F Wiring
The Sharp GP2Y1010AU0F requires an external RC pulse driving network and a voltage divider:
- **Pin 1 ($V_{LED}$):** Connected to +5V through a $150 \Omega$ or $240 \Omega$ current-limiting resistor with a $220 \mu F$ bypass capacitor to GND.
- **Pin 2 ($LED\text{-}GND$):** Connected to Common GND.
- **Pin 3 ($LED$):** Connected to ESP32-C3 **GPIO 3** (`DUST_LED_PIN`). Driven LOW for $280\mu s$ before ADC sampling.
- **Pin 4 ($S\text{-}GND$):** Connected to Common GND.
- **Pin 5 ($V_o$):** Analog output voltage, routed through a resistive voltage divider to scale to $\le 3.3V$ and read via ESP32-C3 **GPIO 4** (`DUST_VO_PIN`).
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
