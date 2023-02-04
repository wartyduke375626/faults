#include "asm.h"
#include "experiments.h"

#define WHITE_LED 12
#define YELLOW_LED 13

#define SIGNAL_PIN 8
#define SIGNAL_REG(reg) reg ## B
#define SIGNAL_BIT 0


void experiment() {
    setPortOn(_SFR_IO_ADDR(SIGNAL_REG(PORT)), SIGNAL_BIT);

    //increment();
    jump();
    //load();
    //delayMicroseconds(1000);
    //delay(5);

    setPortOff(_SFR_IO_ADDR(SIGNAL_REG(PORT)), SIGNAL_BIT);
}

void setup() {
    Serial.begin(19200);
    pinMode(SIGNAL_PIN, OUTPUT);

    digitalWrite(SIGNAL_PIN, LOW);
    delay(3000);

    Serial.println("Experiment is ready.");
}

void loop() {
    Serial.println("Starting experiment.");
    experiment();
    Serial.println("Experiment ended successfully.\n");

    delay(3000);
}
