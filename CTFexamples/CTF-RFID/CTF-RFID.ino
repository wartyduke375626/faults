#include <SPI.h>
#include <PN532_SPI.h>
#include <PN532.h>

#include "asm.h"

#define RED_LED 7
#define GREEN_LED 8
#define WHITE_LED 9
#define SS_PIN 10
#define RFID_TIMEOUT 5000

#define ACCESS_UID_LENGTH 4
#define ACCESS_UID_BYTE_0 0xA3
#define ACCESS_UID_BYTE_1 0xD1
#define ACCESS_UID_BYTE_2 0x8B
#define ACCESS_UID_BYTE_3 0x34


PN532_SPI pn532spi(SPI, SS_PIN);
PN532 nfc(pn532spi);

uint64_t accessCard = 881578403L;

bool checkAccess(uint8_t* uid, uint8_t uidLength) {
    register uint8_t localUidLenght = uidLength;
    register uint8_t uidByte0 = uid[0];
    register uint8_t uidByte1 = uid[1];
    register uint8_t uidByte2 = uid[2];
    register uint8_t uidByte3 = uid[3];
    register uint8_t result;

    __asm__ volatile ( \
        "clr %0"            "\n\t" \
        "eor r0, r0"        "\n\t" \
        "cpi %1, %2"        "\n\t" \
        "breq skip_1"       "\n\t" \
        "inc r0"            "\n\t" \
        "skip_1:"           "\n\t" \
        "cpi %3, %4"        "\n\t" \
        "breq skip_2"       "\n\t" \
        "inc r0"            "\n\t" \
        "skip_2:"           "\n\t" \
        "cpi %5, %6"        "\n\t" \
        "breq skip_3"       "\n\t" \
        "inc r0"            "\n\t" \
        "skip_3:"           "\n\t" \
        "cpi %7, %8"        "\n\t" \
        "breq skip_4"       "\n\t" \
        "inc r0"            "\n\t" \
        "skip_4:"           "\n\t" \
        "cpi %9, %10"       "\n\t" \
        "breq skip_5"       "\n\t" \
        "inc r0"            "\n\t" \
        "skip_5:"           "\n\t" \
        "tst r0"            "\n\t" \
        "brne fail"         "\n\t" \
        "ldi %0, 0x01"      "\n\t" \
        "fail:"             "\n\t" \
        "nop"               "\n\t" \
        : "+d" (result) \
        : "d" (localUidLenght), "M" (ACCESS_UID_LENGTH), \
            "d" (uidByte0), "M" (ACCESS_UID_BYTE_0), \
            "d" (uidByte1), "M" (ACCESS_UID_BYTE_1), \
            "d" (uidByte2), "M" (ACCESS_UID_BYTE_2), \
            "d" (uidByte3), "M" (ACCESS_UID_BYTE_3) \
        : "r0" \
    );
    return result;
}

void flashLED(uint8_t led) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
}

void setup() {
    Serial.begin(19200);

    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(WHITE_LED, OUTPUT);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(WHITE_LED, LOW);

    nfc.begin();
    uint32_t data = nfc.getFirmwareVersion();
    if (!data) {
        Serial.println("Communication with PN532 board failed.");
    }
    nfc.SAMConfig();
    delay(2000);

    Serial.println("Chip booted successfully.");
}

void loop() {
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
    uint8_t uidLength;
    uint8_t success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, RFID_TIMEOUT);

    if (success) {
        Serial.print("\nFound an ISO14443A card with UID value: ");
        for (int8_t i=uidLength-1; i >= 0; --i) Serial.print(uid[i], HEX);
        Serial.println();

        digitalWrite(WHITE_LED, HIGH);
        bool access = checkAccess(uid, uidLength);
        delay(100);
        digitalWrite(WHITE_LED, LOW);
        if (access) {
            Serial.println("Access granted.\n");
            flashLED(GREEN_LED);            
        }
        else {
            Serial.println("Access denied.");
            flashLED(RED_LED); 
        }
    }
    else Serial.println("Waiting for an ISO14443A Card...");
    delay(500);
}