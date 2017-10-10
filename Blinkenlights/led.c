/*
 * led.c
 *
 *  Created on: Oct 6, 2017
 *      Author: Vickram Gidwani
 */

#include "led.h"

void led_init(){
        WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
        PM5CTL0 &= ~LOCKLPM5;//PMM_unlockLPM5(), unlocks pin settings
        P3DIR |= 0b00100000; //set port 3 pin 5 to output mode
        }

void led_on (){
    P3OUT  = 0b00000000;
};

void led_off (){
    P3OUT  = 0b00100000;
};

void led_toggle (){

    if (P3OUT == 0b00000000) {
        printf("P3OUT = 0b00000000");
    }
    else {
        printf("P3OUT = 0b00100000");
    }

    if (P3OUT == 0b00000000) {
        P3OUT = 0b00100000;
    }
    else {
        P3OUT = 0b00000000;
    }
    P3OUT ? 0b00100000 : 0b00000000;

    if (P3OUT == 0b00000000) {
           printf("P3OUT = 0b00000000");
       }
    else {
           printf("P3OUT = 0b00100000");
    }

};
