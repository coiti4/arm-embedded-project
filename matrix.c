#include<stdint.h>
#include "./CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
#include "matrix.h"

void RST(bool x){
    if (x==0) //reboot
        GPIOC->BSRR = (GPIOC->BSRR &~ GPIO_BSRR_BR3_Msk)|(1 << GPIO_BSRR_BR3_Pos);
    else
        GPIOC->BSRR = (GPIOC->BSRR &~ GPIO_BSRR_BS3_Msk)|(1 << GPIO_BSRR_BS3_Pos); 
}

void SB(bool x){
    if(x==0)
        GPIOC->BSRR = (GPIOC->BSRR &~ GPIO_BSRR_BR5_Msk)|(1 << GPIO_BSRR_BR5_Pos);
    else
        GPIOC->BSRR = (GPIOC->BSRR &~ GPIO_BSRR_BS5_Msk)|(1 << GPIO_BSRR_BS5_Pos);
}

void LAT(bool x){
    if(x==0)
        GPIOC->BSRR = (GPIOC->BSRR &~ GPIO_BSRR_BR4_Msk)|(1 << GPIO_BSRR_BR4_Pos);
    else
        GPIOC->BSRR = (GPIOC->BSRR &~ GPIO_BSRR_BS4_Msk)|(1 << GPIO_BSRR_BS4_Pos);
} 

void SCK(bool x){
    if (x==0)
        GPIOB->BSRR = (GPIOB->BSRR &~ GPIO_BSRR_BR1_Msk)|(1 << GPIO_BSRR_BR1_Pos);
    else
        GPIOB->BSRR = (GPIOB->BSRR &~ GPIO_BSRR_BS1_Msk)|(1 << GPIO_BSRR_BS1_Pos);

}

void SDA(bool x){
    if (x==0)
        GPIOA->BSRR = (GPIOA->BSRR &~ GPIO_BSRR_BR4_Msk)|(1 << GPIO_BSRR_BR4_Pos);
    else
        GPIOA->BSRR = (GPIOA->BSRR &~ GPIO_BSRR_BS4_Msk)|(1 << GPIO_BSRR_BS4_Pos);
}

void ROW0(bool x){
    if (x==0)
        GPIOB->BSRR = (GPIOB->BSRR &~ GPIO_BSRR_BR2_Msk)|(1<< GPIO_BSRR_BR2_Pos);
    else
        GPIOB->BSRR = (GPIOB->BSRR &~ GPIO_BSRR_BS2_Msk)|(1 << GPIO_BSRR_BS2_Pos);
}

void ROW1(bool x){
    if (x==0)
        GPIOA->BSRR = (GPIOA->BSRR &~ GPIO_BSRR_BR15_Msk)|(1<< GPIO_BSRR_BR15_Pos);
    else
        GPIOA->BSRR = (GPIOA->BSRR &~ GPIO_BSRR_BS15_Msk)|(1<< GPIO_BSRR_BS15_Pos);
}

void ROW2(bool x){
    if (x==0)
        GPIOA->BSRR = (GPIOA->BSRR &~ GPIO_BSRR_BR2_Msk)|(1 << GPIO_BSRR_BR2_Pos);
    else
        GPIOA->BSRR = (GPIOA->BSRR &~ GPIO_BSRR_BS2_Msk)|(1 << GPIO_BSRR_BS2_Pos);
}

void ROW3(bool x){
    if (x==0)
        GPIOA->BSRR = (GPIOA->BSRR &~ GPIO_BSRR_BR7_Msk)|(1 << GPIO_BSRR_BR7_Pos);
    else
        GPIOA->BSRR = (GPIOA->BSRR &~ GPIO_BSRR_BS7_Msk)|(1 << GPIO_BSRR_BS7_Pos);
}

void ROW4(bool x){
    if (x==0)
        GPIOA->BSRR = (GPIOA->BSRR &~ GPIO_BSRR_BR6_Msk)|(1 << GPIO_BSRR_BR6_Pos);
    else
        GPIOA->BSRR = (GPIOA->BSRR &~ GPIO_BSRR_BS6_Msk)|(1 << GPIO_BSRR_BS6_Pos);
}

void ROW5(bool x){
    if (x==0)
        GPIOA->BSRR = (GPIOA->BSRR &~ GPIO_BSRR_BR5_Msk)|(1 << GPIO_BSRR_BR5_Pos);
    else
        GPIOA->BSRR = (GPIOA->BSRR &~ GPIO_BSRR_BS5_Msk)|(1 << GPIO_BSRR_BS5_Pos);
}

void ROW6(bool x){
    if (x==0)
        GPIOB->BSRR = (GPIOB->BSRR &~ GPIO_BSRR_BR0_Msk)|(1 << GPIO_BSRR_BR0_Pos);
    else
        GPIOB->BSRR = (GPIOB->BSRR &~ GPIO_BSRR_BS0_Msk)|(1 << GPIO_BSRR_BS0_Pos);
}

