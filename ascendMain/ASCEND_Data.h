// Stephen Flores
// ASCEND_Data.h
// Purpose: just functions for saving to SD card (and event logging?)

// NOTE:
// Be sure to adjust saveToSD() to get the correct # of arguments

#ifndef ARDUINO_H
#include "Arduino.h"
#endif

#ifndef SPI_H
#include <SPI.h>
#endif

#ifndef SD_h
#include <SD.h>
#endif

File dataFile;
String fileName = "datalog.csv";
String headers = "Time, ax, ay, az, gx, gy, gz, temp, etc";
int sdPin = 8;

void initSD() {
    // *** SD setup:
        Serial.println("Initializing SD card...");

        int tries = 3;
        while (!SD.begin(sdPin) && tries > 0) {
            Serial.print(".");
            tries--;
            delay(1000);
        }
        Serial.println("Attempted initialization on pin 8");

        dataFile = SD.open(fileName, FILE_WRITE);
        if (dataFile) {
            Serial.println("Writing SD headers...");
            dataFile.println(headers);
            dataFile.close();
        } else {
            Serial.println("File could not be opened. Headers not written");
        }

        dataFile = SD.open(fileName);
        Serial.println("Checking if file is accessible...");
        delay(100);
        if (dataFile) {
            Serial.println("File is accessible");
            dataFile.close();
        } else {
            Serial.println("***** Error: file inaccessible *****");
        }
}

void saveToSD(long time, double a, double b, double c, double d) {
    String dataString = String(time) + ", " + String(a) + ", " + String(b) + ", " + String(c) + ", " + String(d);
    dataFile = SD.open(fileName, FILE_WRITE);
    if (dataFile) {
        //Serial.print("\t\t\t\t\tSaving to SD card: "); Serial.println(dataString);
        dataFile.println(dataString);
        dataFile.close(); // I am dumb.
    } else {
        Serial.println("\t\t\t\t\tError: Could not write to SD!");
    }
}

void saveToSD(float arr[]) {
    // Saving by passing an array!
    int size = sizeof(arr);
    dataFile = SD.open(fileName, FILE_WRITE);

    if (dataFile) {
        String dataString = "";

        for (int i = 0; i < size; i++) {
            dataString += arr[i];
            dataString += ", ";
        }

        dataFile.println(dataString);
        dataFile.close();
    } else {
        Serial.println("\t\t\t\t\tError: Could not write to SD!");
    }
}
