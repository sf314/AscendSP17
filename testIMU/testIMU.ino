// Stephen Flores
// testIMU.ino
// Testing the functionality of ASCEND_IMU library

// NOTE:
// LSM6DS3 uses 3.3V power
// LSM6DS3 SDA is A4, SCL is A5

// LIBRARIES
    #include "Wire.h"
    #include "SPI.h"
    #include "ASCEND_IMU.h"

// OBJECTS
    ASCEND_IMU imu;


void setup() {
    Serial.begin(9600);
    imu.begin();
    Serial.print("Starting test in 3...");
    delay(1000);
    Serial.print("2...");
    delay(1000);
    Serial.println("1...");
    delay(1000);
}

void loop() {
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

    delay(1000);
}
