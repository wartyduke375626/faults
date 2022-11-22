#include "asm.h"

#define GLITCH_PIN 2
#define GLITCH_REG(reg) reg ## D
#define GLITCH_BIT 2

#define SIGNAL_PIN 3
#define SIGNAL_REG(reg) reg ## D
#define SIGNAL_BIT 3



void glitch(uint8_t glitchDelay) {
    waitForSignal(_SFR_IO_ADDR(SIGNAL_REG(PIN)), SIGNAL_BIT);
    powerOff(_SFR_IO_ADDR(GLITCH_REG(PORT)), GLITCH_BIT);

    //delay(glitchDelay);
    //delayMicroseconds(glitchDelay);
    //asmDelay(glitchDelay);
    asmDelay2(glitchDelay);
    //__asm__ volatile("nop");

    powerOn(_SFR_IO_ADDR(GLITCH_REG(PORT)), GLITCH_BIT);
}


void setup() {
    Serial.begin(19200);
    Serial.setTimeout(100);
    pinMode(GLITCH_PIN, OUTPUT);
    pinMode(SIGNAL_PIN, INPUT);
    randomSeed(analogRead(5));

    digitalWrite(GLITCH_PIN, HIGH);
    delay(3000);

    Serial.println("Glitching is ready.");
}


void loop() {
    uint8_t glitchDelay = 6; //random(1, 5);
    Serial.println("Wating for signal...");
    glitch(glitchDelay);
    Serial.println("Glitch executed.\n");

    delay(1000);
}