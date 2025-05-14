/**
* Code from example 2 -- Locked Chip (target of the attack).
*/
#include "asm.h"

// define LED pins
#define RED_LED 7
#define GREEN_LED 8

// vulnerable status variable
uint8_t status = 0;

// main function which accesses the status variable
void checkStatus() {
    // force the global variable to a register to use in Assembly
    register uint8_t localStatus;

    // Assembly code
    asmCheckStatus(localStatus);

    // update global variable
    status = localStatus;
}

// the setup function runs once
void setup() {
    // initialize Serial communication
    Serial.begin(19200);

    // set LED pins to output mode
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    // turn off LEDs
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(2000);

    Serial.println("Chip booted successfully.");
}

// the loop function executes in an infinite loop
void loop() {
    // 1st infinite loop
    while(!status) {
        Serial.println("Chip status: locked");

        // turn on the red LED (we can use this as a signal to synchronize the attack)
        digitalWrite(RED_LED, HIGH);

        // call the target function
        checkStatus();
        delay(500);

        // turn off the red LED
        digitalWrite(RED_LED, LOW);
        delay(500);
    }

    // turn off the red LED and turn on the green LED
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    // 2nd infinite loop the target of the attack is to get the program here
    while(1) {
        Serial.println("Chip status: unlocked");
        delay(1000);
    }
}
