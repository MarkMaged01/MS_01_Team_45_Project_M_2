#include "hardware_control.h"
#include "hardware/pwm.h"


void setup_pwm(uint gpio, uint freq) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0f);  // Adjust for your desired frequency
    pwm_init(slice_num, &config, true);
    pwm_set_wrap(slice_num, 125000 / freq - 1);
}

void set_pwm_duty(uint gpio, float duty) {
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    uint channel = pwm_gpio_to_channel(gpio);
    // pwm_set_chan_level(slice_num, channel, duty * pwm_get_wrap(slice_num));
    pwm_set_chan_level(slice_num, channel, duty * 44);

}
