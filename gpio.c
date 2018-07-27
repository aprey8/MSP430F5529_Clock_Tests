/*
 * system_gpio.c
 *
 *  Created on: Aug 9, 2016
 *      Author: jzhai
 */

#include "gpio.h"

void gpio_init() {
	// Set up the pins to save power
	P1OUT = 0x00;
	P2OUT = 0x00;
	P3OUT = 0x00;
	P4OUT = 0x00;
	P5OUT = 0x00;
	P6OUT = 0x00;
	P7OUT = 0x00;
	P8OUT = 0x00;
	PJOUT = 0x00;
	P1DIR = 0xFF;
	P2DIR = 0xFF;
	P3DIR = 0xFF;
	P4DIR = 0xFF;
	P5DIR = 0xFF;
	P6DIR = 0xFF;
	P7DIR = 0xFF;
	P8DIR = 0xFF;
	PJDIR = 0xFF;
}
