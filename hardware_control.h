#ifndef HARDWARE_CONTROL_H
#define HARDWARE_CONTROL_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

void setup_pwm(uint gpio, uint freq);
void set_pwm_duty(uint gpio, float duty);

#endif
