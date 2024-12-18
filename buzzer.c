#include "buzzer.h"

void buzzer_init(){
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

void buzzer_on(){
    gpio_put(BUZZER_PIN, true);
}

void buzzer_off(){
    gpio_put(BUZZER_PIN, false);
}



