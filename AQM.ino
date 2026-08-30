#include "src/GPS.h"
#include "src/hashing.h"
#include "src/pins.h"
#include "src/record.h"

record lastRec = {};

void setup() {
  Serial.begin(115200);

  if(gpsBegin() == false){
    Serial.println("GPS Initialising");
    while (1) delay (5000);
  }

  memcpy(lastRec.hash, GENESIS_HASH, HASH_SIZE);
}

void loop() {
  GpsReading gps;

  if (gpsRead(gps)){
    Serial.printf("Latitude: %.5f, Longitude: %.5f\n", gps.lat, gps.lon);

    record rec = {};

    rec.lat = gps.lat;
    rec.lon = gps.lon;
    rec.year = gps.year;
    rec.month = gps.month;
    rec.day = gps.day;
    rec.hour = gps.hour;
    rec.min = gps.min;
    rec.sec = gps.sec;
    memcpy(rec.previousHash, lastRec.hash, HASH_SIZE);

    hashRecord((uint8_t *)&rec, sizeof(rec) - sizeof(rec.hash), rec.hash);
    char hex[HASH_SIZE * 2 + 1];
    hashToHex(rec.hash, hex);

    Serial.print("Hash: ");
    Serial.println(hex);

    lastRec = rec;
  }
  
  delay(5000);
}
