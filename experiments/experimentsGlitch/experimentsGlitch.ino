/**
* Kod pouzity na riadenie utokov v casti experimenty (doska Arduino Nano).
* Zaroven bol pouzity pri utoku na priklad 1 -- Uzamknuty cip.
*/

#include "asm.h"

// definicia konstant pre pin, ktory ovlada tranzistor
#define GLITCH_PIN 2
#define GLITCH_PORT PORTD
#define GLITCH_BIT 2

// definicia konstant pre pin, na ktorom prijimame signal pre sinchronizaciu
#define SIGNAL_PIN 3
#define SIGNAL_PORT PIND
#define SIGNAL_BIT 3

// nastavenie maximalnej a minimalnej hodnoty parametrov posun (glitchOffset) a vypadok (glitchDelay)
// mozno upravit podla potreby
#define GLITCH_OFFSET_MIN 1
#define GLITCH_OFFSET_MAX 1
#define GLITCH_DELAY_MIN 6
#define GLITCH_DELAY_MAX 6

// globalne premenne
uint8_t glitchOffset = GLITCH_OFFSET_MIN;
uint8_t glitchDelay = GLITCH_DELAY_MIN;

// funkcia, ktora ovlada tranzistor
void glitch() {
    // ulozime globalne premenne do registrov pre pouzitie v asembleri
    register uint8_t localOffset = glitchOffset;
    register uint8_t localDelay = glitchDelay;

    // pockame na signal
    // _SFR_IO_ADDR staticky vypocita adresu I/O registra pre ovladanie pinu
    waitForSignal(_SFR_IO_ADDR(SIGNAL_PORT), SIGNAL_BIT);

    // posun
    asmDelay(localOffset);

    // vypneme tranzistor
    setPortOff(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);

    // vypadok
    asmDelay(localDelay);

    // zapneme tranzistor
    setPortOn(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);
}

// funkcia setup sa vola jedenkrat pri spusteni
void setup() {
    // inicializujeme seriovu komunikaciu
    Serial.begin(19200);

    // nastavime pin do vystupneho resp. vstupneho modu
    pinMode(GLITCH_PIN, OUTPUT);
    pinMode(SIGNAL_PIN, INPUT);

    // nastavime pin na logicku 1 (zapneme tranzistor)
    digitalWrite(GLITCH_PIN, HIGH);
    delay(3000);

    Serial.println("Glitching is ready.\n");
}

// funkcia loop sa opakuje dookola -- hlavny beh programu
void loop() {
    Serial.println("Waiting for signal...\n");
    // spustime utok
    glitch();

    Serial.println("Glitch executed:");
    Serial.print("\toffset "); Serial.println(glitchOffset);
    Serial.print("\tdelay "); Serial.println(glitchDelay);

    // zvacsime parametre posun a vypadok (ak MAX==MIN => hodnota daneho parametra sa nezmeni)
    glitchOffset += 1;
    if (glitchOffset > GLITCH_OFFSET_MAX) glitchOffset = GLITCH_OFFSET_MIN;
    glitchDelay += 1;
    if (glitchDelay > GLITCH_DELAY_MAX) glitchDelay = GLITCH_DELAY_MIN;

    // pockame na stabilizaciu napatia pred dalsim utokom
    delay(100);
}