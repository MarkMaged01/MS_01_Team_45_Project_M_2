
#define MPU6050_H

#include "pico/stdlib.h"
#include <stdbool.h>

// Define I2C pins for Raspberry Pi Pico
#define I2C_SDA_PIN 4
#define I2C_SCL_PIN 5

// MPU6050 address
#define MPU 0x68

// Timing for I2C bit-banging
#define I2C_DELAY sleep_us(5)

// Global variables
extern float AccX, AccY, AccZ;
extern float GyroX, GyroY, GyroZ;
extern float roll, pitch, yaw;

// Function declarations
void I2C_Start();
void I2C_Stop();
void I2C_WriteByte(uint8_t data);
uint8_t I2C_ReadByte(bool ack);
void MPU6050_WriteRegister(uint8_t reg, uint8_t value);
uint8_t MPU6050_ReadRegister(uint8_t reg);
void MPU6050_ReadRegisters(uint8_t reg, uint8_t* buffer, uint8_t length);
void setup();
void gio();

