/**
* Upgraded code from CTF challenge
* (2023-03-18) original from: https://blog.securitybits.io/2019/06/voltage-glitching-on-the-cheap/
* Instead of the dgitalWrite() function to control the transistor we use macros for C Inline Assembly.
*/

#include "asm.h"

// define constants for pin which controls the transistor
#define GLITCH_PIN 2
#define GLITCH_PORT PORTD
#define GLITCH_BIT 2

// global variables
int incomingByte = 0;
uint8_t glitchDelay = 1;

// the setup function runs once
void setup() {
    // initialize Serial communication
    Serial.begin(19200);
    Serial.println("Arduino is ready");
    
    // set pin to output mode
    pinMode(GLITCH_PIN, OUTPUT);
    
    // set pin to logic 1 (turn on transistor)
    digitalWrite(GLITCH_PIN, HIGH);
    delay(5000);
    
    Serial.println("Gliching is ready");
}

// function which controls the transistor
void glitch() {
    // store the global variable in a register for usage in assembly
    register uint8_t localDelay = glitchDelay;

    // turn off transistor (_SFR_IO_ADDR statically calculates the address of I/O register)
    setPortOff(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);

    // delay procedure
    asmDelay(localDelay);

    // turn on transistor
    setPortOn(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);
    
    // increment delay length for next attempt
    glitchDelay += 1;
    glitchDelay %= 20;
    
    Serial.println();
    Serial.print("Glich Delay set to: ");
    Serial.print(glitchDelay);
    Serial.println();
}

// the loop function executes in an infinite loop
// the main program is the same as in the original version
void loop() {
    // try to read the flag
    for (int i = 0; i<200;i++){
        if (Serial.available() > 0) {
            // read the incoming byte:
            incomingByte = Serial.read();
            Serial.print(char(incomingByte));
        }
    }
    
    // wait for voltage to stabilize before next attempt
    delay(1000);
    glitch();
}