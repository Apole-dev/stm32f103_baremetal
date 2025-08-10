#include <stdbool.h>
#include <stdint.h>

#include "stm32f103xb.h"
#include "stm32f1xx.h"

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
    GPIO_SPEED_LOW,     // STM32F1 : 10MHz
    GPIO_SPEED_MEDIUM,  // STM32F1 : 2MHz
    GPIO_SPEED_FAST     // STM32F1 : 50MHz
} GPIO_Speed_t;

// Eror Status
typedef enum {
    OK,
    INIT_FAIL,
    WRITE_FAIL,
    READ_FAIL,
    CLEAR_FAIL,
} Functional_State;

// Port Number
typedef enum {
    PORT_A = 2,
    PORT_B = 3,
    PORT_C = 4,
    PORT_D = 5,
    PORT_E = 6,
} GPIO_Port_t;

// Main structure
typedef struct {
    GPIO_Port_t port;    // Which port? (ex: GPIOA, GPIOB)
    uint8_t pin;         // Which pin? (ex: 5)
    GPIO_Mode_t mode;    // Pin mode
    GPIO_Speed_t speed;  // Output speed
} GPIO_Config_t;

Functional_State gpio_init(const GPIO_Config_t* config);
Functional_State gpio_write(GPIO_Port_t port, uint8_t pin, bool state);
Functional_State gpio_read(GPIO_Port_t port, uint8_t pin);
Functional_State gpio_clear(GPIO_Port_t port);

/*These functions only works in bluepill boards */
#ifdef BLUEPILL_F103

#define LED_PORT GPIOC
#define LED_PIN 13

// Test Functions
void led_set();

#endif
