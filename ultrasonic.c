#include "ultrasonic.h"
#include "pico/stdlib.h"

#define SOUND_SPEED 0.0343
#define TIMEOUT_US 30000 // 30 ms (for ~5 m max range)

void ultrasound_init() {
    gpio_init(TRIGGER_PIN);
    gpio_set_dir(TRIGGER_PIN, true);
    gpio_put(TRIGGER_PIN, false);

    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, false);

    printf("Ultrasonic sensor initialized.\n");
}

float measure_distance() {
    // Trigger the ultrasonic sensor
    gpio_put(TRIGGER_PIN, true);
    sleep_us(10);  // 10 microseconds pulse (standard for HC-SR04)
    gpio_put(TRIGGER_PIN, false);

    // Wait for echo to start
    int timeout = TIMEOUT_US;
    while (gpio_get(ECHO_PIN) == 0 && timeout-- > 0) {
        sleep_us(1);
    }
    if (timeout <= 0) {
        printf("Echo signal did not start.\n");
        return -1; // Indicate timeout error
    }
    absolute_time_t start_time = get_absolute_time();
    printf("Echo started at time: %lld\n", absolute_time_diff_us(get_absolute_time(), start_time));

    // Wait for echo to end
    timeout = TIMEOUT_US;
    while (gpio_get(ECHO_PIN) == 1 && timeout-- > 0) {
        sleep_us(1);
    }
    if (timeout <= 0) {
        printf("Echo signal did not end.\n");
        return -1; // Indicate timeout error
    }
    absolute_time_t end_time = get_absolute_time();
    printf("Echo ended at time: %lld\n", absolute_time_diff_us(start_time, end_time));

    // Calculate pulse duration and distance
    int64_t pulse_duration = absolute_time_diff_us(start_time, end_time);
    float distance = (pulse_duration * SOUND_SPEED) / 2;

    // Output the result
    printf("Pulse duration: %lld µs, Distance: %.2f cm\n", pulse_duration, distance);
    return distance;
}
