#include "asm.h"

#define RED_LED 7
#define GREEN_LED 8


uint8_t status = 0;

void checkStatus() {
    register uint8_t localStatus;

    __asm__ volatile ( \ 
        "ldi %0, 0xFF"      "\n\t" \
        "ldi r24, 0x20"     "\n\t" \
        "ldi r25, 0x0F"     "\n\t" \
        "ldi r26, 0xAA"     "\n\t" \
        "mov r3, r26"       "\n\t" \
        "dec %0"            "\n\t" \
        "add %0, r24"       "\n\t" \
        "sub %0, r25"       "\n\t" \
        "or %0, r26"        "\n\t" \
        "add r26, r25"      "\n\t" \
        "add %0, r26"       "\n\t" \
        "clr r26"           "\n\t" \
        "sub r26, r24"      "\n\t" \
        "eor %0, r3"        "\n\t" \
        "inc %0"            "\n\t" \        
        "sub r24, r26"      "\n\t" \
        "add %0, r24"       "\n\t" \
        "and r24, %0"       "\n\t" \
        "or r26, r24"       "\n\t" \
        "add r24, r26"      "\n\t" \
        "and r3, r24"       "\n\t" \
        "eor %0, r3"        "\n\t" \
        "sub %0, r24"       "\n\t" \
        "add r26, r25"      "\n\t" \
        "or r26, r24"       "\n\t" \
        "inc r26"           "\n\t" \
        "sub %0, r26"       "\n\t" \
        "eor r3, r3"        "\n\t" \
        "mov r25, r3"       "\n\t" \
        "ldi r25, 0x2F"     "\n\t" \
        "or %0, r25"        "\n\t" \
        "inc %0"            "\n\t" \
        : "=r" (localStatus) \
        : /* No inputs */ \
        : "r3", "r24", "r25", "r26" \
    );

    status = localStatus;
}

void setup() {
    Serial.begin(19200);
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(2000);

    Serial.println("Chip booted successfully.");
}

void loop() {
    
    while(!status) {
        Serial.println("Chip status: locked");
        digitalWrite(RED_LED, HIGH);
        checkStatus();
        delay(500);
        digitalWrite(RED_LED, LOW);
        delay(500);
    }

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    while(1) {
        Serial.println("Chip status: unlocked");
        delay(1000);
    }
}