// Stephen Flores
// ASCEND_Sensors.h
// Implement functionality for the LSM6DS3 accel/gyro IMU

#include "ASCEND_IMU.h"

#ifndef ARDUINO_H
#include "Arduino.h"
#endif

#ifndef SPARKFUNLSM6DS3_h
#include "SparkFunLSM6DS3.h"
#endif

float IMU_Vector::mag() {
    return sqrt(x * x + y * y + z * z);
}

// CONSTRUCTOR
ASCEND_IMU::ASCEND_IMU() {
    sparkfunIMU = LSM6DS3();
    accel = IMU_Vector();
    gyro = IMU_Vector();
    temp = 0;
}

// BEGIN
void ASCEND_IMU::begin() {
    sparkfunIMU.begin();
}

// UPDATE (call every loop before accessing accel/gyro objects)
void ASCEND_IMU::update() {
    accel.x = sparkfunIMU.readFloatAccelX();
    accel.y = sparkfunIMU.readFloatAccelY();
    accel.z = sparkfunIMU.readFloatAccelZ();

    gyro.x = sparkfunIMU.readFloatGyroX();
    gyro.y = sparkfunIMU.readFloatGyroY();
    gyro.z = sparkfunIMU.readFloatGyroZ();

    temp = sparkfunIMU.readTempC(); // No Fahrenheit!
}
