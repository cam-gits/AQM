#include "src/GPS.h"
#include "src/hashing.h"
#include "src/pins.h"

void setup() {
  Serial.begin(115200);

  if(gpsBegin() == false){
    Serial.println("GPS Initialising");
    while (1) delay (5000);
  }

  const char *payload = "Test string for validation";
  
  uint8_t shaResult[HASH_SIZE];
  hashRecord((const uint8_t *)payload, strlen(payload), shaResult);
  char hex[HASH_SIZE * 2 + 1];
  hashToHex(shaResult, hex);

  Serial.print("Hash: ");
  Serial.println(hex);
}

void loop() {
  GpsReading gps;

  if (gpsRead(gps)){
    Serial.printf("Fix: %.5f, %.5f\n", gps.lat, gps.lon);
  }

  delay(5000);
}
