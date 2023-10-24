#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>

#include "display_macros.h"
#include "display.h"

volatile uint8_t pb_debounced_state = 0xFF;

static void pb_debounce(void)
{
    /** EX: 12.4

    TASK: Implement debouncing for the four pushbuttons.

    NOTE: Do not update the value of "pb_debounced_state" on falling/
    rising edges, rather, only update this variable when an appropriate
    number of samples have been taken.
    */

    /** CODE: Write your code for Ex 12.4 within this function. */

    static uint8_t count0 = 0;
    static uint8_t count1 = 0;

    // Sample pushbutton state
    uint8_t pb_state = PORTA.IN;

    uint8_t pb_changed = pb_state ^ pb_debounced_state; // Detect change in state

    count1 = (count1 ^ count0) & pb_changed; // Increment counters
    count0 = ~count0 & pb_changed; // Reset counters

    pb_debounced_state ^= (count1 & count0); // Update debounced state

}

static void spi_write(void)
{
    static uint8_t current_side = 0;

    if (current_side)
    {
        SPI0.DATA = left_byte;
    }
    else
    {
        SPI0.DATA = right_byte;
    }

    // Toggle the current side
    current_side = !current_side;
}

ISR(TCB1_INT_vect)
{
    pb_debounce();
    spi_write();

    TCB1.INTFLAGS = TCB_CAPT_bm;
}
