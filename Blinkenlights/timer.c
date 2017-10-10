/*
 * timer.c
 *
 *  Created on: Oct 8, 2017
 *      Author: Vickram Gidwani
 */

#include "timer.h"

void timerA0_init() {
    //TA0CTL =  //set clock origin with TASSEL (want crystal)
    //TA0R //counter register
    //TA0CCCTL0 //capture/compare 0 control register, up mode,
};

void timerA0_reset() {
    //TA0R or TA0CTL
};

void timerA0_set(uint16_t period) {
    TA0CCR0 = period;
};
