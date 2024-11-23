#include "pico/stdlib.h"
#include <math.h>
#include <stdio.h>

// Define I2C pins for Raspberry Pi Pico
#define I2C_SDA_PIN 4 // Data pin
#define I2C_SCL_PIN 5 // Clock pin

// Timing for I2C bit-banging
#define I2C_DELAY sleep_us(5)

// MPU6050 address
const int MPU = 0x68;

// Global variables
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float roll, pitch, yaw;

// Helper functions for I2C bit-banging
void I2C_Start() {
  gpio_set_dir(I2C_SDA_PIN, GPIO_OUT);
  gpio_put(I2C_SDA_PIN, 1);
  gpio_put(I2C_SCL_PIN, 1);
  I2C_DELAY;
  gpio_put(I2C_SDA_PIN, 0);
  I2C_DELAY;
  gpio_put(I2C_SCL_PIN, 0);
}

void I2C_Stop() {
  gpio_set_dir(I2C_SDA_PIN, GPIO_OUT);
  gpio_put(I2C_SCL_PIN, 0);
  gpio_put(I2C_SDA_PIN, 0);
  I2C_DELAY;
  gpio_put(I2C_SCL_PIN, 1);
  I2C_DELAY;
  gpio_put(I2C_SDA_PIN, 1);
}

void I2C_WriteByte(uint8_t data) {
  gpio_set_dir(I2C_SDA_PIN, GPIO_OUT);
  for (int i = 0; i < 8; i++) {
    gpio_put(I2C_SDA_PIN, (data & 0x80) != 0);
    data <<= 1;
    I2C_DELAY;
    gpio_put(I2C_SCL_PIN, 1);
    I2C_DELAY;
    gpio_put(I2C_SCL_PIN, 0);
  }
  // Acknowledge bit
  gpio_set_dir(I2C_SDA_PIN, GPIO_IN);
  gpio_put(I2C_SCL_PIN, 1);
  I2C_DELAY;
  gpio_put(I2C_SCL_PIN, 0);
}

uint8_t I2C_ReadByte(bool ack) {
  uint8_t data = 0;
  gpio_set_dir(I2C_SDA_PIN, GPIO_IN);
  for (int i = 0; i < 8; i++) {
    gpio_put(I2C_SCL_PIN, 1);
    data = (data << 1) | gpio_get(I2C_SDA_PIN);
    gpio_put(I2C_SCL_PIN, 0);
    I2C_DELAY;
  }
  // Send acknowledgment
  gpio_set_dir(I2C_SDA_PIN, GPIO_OUT);
  gpio_put(I2C_SDA_PIN, !ack);
  gpio_put(I2C_SCL_PIN, 1);
  I2C_DELAY;
  gpio_put(I2C_SCL_PIN, 0);
  return data;
}

// Write to MPU6050 register
void MPU6050_WriteRegister(uint8_t reg, uint8_t value) {
  I2C_Start();
  I2C_WriteByte(MPU << 1);  // Send MPU address with write bit
  I2C_WriteByte(reg);       // Register address
  I2C_WriteByte(value);     // Data to write
  I2C_Stop();
}

// Read from MPU6050 register
uint8_t MPU6050_ReadRegister(uint8_t reg) {
  uint8_t data;
  I2C_Start();
  I2C_WriteByte(MPU << 1);  // Send MPU address with write bit
  I2C_WriteByte(reg);       // Register address
  I2C_Start();
  I2C_WriteByte((MPU << 1) | 1);  // Send MPU address with read bit
  data = I2C_ReadByte(false);     // Read one byte
  I2C_Stop();
  return data;
}

// Read multiple bytes from MPU6050
void MPU6050_ReadRegisters(uint8_t reg, uint8_t* buffer, uint8_t length) {
  I2C_Start();
  I2C_WriteByte(MPU << 1);  // Send MPU address with write bit
  I2C_WriteByte(reg);       // Starting register address
  I2C_Start();
  I2C_WriteByte((MPU << 1) | 1);  // Send MPU address with read bit
  for (uint8_t i = 0; i < length; i++) {
    buffer[i] = I2C_ReadByte(i < (length - 1));  // Acknowledge all but the last byte
  }
  I2C_Stop();
}

void setup() {
  // Initialize stdio for serial communication
  stdio_init_all();

  // Initialize I2C pins
  gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_SIO);
  gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_SIO);
  gpio_set_dir(I2C_SDA_PIN, GPIO_OUT);
  gpio_set_dir(I2C_SCL_PIN, GPIO_OUT);
  gpio_put(I2C_SDA_PIN, 1);
  gpio_put(I2C_SCL_PIN, 1);

  // Wake up MPU6050
  MPU6050_WriteRegister(0x6B, 0x00);

  printf("MPU6050 Initialized\n");
}

void gio() {
  uint8_t buffer[14];
  MPU6050_ReadRegisters(0x3B, buffer, 14);

  // Convert accelerometer data
  AccX = ((int16_t)(buffer[0] << 8 | buffer[1])) / 16384.0;
  AccY = ((int16_t)(buffer[2] << 8 | buffer[3])) / 16384.0;
  AccZ = ((int16_t)(buffer[4] << 8 | buffer[5])) / 16384.0;

  // Convert gyroscope data
  GyroX = ((int16_t)(buffer[8] << 8 | buffer[9])) / 131.0;
  GyroY = ((int16_t)(buffer[10] << 8 | buffer[11])) / 131.0;
  GyroZ = ((int16_t)(buffer[12] << 8 | buffer[13])) / 131.0;

  // Calculate roll and pitch
  roll = atan(AccY / sqrt(AccX * AccX + AccZ * AccZ)) * 180 / M_PI;
  pitch = atan(-1 * AccX / sqrt(AccY * AccY + AccZ * AccZ)) * 180 / M_PI;

  // Print results
  printf("Roll: %.2f | Pitch: %.2f | GyroX: %.2f | GyroY: %.2f | GyroZ: %.2f\n", roll, pitch, GyroX, GyroY, GyroZ);

  sleep_ms(500);
}