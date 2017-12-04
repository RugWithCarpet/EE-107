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
	Timer_A_stop(TA0_BASE);
	Timer_A_clear(TA0_BASE);
	Timer_A_clearTimerInterrupt(TA0_BASE);

	//setup TimerA to be 32kHz clock
	Timer_A_initUpModeParam timer_param = {0};
	timer_param.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
	timer_param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
	timer_param.startTimer = 0; //FALSE
	timer_param.timerPeriod = 124; //125 total counts
	timer_param.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
	timer_param.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE; //disable, not necessary
	Timer_A_initUpMode(TA0_BASE, &timer_param);

	//setup CCR1 to have output that goes high every cycle of TimerA
	Timer_A_initCompareModeParam CCR1_param = {0};
	CCR1_param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
	CCR1_param.compareValue = 123; //gets set at 123
	CCR1_param.compareOutputMode = TIMER_A_OUTPUTMODE_SET_RESET; //gets reset when CCR0 hits 124
	CCR1_param.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
	Timer_A_initCompareMode(TA0_BASE, &CCR1_param);

	Timer_A_startCounter(TA0_BASE, TIMER_A_UP_MODE);


	//setup ADC
	ADC12_B_disable(ADC12_B_BASE);

	ADC12_B_initParam adc_param = {0};
	adc_param.clockSourceDivider = ADC12_B_CLOCKDIVIDER_1;
	adc_param.clockSourceSelect = ADC12_B_CLOCKSOURCE_SMCLK;
	adc_param.clockSourcePredivider = ADC12_B_CLOCKPREDIVIDER__1;
	adc_param.internalChannelMap = ADC12_B_NOINTCH;
	adc_param.sampleHoldSignalSourceSelect = ADC12_B_SAMPLEHOLDSOURCE_1; //Output of TA0_CCR1
	ADC12_B_init(ADC12_B_BASE, &adc_param);

	ADC12_B_setupSamplingTimer(
			ADC12_B_BASE,
			ADC12_B_CYCLEHOLD_32_CYCLES, //8 us of 4 MHz clock
			ADC12_B_CYCLEHOLD_32_CYCLES,
			ADC12_B_MULTIPLESAMPLESDISABLE
	);

	ADC12_B_configureMemoryParam mem5_param = {0};
	mem5_param.differentialModeSelect = ADC12_B_DIFFERENTIAL_MODE_DISABLE;
	mem5_param.inputSourceSelect = ADC12_B_INPUT_A5;
	mem5_param.memoryBufferControlIndex = ADC12_B_MEMORY_5;
	mem5_param.endOfSequence = ADC12_B_NOTENDOFSEQUENCE;
	mem5_param.refVoltageSourceSelect = ADC12_B_VREFPOS_AVCC_VREFNEG_VSS;
	mem5_param.windowComparatorSelect = ADC12_B_WINDOW_COMPARATOR_DISABLE;
	ADC12_B_configureMemory(ADC12_B_BASE, &mem5_param);

	ADC12_B_enableInterrupt(ADC12_B_BASE, ADC12_B_IE5, 0, 0); //enable interrupt for analog source 5 for valid signals --> to be used for DMA
	ADC12_B_enable(ADC12_B_BASE); //should this be enabled here or later? --> conversions won't actually start until ADC12_B_startConversion
}
