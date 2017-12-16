/*
 * AUTO-DICTATOR
 * December, 2017
 * EE 107, Stanford
 *
 * Authors: Vickram Gidwani, Raymond Reynolds, Alex Kucy
 *
 * Implements a button-controllable microphone that is sampled by an ADC and audio samples are streamed via UART
 */


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <msp430.h>
#include "driverlib.h"
#include "led.h"
#include "adc.h"
#include "mom_button.h"
#include "uart.h"

bool volatile start_recording = 0;
bool volatile stop_recording = 0;
bool volatile recording = 0;
uint32_t* volatile adc_mem_address = 0;

int main(void)
{
	WDT_A_hold(WDT_A_BASE); // stop watchdog
	PMM_unlockLPM5(); //disable high-impedance mode to configure port settings

	//Use DCO to set MCLK and SMCLK
    CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_6); //Set DCO to 8 MHz
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1); //Set MCLK to DCO, with divider=1 (8 MHz)
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_4); //Set SMCLK to DCO, with divider=4 (2 MHz)
    CS_turnOnSMCLK();

	button_init();
	led_init();
	uart_init();
    adc_init();

    __enable_interrupt(); //enable global interrupts

    adc_mem_address = ADC12_B_getMemoryAddressForDMA(ADC12_B_BASE, ADC12_B_MEMORY_5);

    while (1) {
            if (start_recording) { //button just pressed --> do this once when starting to record
                ADC12_B_startConversion(ADC12_B_BASE, ADC12_B_START_AT_ADC12MEM5, ADC12_B_REPEATED_SINGLECHANNEL); //start cibversions in ADC
                led_on(); //LED indicator that conversions are happening
                recording = 1; //go to 'recording' state
                start_recording = 0; //only happens once so set start_recording to 0
            } else if (stop_recording) { //button just pressed --> do this once when stopping to record
            	led_off(); //LED indicator off
                ADC12_B_disableConversions(ADC12_B_BASE, ADC12_B_PREEMPTCONVERSION); //stop conversions --> interrupt that triggers UART will also stop
                recording = 0; //leave 'recording' state
                stop_recording = 0;
            }
    }
    return 0;
}

#pragma vector=PORT4_VECTOR
__interrupt void PORT4_ISR() {
    if(!recording) { //start recording
		start_recording = 1;
	} else if (recording) {//stop recording
		stop_recording = 1;
	}
    button_clearInterrupt();
}

#pragma vector=ADC12_B_VECTOR
__interrupt void ADC12_ISR() {
	uart_tx_byte(*adc_mem_address); //send sample value; disables interrupts while sending (in SPI_sendFrame)
	ADC12_B_clearInterrupt(ADC12_B_BASE, 0, ADC12_B_IFG5);
}
