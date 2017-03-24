// IMU 9DOF
#include "SparkFunLSM9DS1.h"

class IMU_Vector {
public:
    float x, y, z;
    float magnitude();
};

class ASCEND_IMU9DOF {
public:
    ASCEND_IMU9DOF();

    IMU_Vector accel;
    IMU_Vector gyro;
    IMU_Vector mag;
    double temp;

    void begin();
    void update();
    void useRawOutput(bool use);

private:
    LSM9DS1 sparkfunIMU;
    bool rawOutput = false;
};
