#include "sen55.h"
#include "pins.h"
#include <Wire.h>
#include <SensirionI2CSen5x.h>

SensirionI2CSen5x sen5x;

void senBegin() {
  Wire.begin(1, 2);
  sen5x.begin(Wire);
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
    out.valid = sen5x.readMeasuredValues(&out.pm1p0, &out.pm2p5, &out.pm4p0, &out.pm10p0,&out.humidity, &out.temperature, &out.vocIndex, &out.noxIndex);
    return out.valid;
}