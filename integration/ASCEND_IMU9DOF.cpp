// Implementation;


#ifndef ARDUINO_H
#include "Arduino.h"
#endif

#ifndef _ASCEND_IMU9DOF_h
#define _ASCEND_IMU9DOF_h

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
    rawOutput = false;
}

// BEGIN
void ASCEND_IMU9DOF::begin() {
    sparkfunIMU.begin();
}

// UPDATE (call every loop before accessing accel/gyro objects)
void ASCEND_IMU9DOF::update() {
    sparkfunIMU.readGyro();
    sparkfunIMU.readAccel();
    sparkfunIMU.readMag();
    sparkfunIMU.readTemp();

    if (rawOutput) {
        accel.x = sparkfunIMU.ax;
        accel.y = sparkfunIMU.ay;
        accel.z = sparkfunIMU.az;

        gyro.x = sparkfunIMU.gx;
        gyro.y = sparkfunIMU.gy;
        gyro.z = sparkfunIMU.gz;

        mag.x = sparkfunIMU.mx;
        mag.y = sparkfunIMU.my;
        mag.z = sparkfunIMU.mz;

        temp = sparkfunIMU.temperature;
    } else {
        // Accel returns amount in g's
        accel.x = sparkfunIMU.calcAccel(sparkfunIMU.ax);
        accel.y = sparkfunIMU.calcAccel(sparkfunIMU.ay);
        accel.z = sparkfunIMU.calcAccel(sparkfunIMU.az);

        // Gyro returns amount in deg/sec
        gyro.x = sparkfunIMU.calcGyro(sparkfunIMU.gx);
        gyro.y = sparkfunIMU.calcGyro(sparkfunIMU.gy);
        gyro.z = sparkfunIMU.calcGyro(sparkfunIMU.gz);

        // Mag returns amount in gauss (?)
        mag.x = sparkfunIMU.calcMag(sparkfunIMU.mx);
        mag.y = sparkfunIMU.calcMag(sparkfunIMU.my);
        mag.z = sparkfunIMU.calcMag(sparkfunIMU.mz);
    }
}

void ASCEND_IMU9DOF::useRawOutput(bool use) {
    rawOutput = use;
}

#endif
