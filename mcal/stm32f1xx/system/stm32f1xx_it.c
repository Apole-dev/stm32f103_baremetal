#include "stm32f1xx.h"

/* Cortex-M3 Exception Handlers */

void NMI_Handler(void)
{
    while (1);
}

void HardFault_Handler(void)
{
    while (1);
}

void MemManage_Handler(void)
{
    while (1);
}

void BusFault_Handler(void)
{
    while (1);
}

void UsageFault_Handler(void)
{
    while (1);
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
}

/* Peripheral Interrupt Handlers */

/* Example: 
void EXTI0_IRQHandler(void)
{
    GPIO pin 0 dış kesmesi için handler
}
*/
