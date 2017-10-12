#include <stdio.h>
#include <msp430.h>
#include "led.h"
#include "timer.h"

unsigned int volatile numInterrupts = 0;

int main(void)
{
    led_init();
    timerA0_init();
    timerA0_set(50000); //period is 50,000 because with 10 interrupts, this is 500,000 counts (at 1 MHz, that is 0.5 s)
    __enable_interrupt(); //enable global interrupts
    return 0;
}

#pragma vector = TIMER0_A0_VECTOR
    __interrupt void Timer0_A0_ISR (void) {
        numInterrupts++; //increment counter after every interrupt
        if (numInterrupts == 10) {
            led_toggle();
            numInterrupts = 0; //reset after hitting 10
        }
    }
