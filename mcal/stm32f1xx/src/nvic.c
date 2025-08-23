/*
 * Author: EREN
 * Date: 25-08-23
 * Description: NVIC driver for STM32F103xB microcontroller.
 */

#include "nvic.h"

#include "stm32f103xb.h"

// 0-32 , 32-64 , 64-96
#define IRQ_RANGE 32

void nvic_enable_interrupt_request(IRQn_Type irq) {
    // The ISER (Interrupt Set-Enable Register) is an array of 32-bit registers.
    NVIC->ISER[irq / IRQ_RANGE] = (1U << (irq % IRQ_RANGE));
}

void nvic_disable_interrupt_request(IRQn_Type irq) {
    // Interrupt Clear Enable Register
    NVIC->ICER[irq / IRQ_RANGE] = (1U << (irq % IRQ_RANGE));
}
