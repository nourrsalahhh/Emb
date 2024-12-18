#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"

#define BUZZER_PIN 16

void buzzer_init(void);
void buzzer_on(void);
void buzzer_off(void);

#endif