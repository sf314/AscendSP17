// Stephen Flores
// test9DOFWriting.ino
// Integrate 9DOF and SD into one!

// NOTE: 9DOF must be powered from 3.3V rail! 5V might break it!

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "ASCEND_Data.h"
#include "ASCEND_IMU9DOF.h"


ASCEND_IMU9DOF imu;

void setup() {
    Serial.begin(9600); // Sparkfun says 11520. Hrmmm. But 11520 Doesn't work, sooo...
    imu.begin();
    SD_init();
    delay(1000);
}


void loop() {
    imu.update();
    double x = imu.accel.x;
    float arr[] = {x, 0, 0};
    SD_add(arr);
    Serial.println(x);
    SD_save();
    delay(500);
}
