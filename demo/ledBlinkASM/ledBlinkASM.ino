#include "asm.h"

#define LED_REG(reg) reg ## B
#define LED_BIT 5


void setup() {
    // set output
    LED_REG(DDR) |= (1u << LED_BIT);
}

void loop() {
    uint16_t delay = 0xFFFF;

    // digital write 1
    LED_REG(PORT) |= (1u << LED_BIT);
    //setPortOn(_SFR_IO_ADDR(LED_REG(PORT)), LED_BIT);
    
    asmDelay0(delay);
    asmDelay0(delay);
    asmDelay0(delay);

    // digital write 0
    LED_REG(PORT) &= ~(1u << LED_BIT);
    //powerOff(_SFR_IO_ADDR(LED_REG(PORT)), LED_BIT);

    asmDelay0(delay);
    asmDelay0(delay);
    asmDelay0(delay);
}
