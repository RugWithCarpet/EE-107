/*
 * spi.c
 *
 *  Created on: Dec 3, 2017
 *      Author: Vickram Gidwani
 */

#include "spi.h"

void SPI_init(void) {
	//Configure UCB0CLK on Pin 2.2 to be SPI Clock
	GPIO_setAsPeripheralModuleFunctionInputPin(
			GPIO_PORT_P2,
			GPIO_PIN2,
			GPIO_SECONDARY_MODULE_FUNCTION
			);

	//Configure 1.6 and 1.7 to be MOSI and MISO, respectively
	GPIO_setAsPeripheralModuleFunctionInputPin(
			GPIO_PORT_P1,
			GPIO_PIN6 + GPIO_PIN7,
			GPIO_SECONDARY_MODULE_FUNCTION
			);

	//Configure SD Chip Select on Pin 2.0 to be in Output Mode and High
	GPIO_setAsOutputPin(
			GPIO_PORT_P2,
			GPIO_PIN0
			);
	GPIO_setOutputHighOnPin(
			GPIO_PORT_P2,
			GPIO_PIN0
			);

	//Configure and Initialize SPI
    EUSCI_B_SPI_initMasterParam param = {0};
    param.selectClockSource = EUSCI_B_SPI_CLOCKSOURCE_SMCLK; //set clocksource to be SMCLK
    param.clockSourceFrequency = CLOCK_FREQ; //clock frequency from predefined constant
    param.desiredSpiClock = DESIRED_SPI_FREQ; //predefined constant
    param.msbFirst = EUSCI_B_SPI_MSB_FIRST; //Most Significant Bit First
    param.clockPhase = EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    param.clockPolarity = EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH; //clock polarity is INACTIVE on HIGH
    param.spiMode = EUSCI_B_SPI_3PIN; //3 pin mode
    EUSCI_B_SPI_initMaster(EUSCI_B0_BASE, &param); //initialize SPI

	EUSCI_B_SPI_enable(EUSCI_B0_BASE);
	EUSCI_B_SPI_clearInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_RECEIVE_INTERRUPT); //clear outstanding receive interrupts
	EUSCI_B_SPI_enableInterrupt(EUSCI_B0_BASE, (EUSCI_B_SPI_TRANSMIT_INTERRUPT | EUSCI_B_SPI_RECEIVE_INTERRUPT)); //use driverlib to enable interrupts for SPI
}

void SPI_sendFrame(uint8_t *pBuffer, uint16_t size) {
	__disable_interrupt(); //disable global interrupts to make writing an atomic action
	uint16_t i;
	for (i = 0; i < size; i++) {
		while(!EUSCI_B_SPI_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT)); //wait until TRANSMIT INTERRUPT flag is high so ready to tx
		EUSCI_B_SPI_transmitData(EUSCI_B0_BASE, pBuffer[i]);
	}
	while(EUSCI_B_SPI_isBusy(EUSCI_B0_BASE) == EUSCI_B_SPI_BUSY);  //wait until SPI is no longer busy
	__enable_interrupt(); //re-enable global interrupts
}
