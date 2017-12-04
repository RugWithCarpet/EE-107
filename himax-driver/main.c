#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <msp430.h>
#include "driverlib.h"
#include "led.h"
#include "adc.h"
#include "dma.h"
#include "mom_button.h"
#include "uart.h"

bool volatile start_recording = 0;
bool volatile stop_recording = 0;

#pragma PERSISTENT(snd_buffer)
uint8_t snd_buffer[128000] = {0}; //128 kB of data for sound = (2 sec)(32000 sample/sec)(2 bytes/sample)

int main(void)
{
	WDT_A_hold(WDT_A_BASE); // stop watchdog
	PMM_unlockLPM5(); //does this have to be done before or after changing pin settings?

	CS_setExternalClockSource(32768, 8000000); //LFXT is 32KHz, HFXT is 8MHz
	CS_turnOnHFXT(CS_HFXT_DRIVE_4MHZ_8MHZ); //turn on HFXT

    CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1); //Set MCLK to HFXT, with divider=1 (8 MHz)
    CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_2); //Set SMCLK to HFXT, with divider=2 (4 MHz)

    CS_turnOnSMCLK();

	button_init();
	led_init();
	uart_init();
    adc_init();
    dma_init();

    __enable_interrupt(); //enable global interrupts

	//data is in memory register for ADC channel 5; 2 bytes are transfered at a time -> don't need to change address
	DMA_setSrcAddress(DMA_CHANNEL_0,
					  ADC12_B_getMemoryAddressForDMA(ADC12_B_BASE, ADC12_B_MEMORY_5),
					  DMA_DIRECTION_UNCHANGED
					  );

	DMA_setDstAddress(DMA_CHANNEL_0,
					  (uint32_t) snd_buffer, //does this need to be dereferenced?
					  DMA_DIRECTION_INCREMENT);
	DMA_enableTransfers(DMA_CHANNEL_0); //won't start until ADC conversion end trigger*/

    while (1) {
            if (start_recording) {
                ADC12_B_startConversion(ADC12_B_BASE, ADC12_B_START_AT_ADC12MEM5, ADC12_B_REPEATED_SINGLECHANNEL);
                led_toggle();
            } else if (stop_recording) {
                ADC12_B_disableConversions(ADC12_B_BASE, ADC12_B_PREEMPTCONVERSION);
                uart_tx_byte(snd_buffer[0]);
                //disable all interrupts? --> interrupts already disabled in SPI_sendFrame()
                stop_recording = 0;
                led_toggle();
                while(1);
            }
    }
    return 0;
}

#pragma vector=PORT4_VECTOR
__interrupt void PORT4_ISR() {
	if(!start_recording && !stop_recording) { //start recording
		start_recording = 1;
	} else if ((start_recording) && (!stop_recording)) {//stop recording
		start_recording = 0;
		stop_recording = 1;
	}
	button_clearInterrupt();
}
