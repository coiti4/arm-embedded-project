#include "./CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
#include <stdint.h>
#include <stddef.h>

void uart_init(){
    //activate clock B
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    //PB6 used with an alternate function
    GPIOB->MODER = (GPIOB->MODER & ~ GPIO_MODER_MODE6_Msk)|(0b10 << GPIO_MODER_MODE6_Pos);

    //PB7 used with an alternate function
    GPIOB->MODER = (GPIOB->MODER & ~ GPIO_MODER_MODE7_Msk)|(0b10 << GPIO_MODER_MODE7_Pos);

    //PB6 it's USART1_TX
    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~ GPIO_AFRL_AFSEL6_Msk)|(0b0111 << GPIO_AFRL_AFSEL6_Pos); //AF7 = 011

    //PB7 it's USART1_RX
    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~ GPIO_AFRL_AFSEL7_Msk)|(0b0111 << GPIO_AFRL_AFSEL7_Pos);

    //USART1 clock enable: I suppose PCLK2 max freq=80MHz
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    //USART1 clock source selection: PCLK
    RCC->CCIPR = (RCC->CCIPR & ~ RCC_CCIPR_USART1SEL_Msk)|(00 << RCC_CCIPR_USART1SEL_Pos); //PCLK = 00

    //USART1 reset
    RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST; //set 1
    RCC->APB2RSTR &= (~RCC_APB2RSTR_USART1RST); //set 0

    //USART1 with oversampling by 16
    USART1->CR1 &= (~USART_CR1_OVER8);//set 0

    //USART1 in mode 8N1
    USART1->CR1 = (USART1->CR1 & ~ USART_CR1_M1_Msk)|(0 << USART_CR1_M1_Pos); //Start bit, 8 data bits, n stop bits
    USART1->CR1 = (USART1->CR1 & ~ USART_CR1_M0_Msk)|(0 << USART_CR1_M0_Pos);
    USART1->CR2 = (USART1->CR2 & ~ USART_CR2_STOP_Msk)|(00 << USART_CR2_STOP_Pos); //1 stop bit
    USART1->CR1 &= (~USART_CR1_PCE); //Parity control disabled  

    //USART1 baud rate register
    USART1->BRR = 694; // USARTDIV = 80MHz/115200 baudios

    //USART1 activation
    USART1->CR1 |= USART_CR1_UE; //USART enabled

    //USART1 TX enable
    USART1->CR1 |= USART_CR1_TE;

    //USART1 RX enable
    USART1->CR1 |= USART_CR1_RE;
}

void uart_putchar(uint8_t c){
    while (!(USART1->ISR & USART_ISR_TXE_Msk));
    //x0000000 == 10000000, if TXE=0 then USART1_TDR is busy
    
    //USART1_TDR is available, i.e. TXE=1
    USART1->TDR = c;
}

void uart_puts(const char *s){
    while (*s)
        uart_putchar(*s++);

    uart_putchar('\r'); 
    uart_putchar('\n');
}

uint8_t uart_getchar(){
    
    if(USART1->ISR & USART_ISR_ORE)
        uart_puts("Overrun error");
    else if(USART1->ISR & USART_ISR_FE)
        uart_puts("Framing error");
    else while (!(USART1->ISR & USART_ISR_RXNE_Msk));
    //if RXNE=0 then USART1_RDR is busy
     
    //USART1_TDR is available, i.e. RXNE=1
    return USART1->RDR;
}

void uart_gets(char *s, size_t size){
    size_t i;
    for (i = 0; i < size; i++){
        s[i] = uart_getchar();
        if(s[i] == '\r')
            break;
    }    
    s[i+1] = '\0';
}

uint32_t sum = 0;

void checksum(){
    while (!(USART1->ISR & USART_ISR_RXNE_Msk))
        sum += uart_getchar();
}