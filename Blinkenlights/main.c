#include <stdio.h>
#include <msp430.h>
#include "led.h"
#include "timer.h"

/**
 * hello.c
 */

unsigned int volatile numInterrupts = 0;

int main(void)
{
    led_init();
    timerA0_init();
    timerA0_set(50000);
    __enable_interrupt(); //enable global interrupts
    return 0;
}

#pragma vector = TIMER0_A0_VECTOR
    __interrupt void Timer0_A0_ISR (void) {
        numInterrupts++;
        if (numInterrupts == 10) {
            led_toggle();
            numInterrupts = 0;
        }
    }
