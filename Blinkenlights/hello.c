#include <stdio.h>
#include <msp430.h> 


/**
 * hello.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;//PMM_unlockLPM5(), unlocks pin settings
	printf("Hello World!\n"); //this will appear in the debug console
	P3DIR |= 0b00100000; //set port 3 pin 5 to output mode
	P3OUT  = 0b00000000; //set port 3 pin 5 to low, LED is active-low. LED on board should now be on.
	return 0;
}
