/*
 * mom_button.h
 *
 *  Created on: Nov 29, 2017
 *      Author: Vickram Gidwani
 */

#ifndef MOM_BUTTON_H_
#define MOM_BUTTON_H_

#include <stdio.h>
#include <stdint.h>
#include <msp430.h>
#include "driverlib.h"

void button_init();
void button_clearInterrupt();

#endif /* MOM_BUTTON_H_ */
