#include "asm.h"

#define GLITCH_PIN 2
#define GLITCH_PORT PORTD
#define GLITCH_BIT 2

#define SIGNAL_PIN 3
#define SIGNAL_PORT PIND
#define SIGNAL_BIT 3

#define BUFFER_SIZE 128


uint8_t glitchOffset = 1;
uint8_t glitchDelay = 6;
char buffer[BUFFER_SIZE];

void glitch() {
    register uint8_t localOffset = glitchOffset;
    register uint8_t localDelay = glitchDelay;

    waitForSignal(_SFR_IO_ADDR(SIGNAL_PORT), SIGNAL_BIT);

    //delayMicroseconds(glitchOffset);
    //asmDelay(localOffset);

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

    memset(buffer, 0, BUFFER_SIZE*sizeof(char));
    Serial.readBytes(buffer, BUFFER_SIZE);

    Serial.println("Glitch executed:");
    Serial.print("\toffset "); Serial.println(glitchOffset);
    Serial.print("\tdelay "); Serial.println(glitchDelay);
    Serial.print(buffer);

    //glitchDelay += 1;
    //if (glitchDelay == 8) glitchDelay = 4;

    //glitchOffset += 1;
    //if (glitchOffset == 11) glitchDelay = 1;

    delay(100);
}