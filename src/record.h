#ifndef RECORD_H
#define RECORD_H

#include "hashing.h"
#include <Arduino.h>

extern const uint8_t GENESIS_HASH[HASH_SIZE];

struct record {
    uint8_t previousHash[HASH_SIZE];
    float lat;
    float lon;
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
    uint8_t hash[HASH_SIZE];
};

#endif