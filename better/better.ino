// Stephen Flores
// Test writing 9DOF stuff to the SD card!!!

// *** Libs and stuff
#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include "CSimu.h"
#include "ASCEND_Data.h"

// *** Time control variables *****************
int sensorDelay = 2000;
bool on = false;
CSimu imu = CSimu();

// *** Setup vars for anemometer **************
double x = 0, y = 0;
const int sensorPin = A1;
int sensorValue = 0;
float sensorVoltage = 0, windSpeed = 0;

double x2 = 0, y2 = 0;
const int sensorPin2 = A1;
int sensorValue2 = 0;
float sensorVoltage2 = 0, windSpeed2 = 0;

float voltageConversionConstant = 0.004882814;
float voltageMin = 0.4;
float voltageMax = 2.0;

float windSpeedMin = 0;
float windSpeedMax = 32;


void setup() {
    delay(1000);
    Serial.begin(9600);
    Wire.begin();
    pinMode(13, OUTPUT);

    // Initializations!
    imu.config();
    SD_init();
    delay(1000);

    // Check SD:
    Serial.println("Is SD available?" + String(SD_available()));

    // Set ground altitude (current alt)
    imu.updateSensors();
    imu.setGroundAltitude(imu.altitude);

    Serial.println("Running test...");
    delay(1000);
}

long currentTime = 0;
long previousTime = 0;
int count = 0;

void loop() {
    currentTime = millis();
    if (currentTime - previousTime > sensorDelay) {
        Serial.println(count); count++;
        imu.updateSensors();

        SD_add(currentTime);

        SD_add(imu.accel.x);
        SD_add(imu.accel.y);
        SD_add(imu.accel.z);
        SD_add(imu.gyro.x);
        SD_add(imu.gyro.y);
        SD_add(imu.gyro.z);
        SD_add(imu.mag.x);
        SD_add(imu.mag.y);
        SD_add(imu.mag.z);
        SD_add(imu.altitude);
        SD_add(imu.temperature);

        sensorValue = analogRead(sensorPin);
        sensorVoltage = sensorValue * voltageConversionConstant;

        sensorValue2 = analogRead(sensorPin2);
        sensorVoltage2 = sensorValue2 * voltageConversionConstant;

        if (sensorVoltage <= voltageMin) { windSpeed = 0; }//Check if voltage is below minimum value. If so, set wind speed to zero.
        else { windSpeed = ((sensorVoltage - voltageMin) * windSpeedMax / (voltageMax - voltageMin)*2.23694); }

        if (sensorVoltage2 <= voltageMin){ windSpeed2 = 0; }//Check if voltage is below minimum value. If so, set wind speed to zero.
        else { windSpeed2 = ((sensorVoltage2 - voltageMin) * windSpeedMax / (voltageMax - voltageMin)*2.23694); }

        x = windSpeed;
        if (x >= y)   { y = x; }
        else          { y = y; }

        x2 = windSpeed2;
        if (x2 >= y2) { y2 = x2; }
        else          { y2 = y2; }

        SD_add(windSpeed);
        SD_add(sensorVoltage);
        SD_add(windSpeed2);
        SD_add(sensorVoltage2);

        SD_save();

        Serial.println();

        previousTime = currentTime;

        if (on) {
            digitalWrite(13, LOW);
            on = false;
        } else {
            digitalWrite(13, HIGH);
            on = true;
        }
    }
}
