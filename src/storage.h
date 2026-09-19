#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#include <FS.h>

void sdBegin();
void appendFile(fs::FS &fs, const char *path, const char *message);

#endif