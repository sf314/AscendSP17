// Stephen Flores
// ASCEND_Sensors.h
// Define functionality for the LSM6DS3 accel/gyro IMU

#ifndef ASCEND_IMU_h
#define ASCEND_IMU_h

#ifndef SPARKFUNLSM6DS3_h
#include "SparkFunLSM6DS3.h"
#endif

class IMU_Vector {
public:
    float x, y, z;
    float mag();
};

class ASCEND_IMU {
public:
    ASCEND_IMU();

    IMU_Vector accel;
    IMU_Vector gyro;
    double temp;

    void begin();
    void update();

private:
    LSM6DS3 sparkfunIMU;
};

#endif
