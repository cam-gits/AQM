#ifndef SEN55_H
#define SEN55_H

struct Sen55Reading {
    float pm1p0;
    float pm2p5;
    float pm4p0;
    float pm10p0;
    float humidity;
    float temperature;
    float vocIndex;
    float noxIndex;
    bool valid;
};

void senBegin();
bool senRead(Sen55Reading &out);

#endif