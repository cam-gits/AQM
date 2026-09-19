#include "sen55.h"
#include "pins.h"
#include <Wire.h>
#include <SensirionI2CSen5x.h>

SensirionI2CSen5x sen5x;

void senBegin() {
    //Sen on Wire1 as two I2C busses in action
    Wire1.begin(SEN55_SDA, SEN55_SCL);
    sen5x.begin(Wire1);

    uint16_t error = sen5x.deviceReset();

    if (error) {
        char errorMessage[256];
        errorToString(error, errorMessage, 256);
        Serial.print("Error starting SEN55: ");
        Serial.println(errorMessage);
        return;
    }
    delay(100);

    error = sen5x.startMeasurement();
    if (error) {
        Serial.println("Error starting measurement!");
    }

    Serial.println("SEN55 Environmental Sensor Node Live");
}

bool senRead(Sen55Reading &out) {
    uint16_t error = sen5x.readMeasuredValues(out.pm1p0, out.pm2p5, out.pm4p0, out.pm10p0, out.humidity, out.temperature, out.vocIndex, out.noxIndex);
    out.valid = (error == 0);
    return out.valid;
}