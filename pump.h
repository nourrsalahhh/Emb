#ifndef PUMP_H 
#define PUMP_H 
#include "pico/stdlib.h" 
#define PUMP_PIN_1 4
#define PUMP_PIN_2 5
void pump_init(void); 
void pump_on(void); 
void pump_off(void);
 #endif