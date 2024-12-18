#include "water.h"
#include "pico/stdlib.h"



void water_sensor_init(void) {
    adc_init();                      // Initialize ADC
    adc_gpio_init(WATER_SENSOR_PIN);  // Initialize the GPIO pin for ADC
    adc_select_input(0);              // Select ADC0 (GP26)
}

// Function to read the water level
float water_sensor_read_level(void) {
    uint16_t raw_value = adc_read();  // Read the raw ADC value (0-4095)
    
    // Convert raw ADC value (0-4095) to voltage (0-3.3V)
    float voltage = (raw_value * 3.3) / 4095.0;
    
    // Map the voltage to water level percentage (0V = 0%, 3.3V = 100%)
    float water_level_percentage = (voltage / 3.3) * 100.0;
    
    return water_level_percentage;
}
