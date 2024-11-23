#include "dht11.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <stdlib.h>  // For srand(), rand()
#include <time.h>    

// Define timing constants for DHT11
#define DHT11_TIMEOUT 10000

static uint dht11_pin;

void dht11_init(uint pin) {
    dht11_pin = pin;
    gpio_init(dht11_pin);
    gpio_set_dir(dht11_pin, GPIO_OUT);
    gpio_put(dht11_pin, 1);
}

static int dht11_wait(uint state) {
    int count = 0;
    while (gpio_get(dht11_pin) == state) {
        if (++count >= DHT11_TIMEOUT) {
            return -1;
        }
    }
    return count;
}

bool dht11_read(float *temperature, float *humidity) {
    uint8_t data[5] = {0};

    // Start signal
    gpio_set_dir(dht11_pin, GPIO_OUT);
    gpio_put(dht11_pin, 0);
    sleep_ms(20);  // Wait for 20ms
    gpio_put(dht11_pin, 1);
    sleep_us(30);

    // Switch to input mode
    gpio_set_dir(dht11_pin, GPIO_IN);

    // Wait for response
    if (dht11_wait(0) == -1 || dht11_wait(1) == -1) {
        return false;
    }

    // Read data
    for (int i = 0; i < 40; i++) {
        if (dht11_wait(0) == -1) {
            return false;
        }
        if (dht11_wait(1) == -1) {
            return false;
        }
        busy_wait_us_32(35);
        if (gpio_get(dht11_pin) == 1) {
            data[i / 8] <<= 1;
            data[i / 8] |= 1;
        } else {
            data[i / 8] <<= 1;
        }
    }

    // Check checksum
    if (data[4] != (data[0] + data[1] + data[2] + data[3])) {
        return false;
    }

    // Extract temperature and humidity
    *humidity = data[0] + data[1] / 10.0;
    *temperature = data[2] + data[3] / 10.0;

    return true;
}

