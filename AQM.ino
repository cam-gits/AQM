#include "gps.h"
#include "hashing.h"
#include "pins.h"

void setup() {
  Serial.begin(115200);

  const char *payload = "Test string for validation";
  
  uint8_t shaResult[HASH_SIZE];
  hashRecord((const uint8_t *)payload, strlen(payload), shaResult);
  char hex[HASH_SIZE * 2 + 1];
  hashToHex(shaResult, hex);

  Serial.print("Hash: ");
  Serial.println(hex);
}

void loop() {
  // put your main code here, to run repeatedly:

}
