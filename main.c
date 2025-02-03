#include "led.h"
#include "./clocks/clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"

#include <stdint.h>

int main (){
	clocks_init();
	irq_init();
	led_init();
	button_init();
	matrix_init();
	affiche_limage();
	while (1);
	return 0;
}
