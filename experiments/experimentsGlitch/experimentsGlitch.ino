#include "asm.h"

#define GLITCH_PIN 2
#define GLITCH_PORT PORTD
#define GLITCH_BIT 2

#define SIGNAL_PIN 3
#define SIGNAL_PORT PIND
#define SIGNAL_BIT 3


uint8_t glitchOffset = 1;
uint8_t glitchDelay = 6;

// Waits for signal, then delays by glitchOffset and executes a glitch of length glitchDelay
void glitch() {
    // Force values to registers for faster asm_delay procedure execution
    register uint8_t localOffset = glitchOffset;
    register uint8_t localDelay = glitchDelay;

    waitForSignal(_SFR_IO_ADDR(SIGNAL_PORT), SIGNAL_BIT);

    //delayMicroseconds(glitchOffset);
    asmDelay(localOffset);

    setPortOff(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);

    //delayMicroseconds(glitchDelay);
    asmDelay(localDelay);

    setPortOn(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);
}

void setup() {
    Serial.begin(19200);
    pinMode(GLITCH_PIN, OUTPUT);
    pinMode(SIGNAL_PIN, INPUT);

    digitalWrite(GLITCH_PIN, HIGH);
    delay(3000);

    Serial.println("Glitching is ready.\n");
}

void loop() {
    Serial.println("Waiting for signal...\n");
    glitch();

    Serial.println("Glitch executed:");
    Serial.print("\toffset "); Serial.println(glitchOffset);
    Serial.print("\tdelay "); Serial.println(glitchDelay);

    // uncomment for automatic glitchDelay and/or glitchOffset increment
    //glitchDelay += 1;
    //if (glitchDelay == 8) glitchDelay = 4;
    //glitchOffset += 1;
    //if (glitchOffset == 11) glitchOffset = 1;

    // wait for power to stabilize before next glitch
    delay(100);
}