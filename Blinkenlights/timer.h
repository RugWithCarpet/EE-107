/*
 * timer.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Vickram Gidwani
 */

#ifndef TIMER_H_
#define TIMER_H_

void timerA0_init();

void timerA0_reset();

//void timerA0_set(uint16_t period);

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void){}

#endif /* TIMER_H_ */
