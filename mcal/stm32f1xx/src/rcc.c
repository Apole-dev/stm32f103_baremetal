/*
 * Author: EREN
 * Date: 25-08-21
 * Description: RCC driver for STM32F103
 */

#include "rcc.h"

#include <stdint.h>

#include "stm32f103xb.h"

uint32_t current_clock_hz = 0;
void rcc_set_config(SystemClock_t clock_source) {
    /*
      000 Zero wait state, if 0 < SYSCLK <= 24 MHz
      001 One wait state, if 24 MHz < SYSCLK <= 48 MHz
      010 Two wait states, if 48 MHz < SYSCLK <= 72 MHz
     */
    // Flash Settings
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    switch (clock_source) {
        case HSI_INTERNAL_CLK_8MHZ:
            // Configure HSI as system clock
            current_clock_hz = 8000000;
            RCC->CR |= RCC_CR_HSION;
            while (!(RCC->CR & RCC_CR_HSIRDY));
            RCC->CFGR &= ~RCC_CFGR_SW;
            RCC->CFGR |= RCC_CFGR_SWS_HSI;
            while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);
            RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);

            break;
        case HSE_EXTERNAL_CLK_8MHZ:
            // Configure HSE as system clock
            current_clock_hz = 8000000;
            RCC->CR |= RCC_CR_HSEON;
            while (!(RCC->CR & RCC_CR_HSERDY));
            RCC->CFGR &= ~RCC_CFGR_SW;
            RCC->CFGR |= RCC_CFGR_SWS_HSE;
            while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE);
            RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);

            break;
        case PLL_HSI_MAX_64MHZ:
            // Configure PLL as system clock
            current_clock_hz = 64000000;
            RCC->CR |= RCC_CR_HSION;
            while (!(RCC->CR & RCC_CR_HSIRDY));
            RCC->CFGR &= ~RCC_CFGR_SW;
            RCC->CFGR |= RCC_CFGR_SW_HSI;
            while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);
            RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);
            RCC->CFGR |= RCC_CFGR_PLLMULL9;
            RCC->CR |= RCC_CR_PLLON;
            while (!(RCC->CR & RCC_CR_PLLRDY));

            RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
            RCC->CFGR |= RCC_CFGR_HPRE_DIV1;   // AHB -> 64MHz
            RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;  // APB1 -> 32MHz
            RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;  // APB2 -> 64MHz

            RCC->CFGR |= RCC_CFGR_SW_PLL;
            while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
            break;
        case PLL_HSE_MAX_72MHZ:
            // Configure PLL as system clock
            current_clock_hz = 72000000;
            RCC->CR |= RCC_CR_HSEON;
            while (!(RCC->CR & RCC_CR_HSERDY));
            RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
            // For detailed information look RM0008 page 50-52.
            RCC->CFGR |= RCC_CFGR_HPRE_DIV1;   // AHB -> 72MHz
            RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;  // APB1 -> 36MHz
            RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;  // APB2 -> 72MHz
            RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);
            RCC->CFGR |= RCC_CFGR_PLLSRC;    // Source HSE
            RCC->CFGR |= RCC_CFGR_PLLMULL9;  // x 9
            RCC->CR |= RCC_CR_PLLON;
            while (!(RCC->CR & RCC_CR_PLLRDY));
            RCC->CFGR |= RCC_CFGR_SW_PLL;
            while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
            break;
        default:
            // Invalid clock source
            break;
    }
}
