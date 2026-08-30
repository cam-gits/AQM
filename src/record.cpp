#include "record.h"

const uint8_t GENESIS_HASH[HASH_SIZE] = {0};

size_t searialiseRecord(const record &r, char *outbuf, size_t buff) {
  char previousHex[HASH_SIZE *2 + 1];
  hashToHex(r.previousHash, previousHex);

  int readable = snprintf(outbuf, buff, "%.5f | %.5f | %02d-%02d-%04d | %02d:%02d:%02d | %s", r.lat, r.lon, r.day, r.month, r.year, r.hour, r.min, r.sec, previousHex);

  return (size_t)readable;

}