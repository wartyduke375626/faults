#include "asm.h"

#define LED_REG(reg) reg ## B
#define LED_BIT 5


void setup() {
    //set port in output mode
    // method 1 (compiler macros):
    LED_REG(DDR) |= (1u << LED_BIT);
    // method 2 (inline assembly):
    //setPortOn(_SFR_IO_ADDR(LED_REG(DDR)), LED_BIT);
}

void loop() {
    uint16_t delay = 0xFFFF;

    // digital write 1
    // method 1 (compiler macros):
    LED_REG(PORT) |= (1u << LED_BIT);
    // method 2 (inline assembly):
    //setPortOn(_SFR_IO_ADDR(LED_REG(PORT)), LED_BIT);
    
    asmDelayLong(delay);
    asmDelayLong(delay);
    asmDelayLong(delay);

    // digital write 0
    // method 1 (compiler macros):
    LED_REG(PORT) &= ~(1u << LED_BIT);
    // method 2 (inline assembly):
    //setPortOff(_SFR_IO_ADDR(LED_REG(PORT)), LED_BIT);

    asmDelayLong(delay);
    asmDelayLong(delay);
    asmDelayLong(delay);
}
