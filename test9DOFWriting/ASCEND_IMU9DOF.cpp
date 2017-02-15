// Implementation;


#ifndef ARDUINO_H
#include "Arduino.h"
#endif

#ifndef SparkFunLSM9DS1_h
#include "SparkFunLSM9DS1.h"
#include "SparkFunLSM9DS1.h"
#include "LSM9DS1_Registers.h"
#include "LSM9DS1_Types.h"
#endif

#include "ASCEND_IMU9DOF.h"

float IMU_Vector::magnitude() {
    return sqrt(x * x + y * y + z * z);
}

// CONSTRUCTOR
ASCEND_IMU9DOF::ASCEND_IMU9DOF() {
    sparkfunIMU = LSM9DS1();
    accel = IMU_Vector();
    gyro = IMU_Vector();
}

// BEGIN
void ASCEND_IMU9DOF::begin() {
    //sparkfunIMU.settings.device.commInterface = IMU_MODE_I2C;
    //sparkfunIMU.settings.device.mAddress = LSM9DS1_M;
    //sparkfunIMU.settings.device.agAddress = LSM9DS1_AG;
    sparkfunIMU.begin();
}

// UPDATE (call every loop before accessing accel/gyro objects)
void ASCEND_IMU9DOF::update() {
    sparkfunIMU.readGyro();
    sparkfunIMU.readAccel();
    sparkfunIMU.readMag();
    sparkfunIMU.readTemp();

    //accel.x = sparkfunIMU.ax;
    accel.y = sparkfunIMU.ay;
    accel.z = sparkfunIMU.az;
    accel.x = sparkfunIMU.calcAccel(sparkfunIMU.ax);

    gyro.x = sparkfunIMU.gx;
    gyro.y = sparkfunIMU.gy;
    gyro.z = sparkfunIMU.gz;

    temp = sparkfunIMU.temperature;
}
