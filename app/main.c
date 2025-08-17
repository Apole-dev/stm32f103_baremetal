#include "gpio.h"
#define EXAMPLE_PIN 13

int main() {
    gpio_handle_t myPort = {
        .port = PORT_A,
        .pin = EXAMPLE_PIN,
        .mode = GPIO_MODE_OUTPUT_PP,
        .speed = GPIO_SPEED_FAST,
    };

    gpio_init_pin(&myPort);
}
