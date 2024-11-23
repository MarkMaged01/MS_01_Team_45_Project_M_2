#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "mpu6050.h"
#include "dht11.h"
#include "hardware_control.h"
#include "gy87.h"
#include "IR.h"

#define SDA_PIN 4
#define SCL_PIN 5
#define BUZZER_PIN 15
#define LED_PIN 14
#define MOTOR_PIN 16
#define DHT11_PIN 17
#define irei 20

int main()
{
    stdio_init_all();
    infrared_sensor_init(irei);
    // int temperature = 0, humidity = 0;

    dht11_init(DHT11_PIN);
    // Initialize I2C and MPU6050
    // gy87_init(i2c0, SDA_PIN, SCL_PIN, 100000);

    // Setup PWM
    setup_pwm(BUZZER_PIN, 1000); // 1 kHz for the buzzer
    setup_pwm(LED_PIN, 1000);    // 1 kHz for LED brightness
    setup_pwm(MOTOR_PIN, 500);   // 500 Hz for motor speed control

    int16_t accel_x, accel_y, accel_z;
    // int temperature, humidity;

    // Initial state variables
    bool led_on = false;
    bool buzzer_on = false;
    bool motor_on = false;

    while (true)
    {
        // Read accelerometer data
        // gy87_read_accel(i2c0, &accel_x, &accel_y, &accel_z);
        // printf("Accel: X=%d Y=%d Z=%d\n", accel_x, accel_y, accel_z);
        if (infrared_sensor_is_triggered(irei))
        {
            printf("Infrared sensor not triggered!\n");
        }
        else
        {
            printf("Infrared sensor triggered.\n");
        }
        // Toggle devices' states
        led_on = !led_on;
        buzzer_on = !buzzer_on;
        motor_on = !motor_on;
        // gio();
        // read();
        // Set PWM duty cycle based on state
        set_pwm_duty(BUZZER_PIN, buzzer_on ? 0.5 : 0.0); // 50% duty cycle if on, else off
        set_pwm_duty(LED_PIN, led_on ? 0.8 : 0.0);       // 80% brightness if on, else off
        set_pwm_duty(MOTOR_PIN, motor_on ? 0.6 : 0.6);   // 60% speed if on, else off
        printf("LED: %s, Buzzer: %s, Motor: %s\n",
               led_on ? "ON" : "OFF",
               buzzer_on ? "ON" : "OFF",
               motor_on ? "ON" : "OFF");

        sleep_ms(1000); // Delay for 1 second
        float temperature = 0, humidity = 0;

        if (
            dht11_read(&temperature, &humidity))
        {
            printf("Temperature: %.1f°C, Humidity: %.1f%%\n", temperature, humidity);
        }
        else
        {
            printf("Failed to read from DHT11 sensor\n");
        }
    }

    // float temperature = 0, humidity = 0;
    // while (1)
    // {
    //
    //     sleep_ms(2000);
    // }
    return 0;
}
