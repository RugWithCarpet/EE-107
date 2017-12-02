#include <stdio.h>
#include <msp430.h>
#include "driverlib.h"
#include "led.h"
#include "adc.h"
#include "mom_button.h"

uint8_t volatile recording = 0;

int main(void)
{
	WDT_A_hold(WDT_A_BASE); // stop watchdog
	PMM_unlockLPM5(); //does this have to be done before or after changing pin settings?

	CS_setExternalClockSource(32000, 8000000); //LFXT is 32KHz, HFXT is 8MHz
	CS_turnOnHFXT(CS_HFXT_DRIVE_4MHZ_8MHZ); //turn on HFXT

    CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1); //Set MCLK to DCO, with divider=1
    CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_2); //Set SMCLK to DCO, with divider=2

	button_init();
    led_init();
    adc_init();
    //still need to configure SPI to communicate with SD card (like in lab2)

    __enable_interrupt(); //enable global interrupts

    while (true) {
    	if (recording) {
    	    ADC12_B_startConversion(ADC12_B_START_AT_ADC12MEM5, ADC12_B_REPEATED_SINGLECHANNEL);
    	    //does DMA need to enabled here or can it be enabled from the beginning?
    	} else {
    		//stop ADC conversions, stop DMA?,s start SD card transfer
    	}
    }

    return 0;
}

#pragma vector=PORT4_VECTOR
__interrupt void PORT4_ISR (void) {
	led_toggle();
	button_clearInterrupt();
	if(recording) { //stop recording
		recording = 0;
	} else { //start recording
		recording = 1;
	}
}
