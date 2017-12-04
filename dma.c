/*
 * dma.c
 *
 *  Created on: Dec 2, 2017
 *      Author: Vickram Gidwani
 */

#include "dma.h"

void dma_init() {
	DMA_disableTransfers(DMA_CHANNEL_0);
	DMA_disableInterrupt(DMA_CHANNEL_0);
	DMA_clearInterrupt(DMA_CHANNEL_0);

	//want DMA to be initialized by ADC12B Source 5 interrupt flag
	//want DMA to send 2 bytes from ADC memory to storage buffer
	DMA_initParam param = {0};
	param.channelSelect = DMA_CHANNEL_0;
	param.transferModeSelect = DMA_TRANSFER_REPEATED_SINGLE; //transfer on every trigger of ADC conversion completion
	param.transferSize = 1; //1 word = 2 bytes = 16 bits for each transfer
	param.transferUnitSelect = DMA_SIZE_SRCWORD_DSTWORD; //is this correct?
	param.triggerSourceSelect = DMA_TRIGGERSOURCE_26; //ADC12B conversion end will serve as trigger
	param.triggerTypeSelect = DMA_TRIGGER_RISINGEDGE;

	DMA_init(&param);

	DMA_enableInterrupt(DMA_CHANNEL_0);
}
