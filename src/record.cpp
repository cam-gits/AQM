#include "record.h"

const uint8_t GENESIS_HASH[HASH_SIZE] = {0};

size_t serialiseRecordJson(const record &r, char *outbuf, size_t buff, bool includeHash) {
  char previousHex[HASH_SIZE * 2 + 1];
  hashToHex(r.previousHash, previousHex);

  char timestamp[24];
  snprintf(timestamp, sizeof(timestamp), "%04d-%02d-%02dT%02d:%02d:%02dZ", r.year, r.month, r.day, r.hour, r.min, r.sec);

  JsonDocument doc;

  doc["lat"] = r.lat;
  doc["lon"] = r.lon;
  doc["time"]  = timestamp;
  doc["prev"] = previousHex;

  if (includeHash) {
    char hashHex[HASH_SIZE * 2 + 1];
    hashToHex(r.hash, hashHex);
    doc["hash"] = hashHex;
  }

  return serializeJson(doc, outbuf, buff);

}