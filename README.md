# Tamper Evident Community Air Quality Monitor
*ESP32-S3 air quality monitor with GPS-tagged PM readings, SHA-256 hash chaining, and e-paper display*

Air quality data collection which is affordable and accessible as a community monitoring tool, producing data which is verifiable and actionable. SHA-256 Hash chaining on device provides tamper evident logging, while a small footprint, simple UI and intuitive data visualisation ensure real time understanding for everyone.

## Hardware

| Component  | Role/Features |
| ------------- | ------------- |
| LilyGO T-SIM7080G-S3  | ESP32-S3 dev board with GPS modem, power management & MicroSD  |
| Sensirion SEN55  | Environmental Node (PM1.0/2.5/10, humidity, temp, VOC, NOx)  |
| GoodDisplay GDEY027T91  | Low-power 2.7" E-Paper display  |
| DESPI-C02  | Display Adapter Board |
| 18650 battery  | Power source  |
| Rotary Encoder (stretch) | User Navigation  |
| ATECC608A (stretch)  | Hardware key storage for cryptographic signing  |


<img width="722" height="509" alt="hardware block diagram" src="https://github.com/user-attachments/assets/c7a77ed4-a788-44d2-9fd5-984bd49e4590" />

## Wiring

<table>
<tr><th>Display</th><th>GPS Modem</th><th>SEN55 </th><th>SD Reader</th></tr>
<tr><td>

| DESPI-C02  | Pin |
| ------------- | ------------- |
| Busy  | 9  |
| RST  | 45  |
| DC  | 0  |
| CS  | 6  |
| CLK  | 3  |
| DIN  | 46  |
| GND  | GND  |
| PWR  | 3V3  |

</td><td>

| GPS Modem  | Pin |
| ------------- | ------------- |
| SDA  | 15  |
| SCL  | 7  |
| PWR  | 41  |
| RXD  | 4  |
| TXD  | 5  |

</td><td>

| SEN55  | Pin |
| ------------- | ------------- |
| SDA  | 1  |
| SCL  | 2  |
| GND  | GND  |
| PWR  | 3V3  |

</td><td>

| SD Reader  | Pin |
| ------------- | ------------- |
| CMD  | 39  |
| CLK  | 38  |
| DATA  | 40  |

</td></tr> </table>

## Build Instructions

1. Download the latest version of the [Arduino IDE](https://www.arduino.cc/en/software/)
2. Install [arduino-esp32](https://github.com/espressif/arduino-esp32) from espressif
3. Install the following libraries through the Arduino Library Manager:
     - ArduinoJson
     - GxEPD2
     - Sensirion Core
     - Sensirion I2C SEN5X
     - TinyGSM
     - XPowersLib
4. Connect components as per [wiring section](#wiring)
5. Compile .ino and upload to device via USB-C.

## Record and Chain Format

Each record contains location, datetime, PM readings, temperature and humidity and is stored in json: 

```json
{"lat":34.101692,"lon":-118.342979,"time":"2026-09-19T12:42:19Z","prev":"bfe7df29...",
    "pm1p0":12.3,"pm2p5":18.7,"pm10p0":25.1,"humidity":62.4,"temperature":19.8,"hash":"a1b2c3d4..."}
```
The records are hashed and linked in a chain to provide tamper evidence across all records:

<img width="722" height="312" alt="Record Chain Diagram" src="https://github.com/user-attachments/assets/bdbd3c45-972a-4720-ad52-987fd0802d7b" />

## Status

**Working:**
- [x] GPS acquisition via SIM7080G/TinyGSM
- [x] SEN55 sensor readings
- [x] SHA-256 hash chaining with mbedTLS
- [x] JSON record serialisation with ArduinoJson
- [x] Storage to MicroSD

**In progress:**
- [ ] Chain validation tool
- [ ] E-paper display integration

**Planned:**
- [ ] Data Visualisations
- [ ] Display views & rotary encoder display mode switching 
- [ ] Refined error handling
- [ ] Chain recovery on boot
- [ ] 3D-printed weather-resistant enclosure
- [ ] Field & reliability testing
- [ ] Performance tuning

**Stretch:**
- [ ] Companion app
- [ ] ATECC608A hardware key storage for cryptographic signing
