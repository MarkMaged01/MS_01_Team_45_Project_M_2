#ifndef MPU6050_H
#define MPU6050_H

#include <stdint.h>

#define MPU6050_ADDRESS 0x68

void mpu6050_init();
void mpu6050_read_acc_gyro(int16_t *acc, int16_t *gyro);

#endif // MPU6050_H
