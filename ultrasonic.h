#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "pico/stdlib.h"

// Define the trigger and echo pins
#define TRIGGER_PIN 2
#define ECHO_PIN 3
#define THRESHOLD 20.0

// Speed of sound in cm/us (0.0343 cm per microsecond)
#define SOUND_SPEED 0.0343

void ultrasound_init();
float measure_distance();

bool is_water_nearby();

#endif