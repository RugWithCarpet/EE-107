/*
 * uart.h
 *
 */

#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include <stdint.h>
#include <msp430.h>
#include "driverlib.h"

void uart_init();
inline void uart_tx_byte(uint8_t data);
inline uint8_t uart_rx_byte();

#endif /* UART_H_ */
