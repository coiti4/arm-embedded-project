#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>
#include "./CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
#include "led.h"

#define MAKE_DEFAULT_HANDLER(handler_name) \
    void __attribute__((weak)) (handler_name)(void){\
        __disable_irq(); \
        while(1); \
        }

void irq_init(void);

//void EXTI15_10_IRQHandler (void);

#endif