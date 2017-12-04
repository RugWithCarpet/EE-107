/*
 * uart.c
 *
 *  Created: 10/2017
 *      Author: Vickram Gidwani
 */

#include "uart.h"

void uart_init() {
	// LAB 2 CODE
	// * Setup crystal clock (LFXT low frequency crystal) on Port J
	// * Set Pin 4, 5 to input Primary Module Function, LFXT.
	// * Math is easier for baud rate with this low-frequency clock.

	GPIO_setAsPeripheralModuleFunctionInputPin(
			GPIO_PORT_PJ,
			GPIO_PIN4 + GPIO_PIN5,
			GPIO_PRIMARY_MODULE_FUNCTION
	);

	//Set ACLK=LFXT
	CS_initClockSignal(CS_ACLK,CS_LFXTCLK_SELECT,CS_CLOCK_DIVIDER_1);
	//Start XT1 with no time out
	CS_turnOnLFXT(CS_LFXT_DRIVE_0);

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
	//Baud rate: user guide page 762
	// N = 32.768kHz/9600, N-INT(N) = 0.413333
	// From table 30-4, we need to set UCBRSx to 0x08
	// and set UCBRx to 3
	param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_ACLK; //32.768kHz
	param.overSampling = EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION; //oversampling is off because we're using LFCLK
	param.secondModReg = 0x92; //Sets UCBRSx
	param.clockPrescalar = 3; //sets UCBRx

	//initialize A_UART
	if(STATUS_FAIL == EUSCI_A_UART_init(EUSCI_A1_BASE, &param)) {return;}
	EUSCI_A_UART_enable(EUSCI_A1_BASE);//enable
	//clear outstanding interrupts
	EUSCI_A_UART_clearInterrupt(EUSCI_A1_BASE,
								EUSCI_A_UART_RECEIVE_INTERRUPT);
	return;

/*	 set UART pin function
	    GPIO_setAsPeripheralModuleFunctionInputPin(
	        GPIO_PORT_P2,
	        GPIO_PIN5 + GPIO_PIN6,
	        GPIO_SECONDARY_MODULE_FUNCTION
	    );

	     reset UART module
	    EUSCI_A_UART_disable(EUSCI_A1_BASE);

	     prepare UART configuration struct
	    EUSCI_A_UART_initParam param = {0};
	    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;
	    param.clockPrescalar = 2;
	    param.firstModReg = 2;
	    param.secondModReg = 0xBB;
	    param.parity = EUSCI_A_UART_NO_PARITY;
	    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
	    param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
	    param.uartMode = EUSCI_A_UART_MODE;
	    param.overSampling = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;

	     configure UART module and enable it
	    EUSCI_A_UART_init(EUSCI_A1_BASE, &param);
	    EUSCI_A_UART_enable(EUSCI_A1_BASE);
	    EUSCI_A_UART_clearInterrupt(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
	    return;*/
}

void uart_tx_byte(uint8_t data) {
	EUSCI_A_UART_transmitData(EUSCI_A1_BASE, data);
}

uint8_t uart_rx_byte() {
	return EUSCI_A_UART_receiveData(EUSCI_A1_BASE);
}
