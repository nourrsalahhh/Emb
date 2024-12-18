#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "fan.h"
#include <stdio.h>

static uint pwm_slice_num; // PWM slice number

void fan_init() {
    // Initialize direction pins
    gpio_init(FAN_PIN_DIR_1);
    gpio_set_dir(FAN_PIN_DIR_1, GPIO_OUT);
    gpio_put(FAN_PIN_DIR_1, 0);

    gpio_init(FAN_PIN_DIR_2);
    gpio_set_dir(FAN_PIN_DIR_2, GPIO_OUT);
    gpio_put(FAN_PIN_DIR_2, 0);

    // Initialize PWM pin
    gpio_set_function(FAN_PIN_PWM, GPIO_FUNC_PWM);
    pwm_slice_num = pwm_gpio_to_slice_num(FAN_PIN_PWM);

    // Configure PWM: frequency = 1 kHz, duty cycle = 0
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 16.0f); // Divide clock to reduce frequency
    pwm_init(pwm_slice_num, &config, true);

    fan_off();
}

void fan_off() {
    // Set duty cycle to 0 (disable H-Bridge)
    pwm_set_gpio_level(FAN_PIN_PWM, 0);

    // Reset direction pins to default state
    gpio_put(FAN_PIN_DIR_1, 0);
    gpio_put(FAN_PIN_DIR_2, 0);
}

void fan_on(uint duty_cycle) {
    if (duty_cycle > 100) duty_cycle = 100; // Clamp duty cycle to valid range

    // Set direction for forward motion (example configuration)
    gpio_put(FAN_PIN_DIR_1, 1);
    gpio_put(FAN_PIN_DIR_2, 0);
    

    // Set PWM level based on duty cycle
    uint16_t level = (duty_cycle * 65535) / 100; // Convert to 16-bit level

    printf("Duty Cycle: %u, PWM Level: %u\n", duty_cycle, level);
    pwm_set_gpio_level(FAN_PIN_PWM, level);
}
