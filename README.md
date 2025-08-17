# STM32F103 Bare-Metal Development Environment

A professional, modular, and reproducible bare-metal development environment for the STM32F103 (Blue Pill) microcontroller, built on Docker and a custom Makefile. This project is designed to provide a clean, portable, and CI/CD-ready foundation for robust embedded systems development, completely independent of vendor-provided HALs.

## GPIO Init Example
This example shows how to initialize a GPIO pin using the gpio_handle_t struct and gpio_init_pin() function in STM32F103 bare-metal.
``` c
gpio_handle_t myPort ={
    .port  = PORT_A,
    .pin   = EXAMPLE_PIN,
    .mode  = GPIO_MODE_OUTPUT_PP,
    .speed = GPIO_SPEED_FAST,
};
gpio_init_pin(&myPort);

```
