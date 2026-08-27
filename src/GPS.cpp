#include "gps.h"
#include "pins.h"

#define XPOWERS_CHIP_AXP2101
#include "XPowersLib.h"

#define TINY_GSM_RX_BUFFER 1024
#define SerialAT Serial1
#define TINY_GSM_MODEM_SIM7080
#include <TinyGsmClient.h>

static XPowersPMU PMU;
static TinyGsm modem(SerialAT);

bool gpsBegin() {
    if (PMU.begin(Wire, AXP2101_SLAVE_ADDRESS, I2C_SDA, I2C_SCL) == false) {
        return false;
    }

    if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_UNDEFINED) {
        PMU.disableDC3();
        delay(200);
    }

    PMU.setDC3Voltage(3000);
    PMU.enableDC3();
    PMU.setBLDO2Voltage(3300);
    PMU.enableBLDO2();
    PMU.disableTSPinMeasure();

    Serial1.begin(115200, SERIAL_8N1, BOARD_MODEM_RXD_PIN, BOARD_MODEM_TXD_PIN);
    pinMode(BOARD_MODEM_PWR_PIN, OUTPUT);
    digitalWrite(BOARD_MODEM_PWR_PIN, LOW);
    delay(100);
    digitalWrite(BOARD_MODEM_PWR_PIN, HIGH);
    delay(1000);
    digitalWrite(BOARD_MODEM_PWR_PIN, LOW);

    int retry = 0;
    while (modem.testAT(1000) == false) {
        if (retry++ > 15) {
            digitalWrite(BOARD_MODEM_PWR_PIN, LOW);
            delay(100);
            digitalWrite(BOARD_MODEM_PWR_PIN, HIGH);
            delay(1000);
            digitalWrite(BOARD_MODEM_PWR_PIN, LOW);
            retry = 0;
        }
    }

    if (modem.enableGPS() == false) {
        return false;
    }

    return true;
}

bool gpsRead(GpsReading &out) {
    out.valid = modem.getGPS(&out.lat, &out.lon, &out.speed, &out.alt, &out.satsVisible, &out.satsUsed, &out.accuracy, &out.year, &out.month, &out.day, &out.hour, &out.min, &out.sec);
    return out.valid;
}