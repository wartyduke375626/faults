/**
* Upraveny kod utoku na firmver zo sutaze CTF
* original prevzaty 2023-03-18 z: https://blog.securitybits.io/2019/06/voltage-glitching-on-the-cheap/
* Miesto funkcie dgitalWrite() na ovladanie tranzistora pouzivame makra napisane v C Inline Assembly.
*/

#include "asm.h"

// definicia konstant pre pin, ktory ovlada tranzistor
#define GLITCH_PIN 2
#define GLITCH_PORT PORTD
#define GLITCH_BIT 2

// globalne premenne
int incomingByte = 0;
uint8_t glitchDelay = 1;

// funkcia setup sa vola jedenkrat pri spusteni
void setup() {
    // inicializujeme seriovu komunikaciu
    Serial.begin(19200);
    Serial.println("Arduino is ready");
    
    // nastavime pin do vystupneho modu
    pinMode(GLITCH_PIN, OUTPUT);
    
    // nastavime pin na logicku 1 (zapneme tranzistor)
    digitalWrite(GLITCH_PIN, HIGH);
    delay(5000);
    
    Serial.println("Gliching is ready");
}

// funkcia, ktora ovlada tranzistor
void glitch() {
    // ulozime globalnu premennu do registra pre pouzitie v asembleri
    register uint8_t localDelay = globalDelay;

    // vypneme tranzistor
    // _SFR_IO_ADDR staticky vypocita adresu I/O registra pre ovladanie pinu
    setPortOff(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);

    // procedura oneskorenia
    asmDelay(localDelay);

    // zapneme tranzistor
    setPortOn(_SFR_IO_ADDR(GLITCH_PORT), GLITCH_BIT);
    
    // zvacsime pocet iteracii proceduri oneskorenia pre dalsi pokus o utok
    glitchDelay += 1;
    glitchDelay %= 20;
    
    Serial.println();
    Serial.print("Glich Delay set to: ");
    Serial.print(glitchDelay);
    Serial.println();
}

// funkcia loop sa opakuje dookola -- hlavny beh programu
// hlavna cast programu je rovnaka ako v povodnom kode
void loop() {
    // pokusime sa precitat flag
    for (int i = 0; i<200;i++){
        if (Serial.available() > 0) {
            // precitame bajt po bajte
            incomingByte = Serial.read();
            Serial.print(char(incomingByte));
        }
    }
    
    // pockame na stabilizaciu napatia a spustime dalsi utok
    delay(1000);
    glitch();
}