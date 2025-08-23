# STM32F103 Bare-Metal Development Environment
Documentation section hi :)

## GPIO Init Example
This example shows how to initialize a GPIO pin using the gpio_handle_t struct and gpio_init_pin() function in STM32F103 bare-metal.
``` c
//Example: GPIO Initialization
gpio_handle_t myPort ={
    .port  = PORT_A,
    .pin   = EXAMPLE_PIN,
    .mode  = GPIO_MODE_OUTPUT_PP,
    .speed = GPIO_SPEED_FAST,
};
gpio_init_pin(&myPort);

```
``` c

//Example: Set Clock
rcc_set_config(PLL_HSE_MAX_72MHZ);
/* Config
 * HSI_INTERNAL_CLK_8MHZ,
 * HSE_EXTERNAL_CLK_8MHZ,
 * PLL_HSI_MAX_64MHZ,
 * PLL_HSE_MAX_72MHZ,*/
```
