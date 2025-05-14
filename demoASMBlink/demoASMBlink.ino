/**
* Simple program for demonstrating manupulation of I/O registers on AVR architecture.
*/

#include "asm.h"

// define constants for PORT B (LED port)
#define LED_REG(reg) reg ## B // usage: e.g. LED_REG(PORT) -> PORTB
#define LED_BIT 5

// the setup function runs once
void setup() {
    // set port to output mode
    // method 1 -- compiler macros:
    LED_REG(DDR) |= (1u << LED_BIT);
    // method 2 -- assembly (_SFR_IO_ADDR statically calculates the address of I/O register):
    //setPortOn(_SFR_IO_ADDR(LED_REG(DDR)), LED_BIT);
}

// the loop function executes in an infinite loop
void loop() {
    uint16_t delay = 0xFFFF;

    // set logic 1 on the specific port (turn on LED)
    // method 1 -- compiler macros:
    LED_REG(PORT) |= (1u << LED_BIT);
    // method 2 -- assembly:
    //setPortOn(_SFR_IO_ADDR(LED_REG(PORT)), LED_BIT);
    
    // delay for enough time for the blink to be visible
    asmDelayLong(delay);
    asmDelayLong(delay);
    asmDelayLong(delay);

    // set logic 0 on the specific port (turn off LED)
    // method 1 -- compiler macros:
    LED_REG(PORT) &= ~(1u << LED_BIT);
    // method 2 -- assembly:
    //setPortOff(_SFR_IO_ADDR(LED_REG(PORT)), LED_BIT);

    // delay for enough time for the blink to be visible
    asmDelayLong(delay);
    asmDelayLong(delay);
    asmDelayLong(delay);
}
