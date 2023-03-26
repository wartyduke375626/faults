#include "asm.h"

#define SIGNAL_PIN 8
#define SIGNAL_PORT PORTB
#define SIGNAL_BIT 0


// uncomment only one definition to set corresponding experiment
#define INCREMENT 1
//#define JUMP 1
//#define LOAD 1

#include "experiments.h"

// executes the defined experiment
void experiment() {
    Serial.println(EXPERIMENT_NAME);
    register uint8_t val;

    setPortOn(_SFR_IO_ADDR(SIGNAL_PORT), SIGNAL_BIT);
    asmExperiment(val);
    setPortOff(_SFR_IO_ADDR(SIGNAL_PORT), SIGNAL_BIT);

    Serial.print("\tresult: "); Serial.println(val);
    Serial.print("\texpected: "); Serial.println(EXPECTED_RESULT);
}

// reads delay value from serial communication (used for glitching with STM board)
void readDelay() {
    Serial.print("\tdelay: ");
    for (uint8_t i=0; i<32; ++i){
        if (Serial.available() > 0) {
            uint8_t incomingByte = Serial.read();
            Serial.print(char(incomingByte));
        }
    }
    Serial.println();
}

void setup() {
    Serial.begin(19200);
    pinMode(SIGNAL_PIN, OUTPUT);

    digitalWrite(SIGNAL_PIN, LOW);
    delay(5000);

    Serial.println("Experiments are ready.\n");
}

void loop() {
    Serial.println("Starting experiment...");
    experiment();
    // uncomment when connected to STM board, which sends corresponding glitchDelay used during attack
    //readDelay();
    Serial.println("Experiment ended successfully.\n");

    // wait for power to stabilize before next attack
    delay(3000);
}