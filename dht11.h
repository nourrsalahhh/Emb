#ifndef DHT11_H
#define DHT11_H

#include <stdint.h>

// Function prototypes
void dht11_init(uint32_t gpio);
int dht11_read(uint32_t gpio, float *temperature, float *humidity);

#endif // DHT11_H