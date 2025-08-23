#ifndef NVIC_H
#define NVIC_H

#include "stm32f103xb.h"
void nvic_enable_interrupt_request(IRQn_Type irq);
void nvic_disable_interrupt_request(IRQn_Type irq);

#endif /* NVIC_H */
