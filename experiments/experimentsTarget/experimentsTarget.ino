/**
*Program used as target of attacks during experiments (ATMega328P).
*/

#include "asm.h"

// define constants for pin used to send synchronization signal
#define SIGNAL_PIN 8
#define SIGNAL_PORT PORTB
#define SIGNAL_BIT 0

// set the experiment (uncomment 1 option)
#define INCREMENT 1
//#define JUMP 1
//#define LOAD 1

#include "experiments.h"

// function which starts the defined experiment
void experiment() {
    Serial.println(EXPERIMENT_NAME);
    
    // output value of the experiment
    register uint8_t val;

    // send synchronization signal (_SFR_IO_ADDR statically calculates the address of I/O register)
    setPortOn(_SFR_IO_ADDR(SIGNAL_PORT), SIGNAL_BIT);

    // run experiment
    asmExperiment(val);

    // turn off synchronization signal
    setPortOff(_SFR_IO_ADDR(SIGNAL_PORT), SIGNAL_BIT);

    Serial.print("\tresult: "); Serial.println(val);
    Serial.print("\texpected: "); Serial.println(EXPECTED_RESULT);
}

// the setup function runs once
void setup() {
    // initialize Serial communication
    Serial.begin(19200);

    // set pin to output mode
    pinMode(SIGNAL_PIN, OUTPUT);

    // set pin to logic 0 (turn off synchronization signal)
    digitalWrite(SIGNAL_PIN, LOW);
    delay(5000);

    Serial.println("Experiments are ready.\n");
}

// the loop function executes in an infinite loop
void loop() {
    Serial.println("Starting experiment...");
    experiment();
    Serial.println("Experiment ended successfully.\n");

    // wait for voltage to stabilize before next attempt
    delay(3000);
}