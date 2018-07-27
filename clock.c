/*
 * system_clock.c
 *
 *  Created on: Aug 9, 2016
 *      Author: jzhai
 */

#include "clock.h"

uint8_t frequency_mhz;

void clock_init_mhz(uint8_t _frequency_mhz) {
	frequency_mhz = _frequency_mhz;

	P5SEL |= BIT4 + BIT5;		// Set P5.4 and P5.5 as XT1
	UCSCTL6 &= ~(XT1OFF);                     // XT1 On
	UCSCTL6 |= XCAP_3;                        // Internal load cap 12pF
											  // XCAP_0: 1pF; XCAP_1: 5.5 pF; XCAP_2: 8.5 pF
	UCSCTL3 = 0;                              // FLL Reference Clock = XT1
	UCSCTL4 = SELA__XT1CLK + SELM__DCOCLKDIV + SELS__DCOCLKDIV; // ACLK = LFTX1 (by default)

	// Loop until XT1,XT2 & DCO stabilizes - In this case loop until XT1 and DC0 settle
	do {
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
		// Clear XT2,XT1,DCO fault flags
		SFRIFG1 &= ~OFIFG;                      // Clear fault flags
	} while (SFRIFG1 & OFIFG);                   // Test oscillator fault flag

	UCSCTL6 &= ~(XT1DRIVE_3);       // Xtal is now stable, reduce drive strength
									// XT1 Driver change to XT1DRIVE_0
	__bis_SR_register(SCG0);                  // Disable the FLL control loop

	UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx

	 // The appropriate value for DCORSEL is obtained from the DCO
	 // Frequency table of the device datasheet.  Find the DCORSEL
	 // value from that table where the minimum frequency with DCOx=31
	 // is closest to your desired DCO frequency.
	switch (frequency_mhz) {
	case 1:
		UCSCTL1 = DCORSEL_3;
		UCSCTL2 = FLLD_1 + 31;
		break;
	case 2:
		UCSCTL1 = DCORSEL_4;
		UCSCTL2 = FLLD_1 + 63;
		break;
	case 4:
		UCSCTL1 = DCORSEL_5;
		UCSCTL2 = FLLD_1 + 127;
		break;
	case 8:
		UCSCTL1 = DCORSEL_6;
		UCSCTL2 = FLLD_1 + 255;
		break;
	case 16:
		UCSCTL1 = DCORSEL_7;
		UCSCTL2 = FLLD_1 + 511;
		break;

	}
	__bic_SR_register(SCG0);                  // Enable the FLL control loop
	// Worst-case settling time for the DCO when the DCO range bits have been
	// changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
	// UG for optimization.
	// 32 x 32 x X MHz / 32,768 Hz = Y = MCLK cycles for DCO to settle
	switch (frequency_mhz) {
	case 1:
		__delay_cycles(32768);
		break;
	case 2:
		__delay_cycles(65536);
		break;
	case 4:
		__delay_cycles(131072);
		break;
	case 8:
		__delay_cycles(262144);
		break;
	case 16:
		__delay_cycles(524288);
		break;
	}
}
