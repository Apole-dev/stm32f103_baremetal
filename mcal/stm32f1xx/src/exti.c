/*
 * Author: EREN
 * Date: 25-23-08
 * Description: File description
 */

#include "exti.h"

#include <stdint.h>

#include "gpio.h"
#include "nvic.h"
#include "stm32f103xb.h"

void exti_configure(GPIO_Port_t port, uint8_t pin, Edge_Trigger_t trigger) {
    switch (port) {
        case PORT_A:
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
            break;
        case PORT_B:
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
            break;
        case PORT_C:
            RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
            break;
        case PORT_D:
            RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
            break;
        case PORT_E:
            RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
            break;
    }
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    // TODO: ADD switch case for config depend on connection to gnd or vcc
    // 2. Set the GPIO pin as input with pull-up or pull-down resistor.
    gpio_set_config(port, pin, GPIO_MODE_INPUT_PULL, GPIO_SPEED_FAST);

    // 3. Connect the GPIO pin to the EXTI line using the AFIO multiplexer.
    uint8_t exti_index = pin / 4;
    uint8_t exti_shif = (pin % 4) * 4;
    // First, clear the 4 bits for the target EXTI line.
    AFIO->EXTICR[exti_index] &= ~(0x0F << exti_shif);
    // Then, set the 4 bits to the code of the desired port.
    AFIO->EXTICR[exti_index] |= ((port - 2) << exti_shif);

    // 4. Configure the EXTI line itself.
    // Unmask the interrupt request from the line. This allows it to generate interrupts.
    EXTI->IMR |= (1U << pin);
    switch (trigger) {
        case RISING_EDGE:
            EXTI->RTSR |= (1U << pin);
            EXTI->FTSR &= ~(1U << pin);  // Ensure falling edge is disabled
            break;
        case FALLING_EDGE:
            EXTI->FTSR |= (1U << pin);
            EXTI->RTSR &= ~(1U << pin);  // Ensure rising edge is disabled
            break;
        case RISING_FALLING_EDGE:
            EXTI->RTSR |= (1U << pin);
            EXTI->FTSR |= (1U << pin);
            break;
    }
    // 5. Enable the corresponding IRQ in the NVIC.
    if (pin >= 0 && pin <= 4) {
        nvic_enable_interrupt_request((IRQn_Type)(EXTI0_IRQn + pin));
    } else if (pin >= 5 && pin <= 9) {
        nvic_enable_interrupt_request(EXTI9_5_IRQn);
    } else if (pin >= 10 && pin <= 15) {
        nvic_enable_interrupt_request(EXTI15_10_IRQn);
    }
}
