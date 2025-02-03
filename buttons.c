#include "buttons.h"
#include "./CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
#include <stdint.h>
#include "led.h"


void button_init(void){
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;  //Clock PC active

    GPIOC->MODER &= ~GPIO_MODER_MODE13_Msk;  //configuration broche PC13 en mode in

    SYSCFG->EXTICR[3] = (SYSCFG->EXTICR[3] &~ SYSCFG_EXTICR4_EXTI13_Msk)|(SYSCFG_EXTICR4_EXTI13_PC); //broche PC13 comme source d'IRQ pour EXTI13 

    //configure l'EXTI selon la procédure décrite en 14.3.4.
    EXTI->IMR1 |= EXTI_IMR1_IM13_Msk; 

    EXTI->RTSR1 &= ~EXTI_RTSR1_RT13; //rising

    EXTI->FTSR1 |= EXTI_FTSR1_FT13; //falling

    //__enable_irq();
    NVIC_EnableIRQ(40); //< External Line[15:10] Interrupts
}

void EXTI15_10_IRQHandler(void) {
    __disable_irq();
    EXTI->PR1 |= EXTI_PR1_PIF13_Msk; //acquittement de l'interruption dans l'EXTI
    led_g_on();
    for(uint32_t i=0; i <20000; i++) {
        asm volatile ("nop");
    };
    led_g_off();
    __enable_irq();
}