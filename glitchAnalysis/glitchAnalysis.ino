/**
* Kod pouzity na analyzu priebehu napatia na cieli pod osciloskopom.
*/

#include "asm.h"

// definicia konstant pre pin, ktory ovlada tranzistor
#define GLITCH_PIN 2
#define GLITCH_PORT PORTD
#define GLITCH_BIT 2

// pin na, ktorom prijimame analogovy vstup pre nastavenie glitchDelay
#define SENSOR_PIN A0


uint8_t glitchDelay = 1;

// funkcia, ktora ovlada tranzistor
void glitch() {
    // ulozime globalnu premennu do registra pre pouzitie v asembleri
    register uint8_t localDelay = glitchDelay;

    // vypneme tranzistor
    // _SFR_IO_ADDR staticky vypocita adresu I/O registra pre ovladanie pinu
    setPortOff(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);

    // oneskorenie (odkomentovat jednu moznost)
    //delay(glitchDelay);
    //delayMicroseconds(glitchDelay);
    asmDelay(localDelay);    
    //asmDelayLong(glitchDelay);
    //nopDelay(10);

    // zapneme tranzistor
    setPortOn(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);
}

// funkcia setup sa vola jedenkrat pri spusteni
void setup() {
    // inicializujeme seriovu komunikaciu
    Serial.begin(19200);

    // nastavime pin do vystupneho modu
    pinMode(GLITCH_PIN, OUTPUT);

    // nastavime pin na logicku 1 (zapneme tranzistor)
    digitalWrite(GLITCH_PIN, HIGH);
    delay(2000);

    Serial.println("Glitching is ready.\n");
}

// funkcia loop sa opakuje dookola -- hlavny beh programu
void loop() {
    // precitame analogovy vstup a nastavime glitchdelay
    int val = analogRead(SENSOR_PIN);
    glitchDelay = val/5 + 1;

    Serial.print("Glitch delay set to: "); Serial.println(glitchDelay);

    // spustime utok
    glitch();
    delay(100);
}