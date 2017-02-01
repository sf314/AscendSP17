// Stephen Flores
// ASCEND_Data.cpp
// Created 2017/2/1
// Implementation of new ASCEND_Data object!

#include "ASCEND_Data.h"
#include "Arduino.h"
#include "SPI.h"
#include "SD.h"

// CONSTRUCTOR
ASCEND_Data::ASCEND_Data() {
    int logCounter = 1;
    filename = "default.csv";
    sdPin = 8;
    dataString = "";
}

// *** ERROR DEFINITION
void ASCEND_Data::error() {
    Serial.println("\t*** Error accessing SD card *** ");
}

// *** SETTERS
void ASCEND_Data::setFilename(String name) {
    filename = name;
}

void ASCEND_Data::setPin(int pin) {
    sdPin = pin;
}

void ASCEND_Data::clear() {
    dataString = "";
}

// *** DATA MANIPULATION
void ASCEND_Data::add(int i) {
    dataString += String(i) + ", ";
}

void ASCEND_Data::add(String s) {
    dataString += s + ", ";
}

void ASCEND_Data::add(float f) {
    dataString += String(f) + ", ";
}

void ASCEND_Data::add(float arr[]) {
    int size = sizeof(arr);

    for (int i = 0; i < size; i++) {
        dataString += String(arr[i]) + ", ";
    }
}

// *** SAVE DATASTRING TO SD CARD
void ASCEND_Data::save() {
    dataFile = SD.open(filename, FILE_WRITE);
    if (dataFile) {
        dataFile.println(String(logCounter) + ", " + dataString);
    } else {
        error();
    }
}

// *** CHECK AVAILABILITY OF SD CARD
bool ASCEND_Data::available() {
    dataFile = SD.open(filename);
    if (dataFile) {
        dataFile.close();
        return true;
    } else {
        error();
        return false;
    }
}


// *** INITIALIZER
void ASCEND_Data::init() {
    Serial.print("ASCEND_Data::init(): \n\tInitializing SD card...");

    int tries = 3;
    while (!SD.begin(sdPin) && tries > 0) {
        Serial.print(".");
        tries--;
        delay(500);
    }
    Serial.println("\tAttempted initialization on pin " + String(sdPin));

    Serial.println("\tChecking if file is accessible...");
    dataFile = SD.open(filename);
    delay(100);
    if (dataFile) {
        Serial.println("\tFile is accessible");
        dataFile.close();
    } else {
        error();
    }
}

void ASCEND_Data::setHeaders(String headers) {
    dataFile = SD.open(filename, FILE_WRITE);
    if (dataFile) {
        dataFile.println(headers);
        dataFile.close();
    } else {
        error();
    }
}
