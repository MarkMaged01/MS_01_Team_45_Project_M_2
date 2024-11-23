#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H

#include "pico/stdlib.h"

// Define the default pin for the infrared sensor
#define IR_SENSOR_PIN 18 // Default GPIO pin for infrared sensor

// Function prototypes
void infrared_sensor_init(uint sensor_pin);
bool infrared_sensor_is_triggered(uint sensor_pin);

#endif // INFRARED_SENSOR_H
