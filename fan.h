#ifndef FAN_H 
#define FAN_H 

#include "pico/stdlib.h"

#define FAN_PIN_DIR_1 6 // Direction pin 1
#define FAN_PIN_DIR_2 7 // Direction pin 2
#define FAN_PIN_PWM   8 // PWM enable pin

void fan_init(void);
void fan_on(uint duty_cycle); // Duty cycle (0-100%)
void fan_off(void);

  #endif