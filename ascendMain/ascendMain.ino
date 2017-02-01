// Stephen Flores
// ascendMain.ino
// Main code for ASCEND Spring 2017 payload

// NOTE:
// LSM6DS3 uses 3.3V power
// LSM6DS3 SDA is A4, SCL is A5

// LIBRARIES
    #include "Wire.h"
    #include "SPI.h"
    #include "SD.h"
    #include "ASCEND_Data.h"
    #include "ASCEND_IMU.h"

// GLOBAL VARS
    ASCEND_IMU imu;

// TIME VARS
    int mainDelay = 100; // Wait how long between logs
    long currentTime = 0;
    long previousTime = 0;
    long previousHallTime = 0;
    long startTime = 0;

void setup() {
    Serial.begin(9600);
    imu.begin();
    initSD();

    startTime = millis();
}



void loop() {
    // Check time
    currentTime = millis();

    if (currentTime - previousTime >= mainDelay) {
        // Update sensors
        imu.update();

        // Save sensor data to vars
        float ax = imu.accel.x;
        float ay = imu.accel.y;
        float az = imu.accel.z;
        float gx = imu.gyro.x;
        float gy = imu.gyro.y;
        float gz = imu.gyro.z;
        float temp = imu.temp;

        // Print sensor data (optional)
        Serial.println("accl: " + String(ax) + ", " + String(ay) + ", " + String(az));
        Serial.println("gyro: " + String(gx) + ", " + String(gy) + ", " + String(gz));
        Serial.println("temp: " + String(temp));

        // Log to SD card
        float arr[] = {currentTime, ax, ay, az, gx, gy, gz, temp};
        saveToSD(arr);

        previousTime = currentTime;
    }
}







// *** IGNORE ***
