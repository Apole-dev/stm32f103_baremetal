/*
 * Author: EREN
 * Date: 25-08-23
 * Description: SysTick driver for Stm32f103.
 */

#include "systick.h"

#include <stdint.h>

#include "rcc.h"  //To learn clock frequency
#include "stm32f103xb.h"

#define DesiredFrequency 1000  // 1ms

static volatile uint32_t tick_count;

void systick_init(void) {
    // Reload Value = (Clcok-mhz/Desired frequency)-1
    SysTick->LOAD = (current_clock_hz / DesiredFrequency) - 1;
    // 2. Reset the current SysTick counter value.
    SysTick->VAL = 0;

    // 3. Configure and enable SysTick.
    // SysTick_CTRL_CLKSOURCE_Msk: Use the processor clock (AHB).
    // SysTick_CTRL_TICKINT_Msk:  Enable SysTick interrupt.
    // SysTick_CTRL_ENABLE_Msk:   Enable the SysTick timer.
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void delay_ms(uint32_t ms) {
    uint32_t temp_time = tick_count;
    while ((tick_count - temp_time) < ms);
}

/**
 * @brief  This function is the SysTick interrupt service routine (ISR).
 * @note   It is called automatically by the hardware every 1ms.
 * The function name is fixed and defined in the startup file.
 *   .weak SysTick_Handler from startup file
 */
void SysTick_Handler(void) { tick_count++; }
