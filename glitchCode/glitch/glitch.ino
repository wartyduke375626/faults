#include "asm.h"

#define GLITCH_PIN 2
#define GLITCH_REG(reg) reg ## D
#define GLITCH_BIT 2

#define SIGNAL_PIN 3
#define SIGNAL_REG(reg) reg ## D
#define SIGNAL_BIT 3


void glitch(uint8_t glitchOffset, uint8_t glitchDelay) {
    waitForSignal(_SFR_IO_ADDR(SIGNAL_REG(PIN)), SIGNAL_BIT);

    //delay(glitchOffset);
    //delayMicroseconds(glitchOffset);
    asmDelay(glitchOffset);
    //asmDelayLong(glitchOffset);
    //nopDelay(10);

    setPortOff(_SFR_IO_ADDR(GLITCH_REG(PORT)), GLITCH_BIT);

    //delay(glitchDelay);
    //delayMicroseconds(glitchDelay);
    asmDelay(glitchDelay);
    //asmDelayLong(glitchDelay);
    //nopDelay(10);

    setPortOn(_SFR_IO_ADDR(GLITCH_REG(PORT)), GLITCH_BIT);
}


void setup() {
    Serial.begin(19200);
    pinMode(GLITCH_PIN, OUTPUT);
    pinMode(SIGNAL_PIN, INPUT);

    digitalWrite(GLITCH_PIN, HIGH);
    delay(5000);

    Serial.println("Glitching is ready.");
}


void loop() {
    uint8_t glitchOffset = 1;
    uint8_t glitchDelay = 4;
    Serial.println("Waiting for signal...");
    glitch(glitchOffset, glitchDelay);

    Serial.print("Glitch executed: offset "); Serial.print(glitchOffset);
    Serial.print(", delay "); Serial.print(glitchDelay); Serial.println("\n");

    delay(10);
}