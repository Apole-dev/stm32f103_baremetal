/*
 * Author: EREN
 * Date: 25-08-17
 * Description: GPIO function definitions,
 */

#include "gpio.h"

#include "stm32f103xb.h"

// Helper: return GPIO base address from enum
GPIO_TypeDef *port_gpio(GPIO_Port_t port) {
    switch (port) {
        case PORT_A:
            return GPIOA;
        case PORT_B:
            return GPIOB;
        case PORT_C:
            return GPIOC;
        case PORT_D:
            return GPIOD;
        case PORT_E:
            return GPIOE;
        default:
            return 0;
    }
}

// Enable GPIO port clock
Functional_State gpio_init_pin(gpio_handle_t *h) {
    if (!h) return INIT_FAIL;

    switch (h->port) {
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
        default:
            return INIT_FAIL;
    }

    // Configure pin mode/speed
    return gpio_set_config(h->port, h->pin, h->mode, h->speed);
}

// Configure pin mode and speed (internal helper)
Functional_State gpio_set_config(GPIO_Port_t port, uint8_t pin, GPIO_Mode_t mode, GPIO_Speed_t speed) {
    GPIO_TypeDef *current_port = port_gpio(port);
    if (!current_port || pin > 15) return INIT_FAIL;

    uint32_t shift = (pin % 8) * 4;
    volatile uint32_t *config_reg = (pin < 8) ? &current_port->CRL : &current_port->CRH;

    // Clear 4 bits
    *config_reg &= ~(0xF << shift);

    uint32_t mode_bits = 0;
    uint32_t cnf_bits = 0;

    switch (mode) {
        case GPIO_MODE_INPUT_ANALOG:
            mode_bits = 0b00;
            cnf_bits = 0b00;
            break;
        case GPIO_MODE_INPUT_FLOATING:
            mode_bits = 0b00;
            cnf_bits = 0b01;
            break;
        case GPIO_MODE_INPUT_PULL:
            mode_bits = 0b00;
            cnf_bits = 0b10;
            break;
        case GPIO_MODE_OUTPUT_PP:
            cnf_bits = 0b00;
            break;
        case GPIO_MODE_OUTPUT_OD:
            cnf_bits = 0b01;
            break;
        case GPIO_MODE_AF_PP:
            cnf_bits = 0b10;
            break;
        case GPIO_MODE_AF_OD:
            cnf_bits = 0b11;
            break;
    }

    if (mode >= GPIO_MODE_OUTPUT_PP) {
        switch (speed) {
            case GPIO_SPEED_LOW:
                mode_bits = 0b01;
                break;
            case GPIO_SPEED_MEDIUM:
                mode_bits = 0b10;
                break;
            case GPIO_SPEED_FAST:
                mode_bits = 0b11;
                break;
        }
    }

    *config_reg |= ((mode_bits | (cnf_bits << 2)) << shift);

    return OK;
}

// Write pin state
Functional_State gpio_write_pin(gpio_handle_t *h, bool on_off) {
    if (!h || h->pin > 15) return WRITE_FAIL;

    GPIO_TypeDef *current_port = port_gpio(h->port);
    if (!current_port) return WRITE_FAIL;

    if (on_off) {
        current_port->BSRR = (1 << h->pin);  // Set bit
    } else {
        current_port->BSRR = (1 << (h->pin + 16));  // Reset bit
    }
    return OK;
}

// Read pin state
Functional_State gpio_read_pin(gpio_handle_t *h, bool *state) {
    if (!h || !state || h->pin > 15) return READ_FAIL;
    GPIO_TypeDef *current_port = port_gpio(h->port);
    if (!current_port) return READ_FAIL;

    *state = ((current_port->IDR >> h->pin) & 0x1) ? true : false;
    return OK;
}

// Clear entire port
Functional_State gpio_clear_port(GPIO_Port_t port) {
    GPIO_TypeDef *current_port = port_gpio(port);
    if (!current_port) return CLEAR_FAIL;

    current_port->ODR = 0x0000;
    return OK;
}

// Set alternate function (AF) remap
Functional_State gpio_set_af_mode(gpio_handle_t *h) {
    (void)h;
    return OK;
}
