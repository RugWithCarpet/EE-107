/*
 * mom_button.c
 *
 *  Created: 11/2017
 *      Author: Vickram Gidwani
 *
 *      IMPLEMENTS MOMENTARY BUTTON AS INPUT SWITCH WITH INTERRUPT
 */

#include "mom_button.h"

void button_init() {
	GPIO_setAsInputPin( //set port 3 pin 5 to output mode
			GPIO_PORT_P4,
			GPIO_PIN4
	);

	GPIO_setAsInputPinWithPullDownResistor( //need pulldown resistor so pin goes low when button not pressed
			GPIO_PORT_P4,
			GPIO_PIN4
	);

	GPIO_disableInterrupt(
			GPIO_PORT_P4,
			GPIO_PIN4
	);

	GPIO_selectInterruptEdge(
			GPIO_PORT_P4,
			GPIO_PIN4,
			GPIO_LOW_TO_HIGH_TRANSITION //unpressed is low, pressed is high
	);

	GPIO_enableInterrupt(
			GPIO_PORT_P4,
			GPIO_PIN4
	);

	GPIO_clearInterrupt(
			GPIO_PORT_P4,
			GPIO_PIN4
	);

}

void button_clearInterrupt() {
	GPIO_clearInterrupt(
			GPIO_PORT_P4,
			GPIO_PIN4
	);
}
