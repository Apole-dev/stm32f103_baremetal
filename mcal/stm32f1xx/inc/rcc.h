#ifndef RCC_H
#define RCC_H

#include <stdint.h>
typedef enum {
    HSI_INTERNAL_CLK_8MHZ,
    HSE_EXTERNAL_CLK_8MHZ,
    PLL_HSI_MAX_64MHZ,
    PLL_HSE_MAX_72MHZ,
} SystemClock_t;

extern uint32_t current_clock_hz;

void rcc_set_config(SystemClock_t clock);
#endif  // RCC_H
