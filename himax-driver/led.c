/*
 * led.c
 *
 *  Created on: Oct 6, 2017
 *      Author: Vickram Gidwani
 */

#include "led.h"

void led_init(){
	GPIO_setAsOutputPin( //set port 3 pin 5 to output mode
			GPIO_PORT_P3,
			GPIO_PIN5
	);
}

void led_on() {     //turn LED on
	GPIO_setOutputLowOnPin( //set port 3 pin 5 active-low
			GPIO_PORT_P3,
			GPIO_PIN5
		);
}

void led_off() {    //turn LED off
	GPIO_setOutputHighOnPin( //set port 3 pin 5 deactive-high
			GPIO_PORT_P3,
			GPIO_PIN5
		);
}

void led_toggle() {     //toggle LED pin
	GPIO_toggleOutputOnPin(
			GPIO_PORT_P3,
			GPIO_PIN5
		);
}
