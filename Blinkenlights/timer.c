/*
 * timer.c
 *
 *  Created on: Oct 8, 2017
 *      Author: Vickram Gidwani
 */

#include "timer.h"

void timerA0_init() {
    TA0CTL = TACLR;
    TA0CTL = MC_0;
    TA0CTL = TASSEL_2 + MC_1; //SMCLK (1 MHz), Up Mode (To TA0CCR0), clear timer
    TA0CCTL0 = CCIE; //enable interrupts

    //set timer divider
};

void timerA0_reset() {
    TA0R = 0;
};

void timerA0_set(uint16_t period) {
    TA0CCR0 = period;
};
