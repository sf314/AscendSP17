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

int counter = 0;
void loop() {
    Serial.println(counter); counter++;
    imu.update();

    SD_add(millis());

    // 9DOF
    //float arr[] = {imu.accel.x, imu.accel.y, imu.accel.z, imu.gyro.x, imu.gyro.y, imu.gyro.z, imu.mag.x, imu.mag.y, imu.mag.z};
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
    SD_add(imu.temp);



    SD_save();
    delay(500);
}
