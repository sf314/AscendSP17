// Stephen Flores
// testSDClass.ino
// For testing the awesome new implementation of data saving!

// LIBRARIES
    //#include "Arduino.h"
    #include "SPI.h"
    #include "SD.h"
    #include "ASCEND_Data.h"


void setup() {
    Serial.begin(9600);

    sd.setFilename("testSD.txt");
    SD_init();

    delay(1000);

    Serial.print("Is SD available?\t");
    Serial.println();
}

void loop() {
    float thing[] = {1, 2, 3, 4, 5};
    SD_add(thing);
    SD_save();

    delay(1000);
}
