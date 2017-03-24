// Stephen Flores
// SDWrite.h
// Created 2017/2/2
// Function-driven SDWrite

#ifndef SDWrite_h
#define SDWrite_h

#include <SPI.h>
#include <SD.h>

// DEFINITIONS: EDIT THESE
#define filename "flight.csv"
#define headers "Time, ax, ay, az, gx, gy, gz, mx, my, mz, alt, temp, h1, t1, f1, hif1, hic1, h2, h2, f2, hif2, hic2, w1, v1, w2, v2"
#define sdPin 10


// VARIABLES
File dataFile;
String dataString;

// // FILE funcs
// void SD_setFilename(String s) {
//     filename = s;
// }

// ERROR PRINTING
void SD_error() {
    Serial.println("\t\t\t*** Error: cannot access SD ***");
}

// DATA MANIPULATION
void SD_add(int i) {
    dataString += String(i) + ", ";
}

void SD_add(long l) { // Added for millis() for ASCEND!
    dataString += String(l) + ", ";
}

void SD_add(String s) {
    dataString += s + ", ";
}

void SD_add(float f) {
    dataString += String(f) + ", ";
}

template<size_t N>
void SD_add(float (&arr)[N]) {
    //int size = sizeof(arr) / sizeof(arr[0]);
    size_t size = N;
    //Serial.println("array size" + String(N));
    for (int i = 0; i < size; i++) {
        dataString += String(arr[i]) + ", ";
    }
}

void SD_save() {
    dataFile = SD.open(filename, FILE_WRITE);
    if (dataFile) {
        dataFile.println(dataString);
        dataString = "";
        dataFile.close();
    }
}

bool SD_available() {
    dataFile = SD.open(filename);
    if (dataFile) {
        dataFile.close();
        return true;
    } else {
        SD_error();
        return false;
    }
}


// INITIALIZER
void SD_init() {
    // *** SD setup:
        Serial.println("Initializing SD card...");

        int tries = 3;
        while (!SD.begin(sdPin) && tries > 0) {
            Serial.print(".");
            tries--;
            delay(1000);
        }
        Serial.println("Attempted initialization on pin " + String(sdPin));

        dataFile = SD.open(filename, FILE_WRITE);
        if (dataFile) {
            Serial.println("Writing SD headers...");
            dataFile.println(headers);
            dataFile.close();
        } else {
            Serial.println("File could not be opened. Headers not written");
        }

        dataFile = SD.open(filename);
        Serial.println("Checking if file is accessible...");
        delay(100);
        if (dataFile) {
            Serial.println("File is accessible");
            dataFile.close();
        } else {
            Serial.println("***** Error: file inaccessible *****");
        }
}


#endif
