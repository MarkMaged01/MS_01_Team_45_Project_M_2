#include <Wire.h>
#include "mpu6050.h"

void mpu6050_init() {
    Wire.begin();
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0);    // Wake up the MPU6050
    Wire.endTransmission(true);
}

void mpu6050_read_acc_gyro(int16_t *acc, int16_t *gyro) {
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(0x3B); // Starting register for accelerometer data
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDRESS, 14, true);

    acc[0] = (Wire.read() << 8 | Wire.read()); // ACCEL_XOUT_H, ACCEL_XOUT_L
    acc[1] = (Wire.read() << 8 | Wire.read()); // ACCEL_YOUT_H, ACCEL_YOUT_L
    acc[2] = (Wire.read() << 8 | Wire.read()); // ACCEL_ZOUT_H, ACCEL_ZOUT_L

    gyro[0] = (Wire.read() << 8 | Wire.read()); // GYRO_XOUT_H, GYRO_XOUT_L
    gyro[1] = (Wire.read() << 8 | Wire.read()); // GYRO_YOUT_H, GYRO_YOUT_L
    gyro[2] = (Wire.read() << 8 | Wire.read()); // GYRO_ZOUT_H, GYRO_ZOUT_L
}
