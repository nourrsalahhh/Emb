#ifndef WATER_H 
#define WATER_H 

#include "pico/stdlib.h" 
#include "hardware/adc.h" 

#define WATER_SENSOR_PIN 26  // GP26 (ADC0)

void water_sensor_init(void);  // Function to initialize the water sensor
float water_sensor_read_level(void);  // Function to read the water level as a percentage

#endif
