//init.c
//extracted from Compilation slides (page 113)-SE203
#include <stdint.h>
#include "memfuncs.h"

extern uint8_t _bstart, _bend;

void init_bss(){
    uint8_t *dst; //always the access are every 8b
    //Zero out bss
    for (dst = &_bstart; dst < &_bend; dst++)
        *dst = 0;
}