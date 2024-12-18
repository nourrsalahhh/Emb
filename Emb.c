#include "pico/stdlib.h"
#include "fan.h"
#include "water.h"
#include "pump.h"
#include "ultrasonic.h"
#include "dht11.h"
#include "buzzer.h"
#include "FreeRTOS.h"
#include "task.h"

#define TEMP1 15
#define TEMP2 23
#define WATER 70
#define DISTANCE 6


void vPumpTask() {
   water_sensor_init();
   pump_init();

   for (;;) {
      float water = water_sensor_read_level();
      vTaskDelay(pdMS_TO_TICKS(2000));

      if(water<=WATER){
      pump_on();
      printf("Pump is ON\n");
      }
      else{
      pump_off();
      printf("Pump is OFF\n");
      }

   }

}

void vFanTask() {
   fan_init();
   dht11_init(15);

   float temperature = 0.0f, humidity = 0.0f;
   
   while (true) {
      int result = dht11_read(15, &temperature, &humidity);

      if (result == 0) {
         printf("Temperature: %.1f°C\n", temperature);
         printf("Humidity: %.1f%%\n", humidity);
      } else {
         printf("Failed to read from DHT11\n");
      }
      vTaskDelay(pdMS_TO_TICKS(2000));
      
      if (temperature >= TEMP1 && temperature <= TEMP2) {
         fan_on(30);
         printf("Fan MEDIUM\n");
         } 
         else if (temperature > TEMP2) {
            fan_on(100);
            printf("Fan HIGH\n");
         }
         else {
            fan_off();
            printf("Fan is OFF\n");
         }
   }
}

void vBuzzerTask() {
      ultrasound_init();
      buzzer_init();
   while (true) {
      float sonic = measure_distance(); 
      printf("Distance: %.2f cm\n", sonic);
      const TickType_t xPeriod = pdMS_TO_TICKS(2000);
      vTaskDelay(xPeriod);
      if(sonic>=DISTANCE){
      buzzer_on();
      printf("Buzzer is ON\n");
      }
      else{
      buzzer_off();
      printf("Buzzer is OFF\n");
      }
   }   
}

void main() {

  stdio_init_all();

   xTaskCreate(vPumpTask, "Pump Task", 256, NULL, 2, NULL);
   xTaskCreate(vFanTask, "Fan Task", 256, NULL, 1, NULL);
   xTaskCreate(vBuzzerTask, "Buzzer Task", 256, NULL, 3, NULL);

   vTaskStartScheduler();

}