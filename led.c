//#define GPIOEN (*(volatile uint32_t *) 0x4002104C) //address AHB1 RCC, enable clock
//#define BMODER (*(volatile uint32_t *) 0x48000400) //select input/output mode
//#define CMODER (*(volatile uint32_t *) 0x48000800) //select input/output mode
//#define GPIOB_BSRR (*(volatile uint32_t *) 0x48000418) //write in the B peripheric
//#define GPIOC_BSRR (*(volatile uint32_t *) 0x48000818) //write in the C peripheric

#include <stdint.h>
#include "led.h"
#include "./CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"

void led_init(){ //elle se chargera d'initialiser le périphérique: activation de l'horloge associée, configuration diverse, etc.
    //led verte
    //GPIOEN = (GPIOEN | 2); // B clock enable
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    //BMODER = (BMODER & ~ (3 << 28))|((3 & 01) << 28); //2b a la position 28 dans le registre BMODER pour mettre en mode sortie le PB14
    GPIOB->MODER = (GPIOB->MODER & ~ GPIO_MODER_MODE14_Msk)|(01 << GPIO_MODER_MODE14_Pos);

    //led bleue jaune
    //GPIOEN = (GPIOEN | 4);
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
}

void led_g_on(){
//allumer led2
    //GPIOB_BSRR |= (1 << 14);
    GPIOB->BSRR = (1 << GPIO_BSRR_BS14_Pos);
}

void led_g_off(){
    GPIOB->BSRR = (1 << GPIO_BSRR_BR14_Pos);
    //GPIOB_BSRR = (GPIOB_BSRR | (1 << 30));
}

void led(enum state S){
    if (S == LED_OFF){
        //port as input, all off
        GPIOC->MODER = (GPIOC->MODER & ~ GPIO_MODER_MODE9_Msk)|(00 << GPIO_MODER_MODE9_Pos); //2b a la position 18 dans le registre CMODER pour mettre en mode entree le PC9
    }
    else{
        //port as output
        //CMODER = (CMODER & ~ (3 << 18))|((3 & 01) << 18); //2b a la position 18 dans le registre CMODER pour mettre en mode sortie le PC9
        GPIOC->MODER = (GPIOC->MODER & ~ GPIO_MODER_MODE9_Msk)|(01 << GPIO_MODER_MODE9_Pos);
        if (S == LED_YELLOW)
        //yellow on
            GPIOC->BSRR = (1 << GPIO_BSRR_BS9_Pos);
            //GPIOC_BSRR = GPIOC_BSRR | (1 << 9);
        else
        //blue on
            GPIOC->BSRR = (1 << GPIO_BSRR_BR9_Pos);
            //GPIOC_BSRR = GPIOC_BSRR | (1 << 25);
    }
}