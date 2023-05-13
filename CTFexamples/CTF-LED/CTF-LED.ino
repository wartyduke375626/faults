/**
* Kod programu z prikladu 1 -- Uzamknuty cip (ciel utoku).
*/
#include "asm.h"

// definicia pinov LED diod
#define RED_LED 7
#define GREEN_LED 8

// klucova premenna status
uint8_t status = 0;

// cielova funkcia, ktora pristupuje k premennej status
void checkStatus() {
    // ulozime globalnu premennu status do registra pre pouzitie v asembleri
    register uint8_t localStatus;

    // asemblerova cast kodu
    asmCheckStatus(localStatus);

    // aktualizujeme globalnu premennu status
    status = localStatus;
}

// funkcia setup sa vola jedenkrat pri spusteni
void setup() {
    // inicializujeme seriovu komunikaciu
    Serial.begin(19200);

    // nastavime piny LED diod do vystupneho modu
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    // vypneme LED diody
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(2000);

    Serial.println("Chip booted successfully.");
}

// funkcia loop sa opakuje dookola -- hlavny beh programu
void loop() {
    // 1. while−cyklus
    while(!status) {
        Serial.println("Chip status: locked");

        // zapneme cervenu LED (toto vyuzivame ako signal na synchronizaciu)
        digitalWrite(RED_LED, HIGH);

        // volanie cielovej funkcie
        checkStatus();
        delay(500);

        // vypneme cervenu LED
        digitalWrite(RED_LED, LOW);
        delay(500);
    }

    // vypneme cervenu LED a zapneme zelenu LED
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    // 2. while−cyklus -- cielom je, aby sa sem program dostal
    while(1) {
        Serial.println("Chip status: unlocked");
        delay(1000);
    }
}