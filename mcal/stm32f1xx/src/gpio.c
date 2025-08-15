#include "gpio.h"

#include "stm32f103xb.h"

// Static Functions
static inline GPIO_TypeDef* port_gpio(uint8_t port) {
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

static inline uint8_t feature_gpio(GPIO_Config_t config) {
    switch (config.speed) {
        case GPIO_SPEED_FAST:
            return 50;
        case GPIO_SPEED_MEDIUM:
            return 10;
        case GPIO_SPEED_LOW:
            return 2;
    }
}

// Definitions
Functional_State gpio_init(GPIO_Port_t port) {
    RCC->APB2RSTR |= (1 << port);
    return OK;
}

Functional_State gpio_write(GPIO_Port_t port, uint8_t pin, bool on_off) {
    GPIO_TypeDef* current_port = port_gpio(port);
    current_port->ODR = on_off ? (current_port->ODR | (pin << 1)) : (current_port->ODR & ~(pin << 1));
}

Functional_State gpio_set_config(GPIO_Port_t port, GPIO_Mode_t mode, GPIO_Speed_t speed) {
    GPIO_TypeDef* current_port = port_gpio(port);
    // TODO : Assign the properties
}
Functional_State gpio_read(GPIO_Port_t port, uint8_t pin);
Functional_State gpio_clear(GPIO_Port_t port);
