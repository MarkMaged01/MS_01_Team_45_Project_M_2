#ifndef DHT11_H
#define DHT11_H

#include "pico/stdlib.h"

bool dht11_read(float *temperature, float *humidity);

#endif
