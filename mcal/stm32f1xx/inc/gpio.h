#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include <stdint.h>

#include "stm32f103xb.h"

// Functional state for error handling
typedef enum {
    OK,
    INIT_FAIL,
    WRITE_FAIL,
    READ_FAIL,
    CLEAR_FAIL,
} Functional_State;

// Pin mode
typedef enum {
    GPIO_MODE_INPUT_ANALOG,
    GPIO_MODE_INPUT_FLOATING,
    GPIO_MODE_INPUT_PULL,
    GPIO_MODE_OUTPUT_PP,  // Push-Pull
    GPIO_MODE_OUTPUT_OD,  // Open-Drain
    GPIO_MODE_AF_PP,      // Alternate Function Push-Pull
    GPIO_MODE_AF_OD       // Alternate Function Open-Drain
} GPIO_Mode_t;

// Pin speed
typedef enum {
    GPIO_SPEED_LOW,     // 10 MHz
    GPIO_SPEED_MEDIUM,  // 2 MHz
    GPIO_SPEED_FAST     // 50 MHz
} GPIO_Speed_t;

// Port selection
typedef enum {
    PORT_A = 2,
    PORT_B = 3,
    PORT_C = 4,
    PORT_D = 5,
    PORT_E = 6,
} GPIO_Port_t;

// Struct representing a GPIO pin
typedef struct {
    GPIO_Port_t port;
    uint8_t pin;
    GPIO_Mode_t mode;
    GPIO_Speed_t speed;
} gpio_handle_t;

// Function prototypes
Functional_State gpio_init_pin(gpio_handle_t *h);
Functional_State gpio_write_pin(gpio_handle_t *h, bool on_off);
Functional_State gpio_read_pin(gpio_handle_t *h, bool *state);
Functional_State gpio_clear_port(GPIO_Port_t port);
Functional_State gpio_set_af_mode(gpio_handle_t *h);
Functional_State gpio_set_config(GPIO_Port_t port, uint8_t pin, GPIO_Mode_t mode, GPIO_Speed_t speed);
Functional_State gpio_test_port(GPIO_Port_t port);

// Internal helper
GPIO_TypeDef *port_gpio(GPIO_Port_t port);

/*These functions only works in bluepill boards */
#ifdef BLUEPILL_F103

#define LED_PORT GPIOC
#define LED_PIN 13

// Test Functions
void led_set();
#endif

#endif  // GPIO_H
