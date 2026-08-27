#ifndef HASHING_H
#define HASHING_H

#include <Arduino.h>

#define HASH_SIZE 32

void hashRecord(const uint8_t *payload, size_t payloadLength, uint8_t *output);
void hashToHex(const uint8_t *hash, char *hexOut);

#endif