void ROW7(bool x){
    if (x==0)
        GPIOA->BSRR = (GPIOA->BSRR &~ GPIO_BSRR_BR3_Msk)|(1 << GPIO_BSRR_BR3_Pos);
    else
        GPIOA->BSRR = (GPIOA->BSRR &~ GPIO_BSRR_BS3_Msk)|(1 << GPIO_BSRR_BS3_Pos);
}

void init_bank0(){
    //we don't use this bank so in order to desactive it 
    for (int8_t i=0; i<24; i++)
        send_byte(255, 0); 
    pulse_LAT();
}

void matrix_init(){
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;  //Clock PA active
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;  //Clock PB active
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;  //Clock PC active

    GPIOA->MODER =(GPIOA->MODER &~ GPIO_MODER_MODE2_Msk)|(01 << GPIO_MODER_MODE2_Pos);  //configuration broche 2 en mode out
    GPIOA->MODER =(GPIOA->MODER &~ GPIO_MODER_MODE3_Msk)|(01 << GPIO_MODER_MODE3_Pos);  //configuration broche 3 en mode out
    GPIOA->MODER =(GPIOA->MODER &~ GPIO_MODER_MODE4_Msk)|(01 << GPIO_MODER_MODE4_Pos);  //configuration broche 4 en mode out
    GPIOA->MODER =(GPIOA->MODER &~ GPIO_MODER_MODE5_Msk)|(01 << GPIO_MODER_MODE5_Pos);  //configuration broche 5 en mode out
    GPIOA->MODER =(GPIOA->MODER &~ GPIO_MODER_MODE6_Msk)|(01 << GPIO_MODER_MODE6_Pos);  //configuration broche 6 en mode out
    GPIOA->MODER =(GPIOA->MODER &~ GPIO_MODER_MODE7_Msk)|(01 << GPIO_MODER_MODE7_Pos);  //configuration broche 7 en mode out
    GPIOA->MODER =(GPIOA->MODER &~ GPIO_MODER_MODE15_Msk)|(01 << GPIO_MODER_MODE15_Pos);  //configuration broche 15 en mode out

    GPIOB->MODER =(GPIOB->MODER &~ GPIO_MODER_MODE0_Msk)|(01 << GPIO_MODER_MODE0_Pos);  //configuration broche 0 en mode out
    GPIOB->MODER =(GPIOB->MODER &~ GPIO_MODER_MODE1_Msk)|(01 << GPIO_MODER_MODE1_Pos);  //configuration broche 1 en mode out
    GPIOB->MODER =(GPIOB->MODER &~ GPIO_MODER_MODE2_Msk)|(01 << GPIO_MODER_MODE2_Pos);  //configuration broche 2 en mode out

    GPIOC->MODER =(GPIOC->MODER &~ GPIO_MODER_MODE3_Msk)|(01 << GPIO_MODER_MODE3_Pos);  //configuration broche 3 en mode out
    GPIOC->MODER =(GPIOC->MODER &~ GPIO_MODER_MODE4_Msk)|(01 << GPIO_MODER_MODE4_Pos);  //configuration broche 4 en mode out
    GPIOC->MODER =(GPIOC->MODER &~ GPIO_MODER_MODE5_Msk)|(01 << GPIO_MODER_MODE5_Pos);  //configuration broche 5 en mode out

    //vitesse
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~ GPIO_OSPEEDR_OSPEED2_Msk)|(0b11 << GPIO_OSPEEDR_OSPEED2_Pos); 
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~ GPIO_OSPEEDR_OSPEED3_Msk)|(0b11 << GPIO_OSPEEDR_OSPEED3_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~ GPIO_OSPEEDR_OSPEED4_Msk)|(0b11 << GPIO_OSPEEDR_OSPEED4_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~ GPIO_OSPEEDR_OSPEED5_Msk)|(0b11 << GPIO_OSPEEDR_OSPEED5_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~ GPIO_OSPEEDR_OSPEED6_Msk)|(0b11 << GPIO_OSPEEDR_OSPEED6_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~ GPIO_OSPEEDR_OSPEED7_Msk)|(0b11 << GPIO_OSPEEDR_OSPEED7_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR &~ GPIO_OSPEEDR_OSPEED15_Msk)|(0b11 << GPIO_OSPEEDR_OSPEED15_Pos);

    GPIOB->OSPEEDR = (GPIOB->OSPEEDR &~ GPIO_OSPEEDR_OSPEED0_Msk)|(0b11 << GPIO_OSPEEDR_OSPEED0_Pos);
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR &~ GPIO_OSPEEDR_OSPEED1_Msk)|(0b11 << GPIO_OSPEEDR_OSPEED1_Pos);
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR &~ GPIO_OSPEEDR_OSPEED2_Msk)|(0b11 << GPIO_OSPEEDR_OSPEED2_Pos);

    GPIOC->OSPEEDR = (GPIOC->OSPEEDR &~ GPIO_OSPEEDR_OSPEED3_Msk)|(0b11 << GPIO_OSPEEDR_OSPEED3_Pos);
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR &~ GPIO_OSPEEDR_OSPEED4_Msk)|(0b11 << GPIO_OSPEEDR_OSPEED4_Pos);
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR &~ GPIO_OSPEEDR_OSPEED5_Msk)|(0b11 << GPIO_OSPEEDR_OSPEED5_Pos);

    //valeur initial acceptable
    //RST : 0 (reset le DM163)
    RST(0);
    LAT(1);
    SB(1);
    SDA(0);
    SCK(0);
    
    //Lines C0-C7 set to zero

    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);   

    //sleep(0.1); //wait 100ms, chequear
    for (int32_t i=0; i<9000000; i++) //au moin 100ms d'attente
        asm volatile ("nop");
    
    //RST high
    RST(1);

    init_bank0(); //its necessary to set before in order to do this
}

