// Stephen Flores
// Test writing 9DOF stuff to the SD card!!!

// *** Libs and stuff
#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include "CSimu.h"
#include "ASCEND_Data.h"
        // #include "DHT.h"

// *** Time control variables *****************
int sensorDelay = 2000;
bool on = false;

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

// *** DHT sensor *****************************
        // #define DHTPIN 2
        // #define DHTPIN2 3
        // #define DHTTYPE 22
        //
        // DHT dht(DHTPIN, DHTTYPE);
        // DHT dht2(DHTPIN2, DHTTYPE);

// *** Objects and stuff
CSimu imu = CSimu();


void setup() {
    delay(1000);
    Serial.begin(9600);
    Wire.begin();
    pinMode(13, OUTPUT);

    // Initializations!
    imu.config();
    SD_init();
            // dht.begin();
            // dht2.begin();
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

void loop() {
    currentTime = millis();
    if (currentTime - previousTime > sensorDelay) {
        imu.updateSensors();

        SD_add(currentTime);

        float f = imu.accel.x; saveF(f);
        f = imu.accel.y; saveF(f);              // 9DOF board
        f = imu.accel.z; saveF(f);

        f = imu.gyro.x; saveF(f);
        f = imu.gyro.y; saveF(f);
        f = imu.gyro.z; saveF(f);

        f = imu.mag.x; saveF(f);
        f = imu.mag.y; saveF(f);
        f = imu.mag.z; saveF(f);

        f = imu.altitude; saveF(f);
        f = imu.temperature; saveF(f);

                // float dht_humi = dht.readHumidity(); saveF(dht_humi); // DHT 1
                // float dht_temp = dht.readTemperature(); saveF(dht_temp);
                // float dht_tfhr = dht.readTemperature(true); saveF(dht_tfhr);
                // f = dht.computeHeatIndex(dht_tfhr, dht_humi); saveF(f);
                // f = dht.computeHeatIndex(dht_temp, dht_humi, false); saveF(f);
                //
                // float dht_humi2 = dht2.readHumidity(); saveF(dht_humi2); // DHT 1
                // float dht_temp2 = dht2.readTemperature(); saveF(dht_temp2);
                // float dht_tfhr2 = dht2.readTemperature(true); saveF(dht_tfhr2);
                // f = dht2.computeHeatIndex(dht_tfhr2, dht_humi2); saveF(f);
                // f = dht2.computeHeatIndex(dht_temp2, dht_humi2, false); saveF(f);

        // Now for anemometer things

        sensorValue = analogRead(sensorPin);
        sensorVoltage = sensorValue * voltageConversionConstant;

        sensorValue2 = analogRead(sensorPin2);
        sensorVoltage2 = sensorValue2 * voltageConversionConstant;

        //if (sensorVoltage <= voltageMin) { windSpeed = 0; }//Check if voltage is below minimum value. If so, set wind speed to zero.
        //else { windSpeed = ((sensorVoltage - voltageMin) * windSpeedMax / (voltageMax - voltageMin)*2.23694); }

        //if (sensorVoltage2 <= voltageMin){ windSpeed2 = 0; }//Check if voltage is below minimum value. If so, set wind speed to zero.
        //else { windSpeed2 = ((sensorVoltage2 - voltageMin) * windSpeedMax / (voltageMax - voltageMin)*2.23694); }

        x = windSpeed;
        if (x >= y)   { y = x; }
        else          { y = y; }

        x2 = windSpeed2;
        if (x2 >= y2) { y2 = x2; }
        else          { y2 = y2; }

        saveF(windSpeed);
        saveF(sensorVoltage);

        saveF(windSpeed2);
        saveF(sensorVoltage2);


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




// ********** FUNCS FOR STUFF ***********
void saveF(float val) {
    // Only save to 2 decimal places?
    float rounded = (float)((int)(val * 100)) / 100.0;
    SD_add(val);
    Serial.print(val);
    Serial.print(", ");
}
