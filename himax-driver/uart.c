/*
 * uart.c
 *
 *  Created: 10/2017
 *      Author: Vickram Gidwani
 */

#include "uart.h"

void uart_init() {
	// Configure UART pins
	//Set P2.5 and P2.6 as Secondary Module Function Input.
	GPIO_setAsPeripheralModuleFunctionInputPin(
			GPIO_PORT_P2,
			GPIO_PIN5 + GPIO_PIN6,
			GPIO_SECONDARY_MODULE_FUNCTION
	);

	EUSCI_A_UART_disable(EUSCI_A1_BASE);

	// Configure UART
	EUSCI_A_UART_initParam param = {0};
	param.uartMode = EUSCI_A_UART_MODE;
	param.parity = EUSCI_A_UART_NO_PARITY; //no parity bits
	param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST; //least significant bit first
	param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT; //one stop bit
	//Baud rate: user guide page 762, http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
	// want baud rate of 230400
	// UCBRx: N = 2MHz/230400
	// UCBRSx: N-INT(N) = 0.6806
	// From table 30-4, we need to set UCBRSx to 0xD6
	param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK; //2MHz
	param.overSampling = EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;
	param.secondModReg = 0xD6; //Sets UCBRSx
	param.clockPrescalar = 8; //sets UCBRx
	param.firstModReg = 0;

	//initialize A_UART
	if(STATUS_FAIL == EUSCI_A_UART_init(EUSCI_A1_BASE, &param)) {return;}
	EUSCI_A_UART_enable(EUSCI_A1_BASE);//enable
	//clear outstanding interrupts
	EUSCI_A_UART_clearInterrupt(EUSCI_A1_BASE,
								EUSCI_A_UART_RECEIVE_INTERRUPT);
	return;
}

void uart_tx_byte(uint8_t data) {
	EUSCI_A_UART_transmitData(EUSCI_A1_BASE, data);
}

uint8_t uart_rx_byte() {
	return EUSCI_A_UART_receiveData(EUSCI_A1_BASE);
}
