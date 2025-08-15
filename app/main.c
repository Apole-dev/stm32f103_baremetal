#include "gpio.h"

#define EXAMPLE_PIN 13

int main() {
    gpio_init(PORT_A);
    gpio_write(PORT_A, EXAMPLE_PIN, ENABLE);
}
