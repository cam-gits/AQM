#include <SD_MMC.h>

#include "src/GPS.h"
#include "src/hashing.h"
#include "src/pins.h"
#include "src/record.h"
#include "src/sen55.h"
#include "src/storage.h"

record lastRec = {};

void setup() {
  Serial.begin(115200);

  if(gpsBegin() == false){
    Serial.println("GPS Initialising");
    while (1) delay (5000);
  }

  //SD to boot after GPS, needs to set working voltage after modem power cycle
  sdBegin();
  senBegin();

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

    if (senRead(sen)){
      rec.pm1p0 = sen.pm1p0;
      rec.pm2p5 = sen.pm2p5;
      rec.pm10p0 = sen.pm10p0;
      rec.humidity = sen.humidity;
      rec.temperature = sen.temperature;
    }

    size_t jsonLen = serialiseRecordJson(rec, serialised, sizeof(serialised), false); hashRecord((uint8_t *)serialised, jsonLen, rec.hash);

    char jsonForStorage[512];
    serialiseRecordJson(rec, jsonForStorage, sizeof(jsonForStorage), true);
    appendFile(SD_MMC, RECORD_PATH, jsonForStorage);
    appendFile(SD_MMC, RECORD_PATH, "\n");

    Serial.println(jsonForStorage);

    hashToHex(rec.hash, hex);
    Serial.print("\nHash: ");
    Serial.println(hex);

    lastRec = rec;
  }
  
  delay(5000);
}