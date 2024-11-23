#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "gy87.h"
#include "dht11.h"
#include "hardware_control.h"

#define SDA_PIN 4
#define SCL_PIN 5
#define BUZZER_PIN 15
#define LED_PIN 14
#define MOTOR_PIN 16
#define DHT11_PIN 17

// int main() {
//     stdio_init_all();

//     // Initialize I2C and MPU6050
//     gy87_init(i2c0, SDA_PIN, SCL_PIN, 100000);

//     // Setup PWM
//     setup_pwm(BUZZER_PIN, 1000);  // 1 kHz for the buzzer
//     setup_pwm(LED_PIN, 1000);     // 1 kHz for LED brightness
//     setup_pwm(MOTOR_PIN, 500);    // 500 Hz for motor speed control

//     int16_t accel_x, accel_y, accel_z;
//     int16_t gyro_x, gyro_y, gyro_z;
//     int temperature, humidity;

//     while (true) {
//         // Read accelerometer data
//         gy87_read_accel(i2c0, &accel_x, &accel_y, &accel_z);

//         // Read gyroscope data
//         gy87_read_gyro(i2c0, &gyro_x, &gyro_y, &gyro_z);

//         // Read temperature and humidity
//         if (dht11_read(DHT11_PIN, &temperature, &humidity)) {
//             // Clear the console for a cleaner view
//             // printf("\033[2J\033[H"); // ANSI escape codes to clear console and reset cursor

//             // Print the MPU6050 data
//             printf("=========== Sensor Readings ===========\n");
//             printf("MPU6050 Accelerometer:\n");
//             printf("  X: %d\n", accel_x);
//             printf("  Y: %d\n", accel_y);
//             printf("  Z: %d\n\n", accel_z);

//             printf("MPU6050 Gyroscope:\n");
//             printf("  X: %d\n", gyro_x);
//             printf("  Y: %d\n", gyro_y);
//             printf("  Z: %d\n\n", gyro_z);

//             // Print the DHT11 data
//             printf("DHT11 Temperature and Humidity:\n");
//             printf("  Temp : %d°C\n", temperature);
//            

//             // Print device control states
//             printf("=========== Device Controls ===========\n");
//             printf("Buzzer PWM Duty Cycle: %.0f%%\n", 0.5 * 100);
//             printf("LED PWM Brightness: %.0f%%\n", 0.8 * 100);
//             printf("Motor PWM Speed: %.0f%%\n", 0.6 * 100);
//             printf("=======================================\n");

//         } else {
//             printf("DHT11 read failed! Retrying...\n");
//         }

//         // Control devices (example)
//         set_pwm_duty(BUZZER_PIN, 0.5);  // 50% duty cycle
//         set_pwm_duty(LED_PIN, 0.8);    // 80% brightness
//         set_pwm_duty(MOTOR_PIN, 0.6);  // 60% speed

//         sleep_ms(1000);  // Delay for 1 second
//     }

//     return 0;
// }