void pulse_SCK(){
    SCK(0);
    for (int8_t i=0; i<3; i++) //37.5ns d'attente
        asm volatile ("nop");
    SCK(1);
    for (int8_t i=0; i<3; i++)
        asm volatile ("nop");
    SCK(0);
    for (int8_t i=0; i<3; i++)
        asm volatile ("nop");
}

void pulse_LAT(){
    LAT(1);
    for (int8_t i=0; i<3; i++)
        asm volatile ("nop");
    LAT(0);
    asm volatile ("nop"); //attente au moin de 7 ns
    LAT(1);
    for (int8_t i=0; i<3; i++)
        asm volatile ("nop");
}

void deactivate_rows(){
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
}

void activate_row(int row){
    switch (row){
        case 0:
            ROW0(1);
            break;
        case 1:
            ROW1(1);
            break;
        case 2:
            ROW2(1);
            break;
        case 3:
            ROW3(1);
            break;
        case 4:
            ROW4(1);
            break;
        case 5:
            ROW5(1);
            break;
        case 6:
            ROW6(1);
            break;
        case 7:
            ROW7(1);
    }
}

void send_byte(uint8_t val, int bank){
    //bank soit 0 soit 1, val deja rgb encoded
    SB(bank);
    LAT(1);
    int j;
    if (bank==1)
        j = 7;
    else //bank=0
        j = 5;
    for (int8_t i=j; i>=0; i--){
        if((val & (1 << i)) == (1 << i))
            SDA(1);
        else
            SDA(0);
    pulse_SCK();
    }
}

void mat_set_row(int row, const rgb_color * val){
    for (int8_t i=0; i<8; i++){
        send_byte(val->b,1);
        send_byte(val->g,1);
        send_byte(val->r,1);
        val++;
    }
    deactivate_rows();  //important to desactivate all rows before
    activate_row(row);
    pulse_LAT();
}

void test_row(int row){
    for (int8_t i=0; i<8; i++){
        send_byte(0,1);
        send_byte(255,1);
        send_byte(0,1);
    }
    activate_row(row);
    pulse_LAT();
}

void test_pixels(){

    rgb_color azul[8];
    uint8_t color = 255;
    for (int8_t i=0; i<=7; i++){
        (azul[i]).b = color>>i; //it divides by two allowing us to have a degrade
        (azul[i]).g = 0;
        (azul[i]).r = 0;
    }
    const rgb_color * blue = &azul[7];

    rgb_color verde[8];
    for (int8_t i=0; i<=7; i++){
        (verde[i]).g = color>>i;
        (verde[i]).b = 0;
        (verde[i]).r = 0;
    }
    const rgb_color * green = &verde[7];

    rgb_color rojo[8];
    for (int i=0; i<=7; i++){
        (rojo[i]).r = color>>i;
        (rojo[i]).g = 0;
        (rojo[i]).b = 0;
    }
    const rgb_color * red = &rojo[7];

    while (1){
            mat_set_row(0, blue);
            for (int16_t i=0; i<500; i++)
                asm volatile ("nop");
            mat_set_row(1, green);
            for (int16_t i=0; i<500; i++)
                asm volatile ("nop");
            mat_set_row(2, red);
            for (int16_t i=0; i<500; i++)
                asm volatile ("nop");
            mat_set_row(3, blue);
            for (int16_t i=0; i<500; i++)
                asm volatile ("nop");
            mat_set_row(4, green);
            for (int16_t i=0; i<500; i++)
                asm volatile ("nop");
            mat_set_row(5, red);
            for (int16_t i=0; i<500; i++)
                asm volatile ("nop");
            mat_set_row(6, blue);
            for (int16_t i=0; i<500; i++)
                asm volatile ("nop");
            mat_set_row(7, green);
            for (int16_t i=0; i<500; i++)
                asm volatile ("nop");
        }
}

extern uint8_t _binary_image_raw_start;

void affiche_limage(){
    const rgb_color * read_img = (rgb_color *) (&_binary_image_raw_start);
    while (1){
        for (int8_t i=7; i>=0; i--){
            mat_set_row(i, read_img);
            for (int16_t i=0; i<500; i++)
                asm volatile ("nop");
            read_img = read_img + 8;
        }
    read_img = (rgb_color *) (&_binary_image_raw_start);
    }
}