#include "asm.h"

#define GLITCH_PIN 2
#define GLITCH_PORT PORTD
#define GLITCH_BIT 2

#define SENSOR_PIN A0


uint8_t glitchDelay = 1;

void glitch() {
    register uint8_t localDelay = glitchDelay;

    setPortOff(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);

    //delay(glitchDelay);
    //delayMicroseconds(glitchDelay);
    asmDelay(localDelay);    
    //asmDelayLong(glitchDelay);
    //nopDelay(10);

    setPortOn(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);
}


void setup() {
    Serial.begin(19200);
    pinMode(GLITCH_PIN, OUTPUT);

    digitalWrite(GLITCH_PIN, HIGH);
    delay(2000);

    Serial.println("Glitching is ready.\n");
}


void loop() {
    int val = analogRead(SENSOR_PIN);
    glitchDelay = val/5 + 1;

    Serial.print("Glitch delay set to: "); Serial.println(glitchDelay);

    glitch();
    delay(100);
}