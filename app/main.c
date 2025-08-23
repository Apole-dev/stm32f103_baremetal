#include "gpio.h"
#include "rcc.h"
#define EXAMPLE_PIN 13

int main() {
    // Example: Set Clock
    rcc_set_config(HSI_INTERNAL_CLK_8MHZ);

    // Example: Initialize GPIO pin
    gpio_handle_t myPin = {.port = PORT_B, .pin = EXAMPLE_PIN, .mode = GPIO_MODE_AF_PP, .speed = GPIO_SPEED_FAST};
    gpio_init_pin(&myPin);
}
