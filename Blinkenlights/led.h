/*
 * led.h
 *
 *  Created on: Oct 6, 2017
 *      Author: Vickram Gidwani
 */

#ifndef LED_H_
#define LED_H_

#include <stdio.h>
#include <msp430.h>

void led_init();
void led_on ();
void led_off ();
void led_toggle ();

#endif /* LED_H_ */
