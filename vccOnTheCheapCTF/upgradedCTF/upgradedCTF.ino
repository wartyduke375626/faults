/*
Original code from: https://blog.securitybits.io/2019/06/voltage-glitching-on-the-cheap/
Code was modified for our purposes
*/

#include "asm.h"

#define GLITCH_PIN 2
#define GLITCH_PORT PORTD
#define GLITCH_BIT 2

int incomingByte = 0;

uint8_t glitchDelay = 1;


void setup() {
    Serial.begin(19200);
    Serial.println("Arduino is ready");
    
    pinMode(GLITCH_PIN, OUTPUT);
    
    digitalWrite(GLITCH_PIN, HIGH);
    delay(5000);
    
    Serial.println("Gliching is ready");
}

void glitch() {
    register uint8_t localDelay = globalDelay;
    setPortOff(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);
    asmDelay(localDelay);
    setPortOn(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);
    
    glitchDelay += 1;
    glitchDelay %= 20;
    
    Serial.println();
    Serial.print("Glich Delay set to: ");
    Serial.print(glitchDelay);
    Serial.println();
}

void loop() {
    for (int i = 0; i<200;i++){
        if (Serial.available() > 0) {
            // read the incoming byte:
            incomingByte = Serial.read();
            Serial.print(char(incomingByte));
        }
    }
    
    delay(1000);
    glitch();
}