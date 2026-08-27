#ifndef GPS_H
#define GPS_H
#include <Arduino.h>

struct GpsReading {
    float lat;
    float lon;
    float speed;
    float alt;
    int satsVisible;
    int satsUsed;
    float accuracy;
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
    bool valid;
};

bool gpsBegin();
bool gpsRead(GpsReading &out);

#endif