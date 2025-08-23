#ifndef EXTI_H
#define EXTI_H

#include <stdint.h>

#include "gpio.h"

typedef enum { RISING_EDGE, FALLING_EDGE, RISING_FALLING_EDGE } Edge_Trigger_t;

void exti_configure(GPIO_Port_t port, uint8_t pin, Edge_Trigger_t);
#endif /* EXTI_H */
