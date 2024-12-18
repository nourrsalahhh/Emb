#include "pump.h"
 void pump_init() { 
    gpio_init(PUMP_PIN_1);
    gpio_set_dir(PUMP_PIN_1, GPIO_OUT); 
    gpio_init(PUMP_PIN_2);
    gpio_set_dir(PUMP_PIN_2, GPIO_OUT); 
    } 
 void pump_off() { 
    gpio_put(PUMP_PIN_1, 0);
    gpio_put(PUMP_PIN_2, 0);
     } 
 void pump_on() { 
    gpio_put(PUMP_PIN_1, 1);
    gpio_put(PUMP_PIN_2, 0);  
    }