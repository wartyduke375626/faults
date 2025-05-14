/**
* Program used to control the attacks during experiments (Arduino Nano board).
* Also used as demo when attacking example 1 -- Locked Chip.
*/

#include "asm.h"

// define constants for pin which controls the transistor
#define GLITCH_PIN 2
#define GLITCH_PORT PORTD
#define GLITCH_BIT 2

// define constants for pin on which we receive synchronization signal
#define SIGNAL_PIN 3
#define SIGNAL_PORT PIND
#define SIGNAL_BIT 3

// set min and max values of parameters glitchOffset and glitchDelay
// modify according to experiment
#define GLITCH_OFFSET_MIN 1
#define GLITCH_OFFSET_MAX 1
#define GLITCH_DELAY_MIN 6
#define GLITCH_DELAY_MAX 6

// global variables
uint8_t glitchOffset = GLITCH_OFFSET_MIN;
uint8_t glitchDelay = GLITCH_DELAY_MIN;

// function which controls the transistor
void glitch() {
    // store the global variables in a registers for usage in assembly
    register uint8_t localOffset = glitchOffset;
    register uint8_t localDelay = glitchDelay;

    // wait for signal (_SFR_IO_ADDR statically calculates the address of I/O register)
    waitForSignal(_SFR_IO_ADDR(SIGNAL_PORT), SIGNAL_BIT);

    // glitchOffset
    asmDelay(localOffset);

    // turn off transistor
    setPortOff(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);

    // glitchDelay
    asmDelay(localDelay);

    // turn on transistor
    setPortOn(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);
}

// the setup function runs once
void setup() {
    // initialize Serial communication
    Serial.begin(19200);

    // set pins to input/output modes
    pinMode(GLITCH_PIN, OUTPUT);
    pinMode(SIGNAL_PIN, INPUT);

    // set pin to logic 1 (turn on transistor)
    digitalWrite(GLITCH_PIN, HIGH);
    delay(3000);

    Serial.println("Glitching is ready.\n");
}

// the loop function executes in an infinite loop
void loop() {
    Serial.println("Waiting for signal...\n");
    // run the attack
    glitch();

    Serial.println("Glitch executed:");
    Serial.print("\toffset "); Serial.println(glitchOffset);
    Serial.print("\tdelay "); Serial.println(glitchDelay);

    // increment parameters glitchOffset and glitchDelay (if MAX==MIN => values don't change)
    glitchOffset += 1;
    if (glitchOffset > GLITCH_OFFSET_MAX) glitchOffset = GLITCH_OFFSET_MIN;
    glitchDelay += 1;
    if (glitchDelay > GLITCH_DELAY_MAX) glitchDelay = GLITCH_DELAY_MIN;

    // wait for voltage to stabilize before next attempt
    delay(100);
}