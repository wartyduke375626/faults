/**
* Jednoduchy program pre demonstraciu nastavenia I/O registrov na architekture AVR.
*/

#include "asm.h"

// definicia konstant pre pin
#define LED_REG(reg) reg ## B // pouzitie: napr LED_REG(PORT) -> PORTB
#define LED_BIT 5

// funkcia setup sa vola jedenkrat pri spusteni
void setup() {
    // nastavenie portu na vystupny mod
    // metoda 1 -- makra kompilatora:
    LED_REG(DDR) |= (1u << LED_BIT);
    // metoda 2 -- assembler:
    // _SFR_IO_ADDR staticky vypocita adresu I/O registra pre ovladanie pinu
    setPortOn(_SFR_IO_ADDR(LED_REG(DDR)), LED_BIT);
}

// funkcia loop sa opakuje dookola -- hlavny beh programu
void loop() {
    uint16_t delay = 0xFFFF;

    //  nastavenie logickej 1 na danom porte -- zapnutie LED
    // metoda 1 -- makra kompilatora:
    LED_REG(PORT) |= (1u << LED_BIT);
    // metoda 2 -- assembler:
    setPortOn(_SFR_IO_ADDR(LED_REG(PORT)), LED_BIT);
    
    // oneskorenie; dostatocne dlhe, aby bolo zapnutie LED viditelne ludskym okom
    asmDelayLong(delay);
    asmDelayLong(delay);
    asmDelayLong(delay);

    //  nastavenie logickej 0 na danom porte -- vypnutie LED
    // metoda 1 -- makra kompilatora:
    LED_REG(PORT) &= ~(1u << LED_BIT);
    // metoda 2 -- assembler:
    //setPortOff(_SFR_IO_ADDR(LED_REG(PORT)), LED_BIT);

    // oneskorenie; dostatocne dlhe, aby bolo vypnutie LED viditelne ludskym okom
    asmDelayLong(delay);
    asmDelayLong(delay);
    asmDelayLong(delay);
}
