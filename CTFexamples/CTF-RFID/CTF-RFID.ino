/**
* Code from example 1 -- RFID Card Reader (target of the attack).
*/
#include <SPI.h>
#include <PN532_SPI.h>
#include <PN532.h>

#include "asm.h"

// define LED pins
#define RED_LED 7
#define GREEN_LED 8
#define WHITE_LED 9

// define the SS pin for the NFC module (uses the SPI bus)
#define SS_PIN 10
// timeout for reading cards (when timer runs out, attempt to read RFID card returns false)
#define RFID_TIMEOUT 5000

// hardcoded bytes of the 'correct' card UID, which has access granted
#define CORRECT_UID_LENGTH 4
#define CORRECT_UID_BYTE_0 0xA3
#define CORRECT_UID_BYTE_1 0xD1
#define CORRECT_UID_BYTE_2 0x8B
#define CORRECT_UID_BYTE_3 0x34

// NFC module object
PN532_SPI pn532spi(SPI, SS_PIN);
PN532 nfc(pn532spi);

// this function decides whether to grant access -- target function of the attack
bool checkAccess(uint8_t* uid, uint8_t uidLength) {
    // store the UID value into registers to use in Assembly code
    register uint8_t localUidLenght = uidLength;
    register uint8_t uidByte0 = uid[0];
    register uint8_t uidByte1 = uid[1];
    register uint8_t uidByte2 = uid[2];
    register uint8_t uidByte3 = uid[3];
    register uint8_t result;

    // vulnerable part in Assembly code
    asmCheckAccess(result,
        localUidLenght, uidByte0, uidByte1, uidByte2, uidByte3,
        CORRECT_UID_LENGTH, CORRECT_UID_BYTE_0, CORRECT_UID_BYTE_1, CORRECT_UID_BYTE_2, CORRECT_UID_BYTE_3
    );

    return result;
}

// flashes the LED once
void flashLED(uint8_t led) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
}

// the setup function runs once
void setup() {
    // initialize Serial communication
    Serial.begin(19200);

    // set LED pins to output mode
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(WHITE_LED, OUTPUT);

    // turn off LEDs
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(WHITE_LED, LOW);

    // initialize NFC module
    nfc.begin();
    uint32_t data = nfc.getFirmwareVersion();
    if (!data) {
        Serial.println("Communication with PN532 board failed.");
    }
    nfc.SAMConfig();
    delay(2000);

    Serial.println("Chip booted successfully.");
}

// the loop function executes in an infinite loop
void loop() {
    // read the RFID card
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
    uint8_t uidLength;
    uint8_t success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, RFID_TIMEOUT);

    // if a card was successfully read, check access
    if (success) {
        Serial.print("\nFound an ISO14443A card with UID value: ");
        for (int8_t i=uidLength-1; i >= 0; --i) Serial.print(uid[i], HEX);
        Serial.println();

        // turn on white LED to indicate a card has been read (we can use this as a signal to synchronize the attack)
        digitalWrite(WHITE_LED, HIGH);

        // call the target function
        bool access = checkAccess(uid, uidLength);
        delay(100);
        digitalWrite(WHITE_LED, LOW);

        // access verdic
        if (access) {
            Serial.println("Access granted.\n");
            flashLED(GREEN_LED);            
        }
        else {
            Serial.println("Access denied.");
            flashLED(RED_LED); 
        }
    }

    // if nothing was read, delay and wait for a card to be read
    else Serial.println("Waiting for an ISO14443A Card...");
    delay(500);
}