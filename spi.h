/*******************************************************************************
 *
 *  HAL_SDCard.h
 *
 *  Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#ifndef HAL_SPI_H
#define HAL_SPI_H

#include <stdint.h>
#include "FatFs/sdcard.h"

// Pins from MSP430 connected to the SD Card
#define SPI_SIMO        BIT6
#define SPI_SOMI        BIT7
#define SPI_CLK         BIT2
#define SD_CS           BIT0

// Ports
#define SPI_SEL         P1SEL1
#define SPI_DIR         P1DIR
#define SPI_OUT         P1OUT
#define SPI_REN         P1REN
#define SD_CS_SEL       P2SEL1
#define SD_CS_OUT       P2OUT
#define SD_CS_DIR       P2DIR

#define CLOCK_FREQ             4000000
#define DESIRED_SPI_FREQ       400000
#define DESIRED_SPI_FAST_FREQ  4000000

extern void SPI_init(void);
extern void SPI_fastMode(void);
extern void SPI_readFrame(uint8_t *pBuffer, uint16_t size);
extern void SPI_sendFrame(uint8_t *pBuffer, uint16_t size);
extern void SPI_setCSHigh(void);
extern void SPI_setCSLow(void);
extern SDCardLib_Status SPI_detectCard(void);
extern Calendar SPI_getRTCTime(void);
extern void SPI_setRTCTime(Calendar *curTime);

extern SDCardLib_Interface sdIntf_MSP430FR5994LP;
#endif /* HAL_SPI_H */
