#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include "ASCEND_GPS.h"
#include "ASCEND_Data.h"

void setup() {
    Serial.begin(9600);
    delay(500);
    Serial.println("Starting test...");
    SD_init();
    GPS_begin();
    delay(1000);
}

void loop() {
    SD_add((int)millis());
    String gpsOutput = GPS_getSentence();
    SD_add(gpsOutput);
    Serial.println(gpsOutput);
    SD_save();
    delay(1000);
}
