// Stephen Flores
// testSDClass.ino
// For testing the awesome new implementation of data saving!

// LIBRARIES
    //#include "Arduino.h"
    #include "SPI.h"
    #include "SD.h"
    #include "ASCEND_Data.h"

// OBJECTS
    ASCEND_Data sd;


void setup() {
    Serial.begin(9600);

    sd.setPin(8);
    sd.setFilename("testSD.txt");
    sd.init();

    delay(1000);

    Serial.print("Is SD available?\t");
    Serial.println(sd.available());
}

void loop() {
    float thing[] = {1, 2, 3, 4, 5};
    sd.add(thing);
    sd.save();

    delay(1000);
}
