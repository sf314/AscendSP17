// Stephen Flores
// testSDClass.ino
// For testing the awesome new implementation of data saving!
// Pins:
// 5V to 5V, GND to GND
// CLK to pin 13, DO to pin 12
// DI to pin 11, CS to pin 10

// LIBRARIES
    //#include "Arduino.h"
    #include "SPI.h"
    #include "SD.h"
    #include "ASCEND_Data.h"


void setup() {
    Serial.begin(9600);

    //SD_setFilename("testSD.txt");
    SD_init();

    delay(1000);

    Serial.print("Is SD available?\t");
    Serial.println(SD_available());
}

void loop() {
    float thing[] = {1, 2, 3, 4, 5};
    SD_add(thing);
    SD_save();

    delay(1000);
}
