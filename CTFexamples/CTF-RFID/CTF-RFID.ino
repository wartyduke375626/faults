/**
* Kod programu z prikladu 2 -- Citacka RFID kariet (ciel utoku).
*/
#include <SPI.h>
#include <PN532_SPI.h>
#include <PN532.h>

#include "asm.h"

// definicia pinov LED diod
#define RED_LED 7
#define GREEN_LED 8
#define WHITE_LED 9

// definicia SS pinu pre NFC modul (pouzivame rozhranie SPI)
#define SS_PIN 10
// timeout pre citanie kariet (ked vyprsi, pokus o precitanie karty vrati false)
#define RFID_TIMEOUT 5000

// staticky deklarovane bajty 'spravnej' cipovej karty, ktorej program pristup udeli
#define CORRECT_UID_LENGTH 4
#define CORRECT_UID_BYTE_0 0xA3
#define CORRECT_UID_BYTE_1 0xD1
#define CORRECT_UID_BYTE_2 0x8B
#define CORRECT_UID_BYTE_3 0x34

// objekt, ktorym ovladame NFC modul
PN532_SPI pn532spi(SPI, SS_PIN);
PN532 nfc(pn532spi);

// funkcia, ktora rozhodne, ci prorgam udeli pristup -- cielova funkcia utoku
bool checkAccess(uint8_t* uid, uint8_t uidLength) {
    // ulozime precitane hodnoty UID do registrov pre pouzitie v asembleri
    register uint8_t localUidLenght = uidLength;
    register uint8_t uidByte0 = uid[0];
    register uint8_t uidByte1 = uid[1];
    register uint8_t uidByte2 = uid[2];
    register uint8_t uidByte3 = uid[3];
    register uint8_t result;

    // cast kodu v asembleri -- tu sa deje rozhodnutie o udeleni pristupu
    asmCheckAccess(result,
        localUidLenght, uidByte0, uidByte1, uidByte2, uidByte3,
        CORRECT_UID_LENGTH, CORRECT_UID_BYTE_0, CORRECT_UID_BYTE_1, CORRECT_UID_BYTE_2, CORRECT_UID_BYTE_3
    );

    return result;
}

// funkcia blikne LED diodou
void flashLED(uint8_t led) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
}

// funkcia setup sa vola jedenkrat pri spusteni
void setup() {
    // inicializujeme seriovu komunikaciu
    Serial.begin(19200);

    // nastavime piny LED diod do vystupneho modu
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(WHITE_LED, OUTPUT);

    // vypneme LED diody
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(WHITE_LED, LOW);

    // inicializacia NFC modulu
    nfc.begin();
    uint32_t data = nfc.getFirmwareVersion();
    if (!data) {
        Serial.println("Communication with PN532 board failed.");
    }
    nfc.SAMConfig();
    delay(2000);

    Serial.println("Chip booted successfully.");
}

// funkcia loop sa opakuje dookola -- hlavny beh programu
void loop() {
    // precitame cipovu kartu
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
    uint8_t uidLength;
    uint8_t success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, RFID_TIMEOUT);

    // ak sa podarilo nejaku kartu precitat, overime pristup
    if (success) {
        Serial.print("\nFound an ISO14443A card with UID value: ");
        for (int8_t i=uidLength-1; i >= 0; --i) Serial.print(uid[i], HEX);
        Serial.println();

        // zapneme bielu LED na indikaciu, ze sme nieco precitali (toto vyuzivame ako signal na synchronizaciu)
        digitalWrite(WHITE_LED, HIGH);

        // volanie cielovej funkcie
        bool access = checkAccess(uid, uidLength);
        delay(100);
        digitalWrite(WHITE_LED, LOW);

        // verdikt udelenia pristupu
        if (access) {
            Serial.println("Access granted.\n");
            flashLED(GREEN_LED);            
        }
        else {
            Serial.println("Access denied.");
            flashLED(RED_LED); 
        }
    }

    // ak sme nic neprecitali cakame dalej na prilozenie karty
    else Serial.println("Waiting for an ISO14443A Card...");
    delay(500);
}