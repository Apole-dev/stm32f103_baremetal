#include "gpio.h"

#include "stm32f103xb.h"

Functional_State gpio_init(const GPIO_Config_t *config) {
    if (config == 0) return INIT_FAIL;
    RCC->APB2RSTR |= (1 << config->port);
    return ENABLE;
}

Functional_State gpio_write(GPIO_TypeDef *port, uint8_t pin, bool state) {
    if (state) {
        port->BSRR = (1U << pin);  // Set the pin (write 1 to the corresponding bit in the lower 16 bits)
    } else {
        port->BSRR = (1U << (pin + 16));  // Reset the pin (write 1 to the corresponding bit in the upper 16 bits)
    }
    return OK;
}