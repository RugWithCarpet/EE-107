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

void led_on (){     //turn LED on
    P3OUT  = 0b00000000; //set port 3 pin 5 active-low
};

void led_off (){    //turn LED off
    P3OUT  = 0b00100000; //set port 3 pin 5 deactive-high
};

void led_toggle (){     //toggle LED pin
    if (P3OUT == 0b00000000) { //if 'on'
        led_off(); //set port 3 pin 5 deactive-high
    }
    else {
        led_on(); //set port 3 pin 5 active-low
    }
};
