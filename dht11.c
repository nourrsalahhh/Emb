#include "dht11.h"
#include "pico/stdlib.h"

// Constants
#define DHT11_MAX_TIMINGS 85
#define DHT11_HIGH_LEVEL 50

// Initialize the DHT11 pin
void dht11_init(uint32_t gpio) {
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_put(gpio, 1); // Set pin high initially
}

// Read temperature and humidity from DHT11
int dht11_read(uint32_t gpio, float *temperature, float *humidity) {
    uint16_t pulses[DHT11_MAX_TIMINGS] = {0};
    uint8_t data[5] = {0};

    // Send start signal
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_put(gpio, 0); // Pull low for 18ms
    sleep_ms(18);
    gpio_put(gpio, 1); // Pull high for 20-40µs
    sleep_us(40);
    gpio_set_dir(gpio, GPIO_IN); // Switch to input mode

    // Read pulse lengths
    uint32_t last_time = time_us_32();
    int current_level = gpio_get(gpio);
    int count = 0;

    while (count < DHT11_MAX_TIMINGS) {
        int new_level = gpio_get(gpio);
        if (new_level != current_level) {
            uint32_t now = time_us_32();
            pulses[count++] = now - last_time;
            last_time = now;
            current_level = new_level;
        }
        if ((time_us_32() - last_time) > 1000) {
            break; // Timeout
        }
    }

    // Parse the pulse data into 5 bytes
    for (int i = 0; i < 40; ++i) {
        data[i / 8] <<= 1;
        if (pulses[2 * i + 1] > DHT11_HIGH_LEVEL) {
            data[i / 8] |= 1;
        }
    }

    // Convert the data into temperature and humidity
    *humidity = (data[0] + data[1] / 10.0f ) - 100;
    *temperature = data[2] + data[3] / 10.0f;

    return 0; // Always return success
}