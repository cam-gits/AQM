#include "storage.h"
#include "pins.h"

#include <Arduino.h>
#include <FS.h>
#include <SD_MMC.h>
#include <stdio.h>
#define XPOWERS_CHIP_AXP2101
#include "XPowersLib.h"

XPowersPMU PMU;

void appendFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if (!file) {
        Serial.println("Failed to open file for appending");
        return;
    }
    if (file.print(message)) {
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }

    file.close();
}

void sdBegin(){
    PMU.setALDO3Voltage(3300);   // SD Card VDD 3300
    PMU.enableALDO3();
    PMU.disableTSPinMeasure();

    SD_MMC.setPins(SDMMC_CLK, SDMMC_CMD, SDMMC_DATA); 

        if (!SD_MMC.begin("/sdcard", true)) {
        Serial.println("Card Mount Failed");
        while (1) {
            delay(1000);
        }

    }

    uint8_t cardType = SD_MMC.cardType();
    if (cardType == CARD_NONE) {
        Serial.println("No SD_MMC card attached");
        while (1) {
            delay(1000);
        }
    }
        Serial.print("SD_MMC Card Type: ");
    if (cardType == CARD_MMC) {
        Serial.println("MMC");
    } else if (cardType == CARD_SD) {
        Serial.println("SDSC");
    } else if (cardType == CARD_SDHC) {
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
    Serial.printf("SD_MMC Card Size: %lluMB\n", cardSize);
    
}