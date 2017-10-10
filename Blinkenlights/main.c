#include <stdio.h>
#include <msp430.h>
#include "led.h"



/**
 * hello.c
 */
int main(void)
{
    led_init();

    led_on();
    led_toggle();

    //enable global interrupts

	return 0;


}
