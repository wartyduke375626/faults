/**
* Program used to analyze the voltage waveform under an oscilloscope.
*/

#include "asm.h"

// define constants for pin which controls the transistor
#define GLITCH_PIN 2
#define GLITCH_PORT PORTD
#define GLITCH_BIT 2

// analog input pin, used to dynamically set glitchDelay
#define SENSOR_PIN A0


uint8_t glitchDelay = 1;

// function which controls the transistor
void glitch() {
    // store the global variable in a register for usage in assembly
    register uint8_t localDelay = glitchDelay;

    // turn off transistor (_SFR_IO_ADDR statically calculates the address of I/O register)
    setPortOff(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);

    // delay (uncomment one option)
    //delay(glitchDelay);
    //delayMicroseconds(glitchDelay);
    asmDelay(localDelay);    
    //asmDelayLong(glitchDelay);
    //nopDelay(10);

    // turn on transistor
    setPortOn(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);
}

// the setup function runs once
void setup() {
    // initialize Serial communication
    Serial.begin(19200);

    // set pin to output mode
    pinMode(GLITCH_PIN, OUTPUT);

    // set pin to logic 1 (turn on transistor)
    digitalWrite(GLITCH_PIN, HIGH);
    delay(2000);

    Serial.println("Glitching is ready.\n");
}

// the loop function executes in an infinite loop
void loop() {
    // read analog input and set glitch delay
    int val = analogRead(SENSOR_PIN);
    glitchDelay = val/5 + 1;

    Serial.print("Glitch delay set to: "); Serial.println(glitchDelay);

    glitch();
    delay(100);
}