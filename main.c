#include <msp430.h> 
#include "clock.h"
#include "gpio.h"

#define NOP_CYCLES1 100
#define NOP_CYCLES2 65000

/*
 * main.c
 * This is code to test power consumption at different clock speeds during nops and sleep
 */
uint16_t i;
//void SetVcoreUp (unsigned int level);

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    gpio_init();

    P2DIR |= 0x01;
    P2OUT |= 0x01;
    P2OUT &= 0x01;
    P2OUT |= 0x01;

    for(i = NOP_CYCLES1; i > 0; i--) {
    	__delay_cycles(1000);
    }

    clock_init_mhz(16);
    for(i = NOP_CYCLES2; i > 0; i--) {
    	__no_operation();
    }

//    clock_init_mhz(2);
//    for(i = NOP_CYCLES2; i > 0; i--) {
//    	__no_operation();
//    }

//    clock_init_mhz(4);
//    for(i = NOP_CYCLES2; i > 0; i--) {
//    	__no_operation();
//    }

//    clock_init_mhz(8);
//    for(i = NOP_CYCLES2; i > 0; i--) {
//    	__no_operation();
//    }
////
//    clock_init_mhz(16);
//    for(i = NOP_CYCLES2; i > 0; i--) {
//    	__no_operation();
//    }
    //_BIS_SR(LPM4_bits); // Enter LPM3 w/interrupt

	return 0;
}
