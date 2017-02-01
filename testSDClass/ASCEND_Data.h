// Stephen Flores
// ASCEND_Data.h
// Created 2017/2/1
// Shall replace old function-driven thing with object implementation!

#ifndef ASCEND_Data_h
#define ASCEND_Data_h

#ifndef SD_H
#include "SD.h"
#endif

#ifndef SPI_H
#include "SPI.h"
#endif


class ASCEND_Data {
public:
    ASCEND_Data();
    void init();
    void setFilename(String name);
    void setHeaders(String headers);
    void setPin(int pin);

    void add(float arr[]);   // Add arrays of floats
    void add(int i);         // Add a single int
    void add(float f);       // Add a single float
    void add(String s);      // Add a string, like a log message or something

    void save();             // Commit changes to disk
    void clear();            // Reset dataString without saving.
    bool available();        // Make sure the SD card is available

private:
    int logCounter;
    String filename;
    int sdPin;
    String dataString;

    File dataFile;

    void error();
};

#endif
