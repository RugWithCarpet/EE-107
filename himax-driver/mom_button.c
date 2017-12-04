/*
 * mom_button.c
 *
 *  Created on: Nov 29, 2017
 *      Author: Vickram Gidwani
 */

#include "mom_button.h"

void button_init() {
	GPIO_setAsInputPin( //set port 3 pin 5 to output mode
			GPIO_PORT_P4,
			GPIO_PIN4
	);

	GPIO_setAsInputPinWithPullDownResistor(
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
