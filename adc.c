/*
 * adc.c
 *
 *  Created on: Nov 29, 2017
 *      Author: Vickram Gidwani
 */


#include "adc.h"

void adc_init() {

	//Setup microphone on pin 1.5 (A5) as analog input
	GPIO_setAsPeripheralModuleFunctionInputPin(
			GPIO_PORT_P1,
			GPIO_PIN5,
			GPIO_TERNARY_MODULE_FUNCTION
	);


	//14 clock cycles for 12 bit conversion
	//2 clock cycles for between sampling and conversion
	//32 clock cycles for sampling/hold
	//minimum of 50 clock cycles per period
	//4 MHz SMCLK
	//32 kHz sampling clock

	Timer_A_initUpModeParam timer_param = {0};
	timer_param.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
	timer_param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
	timer_param.startTimer = FALSE;
	timer_param.timerPeriod = 125;
	timer_param.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;
	timer_param.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;


	//set up TimerA0 Compare/Control Register 1 as 32 kHz clock
	Timer_A_initUpMode(
			TA0_BASE,

	);


	ADC12_B_initParam adc_param = {0};
	adc_param.clockSourceDivider = ADC12_B_CLOCKDIVIDER_1;
	adc_param.clockSourceSelect = ADC12_B_CLOCKSOURCE_SMCLK;
	adc_param.clockSourcePredivider = ADC12_B_CLOCKPREDIVIDER__1;
	adc_param.internalChannelMap = ADC12_B_NOINTCH;
	adc_param.sampleHoldSignalSourceSelect = ADC12_B_SAMPLEHOLDSOURCE_1; //TimerA0 Compare/Control Register 1
	ADC12_B_init(ADC12_B_BASE, &adc_param);

	ADC12_B_setupSamplingTimer(
			ADC12_B_BASE,
			ADC12_B_CYCLEHOLD_32_CYCLES, //8 us of 4 MHz clock
			ADC12_B_CYCLEHOLD_32_CYCLES,
			ADC12_B_MULTIPLESAMPLEDISABLE
	)


}
