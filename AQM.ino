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

    record rec = {};
    char hex[HASH_SIZE * 2 + 1];
    char serialised[256];

    rec.lat = gps.lat;
    rec.lon = gps.lon;
    rec.year = gps.year;
    rec.month = gps.month;
    rec.day = gps.day;
    rec.hour = gps.hour;
    rec.min = gps.min;
    rec.sec = gps.sec;
    memcpy(rec.previousHash, lastRec.hash, HASH_SIZE);

    int serialLen = searialiseRecord(rec, serialised, sizeof(serialised));
    
    hashToHex(rec.previousHash, hex);

    Serial.print("Record:\n");
    Serial.println(serialised);

    hashRecord((uint8_t *)&serialised, serialLen, rec.hash);
    hashToHex(rec.hash, hex);

    Serial.print("\nHash: ");
    Serial.println(hex);

    lastRec = rec;
  }
  
  delay(5000);
}
