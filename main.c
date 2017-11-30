#include <stdio.h>
#include <msp430.h>
#include "driverlib.h"
#include "led.h"
#include "timer.h"
#include "adc.h"
#include "mom_button.h"

int main(void)
{
	WDT_A_hold(WDT_A_BASE); // stop watchdog
	PMM_unlockLPM5(); //does this have to be done before or after changing pin settings?
	button_init();
    led_init();
    //adc_init();
    __enable_interrupt(); //enable global interrupts
    return 0;
}

#pragma vector = TIMER0_A0_VECTOR
    __interrupt void Timer0_A0_ISR (void) {
    }

#pragma vector=PORT4_VECTOR
__interrupt void PORT4_ISR (void) {
	led_toggle();
	button_clearInterrupt();
}
