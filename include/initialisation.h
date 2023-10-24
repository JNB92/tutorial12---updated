#ifndef INITIALISATION_H
#define INITIALISATION_H 1

#include <avr/io.h>

/**
 * @brief Enable pull-up resistor for pushbuttons.
 */
static inline void button_init(void)
{
    // Enable pull-up resistors for PBs
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm; // S1
    PORTA.PIN5CTRL = PORT_PULLUPEN_bm; // S2
    PORTA.PIN6CTRL = PORT_PULLUPEN_bm; // S3
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm; // S4
}

/**
 * @brief Configure TCA0 for waveform output generation on PB0.
 */
void pwm_init(void)
{
    /** EX: 12.2

    TASK: Configure TCA0 for waveform output on PB0. The buzzer should
    be silent initially.
    */

   // Configure pins
   PORTB.DIRSET = PIN0_bm;

    // Configure TCA0
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc; 

    // Enable waveform output on PB0
    TCA0.SINGLE.CTRLB |= TCA_SINGLE_CMP0EN_bm;

    // Set period to 7062
    TCA0.SINGLE.PER = 7062;

    // Set duty cycle to 50%
    TCA0.SINGLE.CMP0 = TCA0.SINGLE.PER >> 1;


    // Enable TCA0
    TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV1_gc;

    /** CODE: Write your code for Ex 12.2 within this function. */

}

/**
 * @brief Configure SPI for 7-segment display.
 */
static inline void spi_init(void)
{
    // Configure pins
    // DISP LATCH (PA1)
    PORTA.OUTCLR = PIN1_bm;
    PORTA.DIRSET = PIN1_bm;
    // SPI CLK (PC0), SPI MOSI (PC2)
    PORTC.DIRSET = PIN0_bm | PIN2_bm;

    PORTMUX.SPIROUTEA = PORTMUX_SPI0_ALT1_gc;   // Select alternate pin configuration for SPI
    SPI0.CTRLB = SPI_SSD_bm;                    // Disable client select line
    SPI0.INTCTRL = SPI_IE_bm;                   // Enable interrupt
    SPI0.CTRLA = SPI_MASTER_bm | SPI_ENABLE_bm; // Enable SPI as master
}

/**
 * @brief Configure TCB1 for updating the 7-segment display and
 * pushbutton debouncing.
 */
static inline void timer_init(void)
{
    // Interrupt every 5ms
    TCB1.CCMP = 16667;
    TCB1.INTCTRL = TCB_CAPT_bm;
    TCB1.CTRLA = TCB_ENABLE_bm;
}

#endif
