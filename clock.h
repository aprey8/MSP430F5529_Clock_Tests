/*
 * system_clock.h
 *
 *  Created on: Aug 9, 2016
 *      Author: jzhai
 */

#ifndef DIOXIDE_EXPERIMENT_SUPPORT_CLIENT_UART_CLOCK_H_
#define DIOXIDE_EXPERIMENT_SUPPORT_CLIENT_UART_CLOCK_H_

#include <msp430.h>
#include <stdint.h>

extern uint8_t frequency_mhz;

void clock_init_mhz(uint8_t frequency_mhz);

#endif /* DIOXIDE_EXPERIMENT_SUPPORT_CLIENT_UART_CLOCK_H_ */
