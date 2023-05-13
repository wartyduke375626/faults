/**
* Kod pouzity v casti experimenty ako ciel (ATMega328P).
*/

#include "asm.h"

// definicia konstant pre pin, ktorym posielame signal pre synchronizaciu
#define SIGNAL_PIN 8
#define SIGNAL_PORT PORTB
#define SIGNAL_BIT 0

// definicia expreimentu (odkomentovat prave 1 moznost)
#define INCREMENT 1
//#define JUMP 1
//#define LOAD 1

#include "experiments.h"

// funkcia spusti definovany experiment
void experiment() {
    Serial.println(EXPERIMENT_NAME);
    
    // zdefinujeme vystupnu hodnotu experimentu (v registri)
    register uint8_t val;

    // posleme signal
    // _SFR_IO_ADDR staticky vypocita adresu I/O registra pre ovladanie pinu
    setPortOn(_SFR_IO_ADDR(SIGNAL_PORT), SIGNAL_BIT);

    // spustime experiment
    asmExperiment(val);

    // vypneme signal
    setPortOff(_SFR_IO_ADDR(SIGNAL_PORT), SIGNAL_BIT);

    Serial.print("\tresult: "); Serial.println(val);
    Serial.print("\texpected: "); Serial.println(EXPECTED_RESULT);
}

// funkcia setup sa vola jedenkrat pri spusteni
void setup() {
    // inicializujeme seriovu komunikaciu
    Serial.begin(19200);

    // nastavime pin do vystupneho modu
    pinMode(SIGNAL_PIN, OUTPUT);

    // nastavime pin na logicku 0 (vypneme signal)
    digitalWrite(SIGNAL_PIN, LOW);
    delay(5000);

    Serial.println("Experiments are ready.\n");
}

// funkcia loop sa opakuje dookola -- hlavny beh programu
void loop() {
    Serial.println("Starting experiment...");
    experiment();
    Serial.println("Experiment ended successfully.\n");

    // pockame na stabilizaciu napatia pred dalsim utokom
    delay(3000);
}