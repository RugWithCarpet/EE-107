#include <spi.h>
#include "driverlib.h"

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

SDCardLib_Interface sdIntf_MSP430FR5994LP = {
        CLOCK_FREQ,
        SPI_init,
        SPI_fastMode,
        SPI_readFrame,
        SPI_sendFrame,
        SPI_setCSHigh,
        SPI_setCSLow,
        SPI_detectCard,
        SPI_getRTCTime,
        SPI_setRTCTime
};

/***************************************************************************//**
 * @brief   Enable fast SD Card SPI transfers. This function is typically
 *          called after the initial SD Card setup is done to maximize
 *          transfer speed.
 * @param   None
 * @return  None
 ******************************************************************************/
void SPI_fastMode(void)
{
    EUSCI_B_SPI_changeMasterClockParam param = {0};
    param.clockSourceFrequency = CLOCK_FREQ;
    param.desiredSpiClock = DESIRED_SPI_FAST_FREQ;
    EUSCI_B_SPI_changeMasterClock(EUSCI_B0_BASE, &param);
}

/***************************************************************************//**
 * @brief   Read a frame of bytes via SPI
 * @param   pBuffer Place to store the received bytes
 * @param   size Indicator of how many bytes to receive
 * @return  None
 ******************************************************************************/
void SPI_readFrame(uint8_t *pBuffer, uint16_t size)
{
    uint16_t gie = __get_SR_register() & GIE;              // Store current GIE state

    __disable_interrupt();                                 // Make this operation atomic

    // Ensure RXIFG is clear
    EUSCI_B_SPI_clearInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_RECEIVE_INTERRUPT);

    // Clock the actual data transfer and receive the bytes
    while (size--){
        // Wait while not ready for TX
        while(!EUSCI_B_SPI_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_SPI_TRANSMIT_INTERRUPT));
        // Write dummy byte
        EUSCI_B_SPI_transmitData(EUSCI_B0_BASE, 0xff);
        // Wait for RX buffer (full)
        while(!EUSCI_B_SPI_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_SPI_RECEIVE_INTERRUPT));
        *pBuffer++ = EUSCI_B_SPI_receiveData(EUSCI_B0_BASE);
    }

    __bis_SR_register(gie);                                // Restore original GIE state
}


/***************************************************************************//**
 * @brief   Set the SD Card's chip-select signal to high
 * @param   None
 * @return  None
 ******************************************************************************/
void SPI_setCSHigh(void)
{
    GPIO_setOutputHighOnPin(
        GPIO_PORT_P2,
        GPIO_PIN0
        );
}

/***************************************************************************//**
 * @brief   Set the SD Card's chip-select signal to low
 * @param   None
 * @return  None
 ******************************************************************************/
void SPI_setCSLow(void)
{
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P2,
        GPIO_PIN0
        );
}

SDCardLib_Status SPI_detectCard(void)
{
    return SDCARDLIB_STATUS_PRESENT;
}

Calendar SPI_getRTCTime(void)
{
    return RTC_C_getCalendarTime(RTC_C_BASE);
}

void SPI_setRTCTime(Calendar *curTime)
{
    //Initialize Calendar Mode of RTC
    RTC_C_initCalendar(RTC_C_BASE,
            curTime,
            RTC_C_FORMAT_BINARY);

    //Start RTC Clock
    RTC_C_startClock(RTC_C_BASE);
}