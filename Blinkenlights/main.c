#include <stdio.h>
#include <msp430.h>
#include "led.h"



/**
 * hello.c
 */
int main(void)
{
    led_init();

//    int j = 0;
//    for (j = 0; j < 10; j++) {
//        led_on();
//
//        int i = 0;
//        for (i = 0; i < 10000; i++) { }
//
//        led_toggle();
//    }

    led_on();
    led_toggle();




	return 0;


}
