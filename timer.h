/*
 * timer.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Vickram Gidwani
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdio.h>
#include <msp430.h>
#include <stdint.h>

void timerA0_init();

void timerA0_reset();

void timerA0_set(uint16_t period);

#endif /* TIMER_H_ */
