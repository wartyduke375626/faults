#include "asm.h"

#define POWER_PIN 2
#define POWER_REG(reg) reg ## D
#define POWER_BIT 2
#define BUFFER_SIZE 100


//uint8_t glitchDelay = 10;


void glitch(uint8_t delay) {
    powerOff(_SFR_IO_ADDR(POWER_REG(PORT)), POWER_BIT);

    delayMicroseconds(delay);
    asmDelay(delay);
    //asmDelay2(delay);
    //__asm__ volatile("nop");

    powerOn(_SFR_IO_ADDR(POWER_REG(PORT)), POWER_BIT);
}


void setup() {
    Serial.begin(19200);
    Serial.setTimeout(100);
    pinMode(POWER_PIN, OUTPUT);
    randomSeed(analogRead(5));

    digitalWrite(POWER_PIN, HIGH);
    delay(3000);

    Serial.println("Glitching is ready.");
}


void loop() {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE * sizeof(char));
    Serial.readBytesUntil('\n', buffer, BUFFER_SIZE);
    Serial.println(buffer);
    
    for (unsigned int i=0; i<5; ++i) {
        uint16_t r = random(1, 100);
        delay(r);
        uint16_t r = random(1, 8);
        Serial.println(r);
        glitch(r);
    }

    //glitchDelay = (glitchDelay + 1u) % 16u;
    Serial.println("Glitch Attempt executed.");
    delay(1000);
}