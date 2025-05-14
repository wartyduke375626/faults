# Obsah elektronickej prílohy

Elektronická príloha obsahuje zdrojové kódy programov použitých v práci. Obsah jednotlivých adresárov je nasledovný:

## demoASMBlink/

Obsahuje jednoduchý program, ktorý bliká LED diódou. Program slúži na demonštráciu nastavenia vstupno-výstupných portov na architektúre AVR.

##  vccOnTheCheap/

V tomto adresári sa nachádza kód použitý v sekcii 3.1 – Útok na firmvér zo súťaže CTF.
Obsahuje nasledovné podadresáre:

* **vccOnTheCheap/originalCTF/** – obsahuje pôvodný kód prevzatý z: https://blog.securitybits.io/2019/06/voltage-glitching-on-the-cheap/

* **vccOnTheCheap/upgradedCTF/** – obsahuje vylepšený program tohto útoku (aj s časťami písanými v C Inline Assembly).

* **vccOnTheCheap/fiesta.hex** – skompilovaný HEX obraz strojového kódu firmvéru zo súťaže, na ktorý sme útočili.

* **vccOnTheCheap/Makefile** – poskytuje príkaz pre nahratie "fiesta.hex" na mikrokontrolér ATMega328P pomocou softvéru AVRDUDE. (Je potrebné upraviť parameter /dev/ttyUSB0 – cieľový port, kde je mikrokontrolér pripojený.)

## glitchAnalysis/

Adresár obsahuje pomocný program, ktorý bol použitý na analýzu priebehu napätia pod osciloskopom.

## experiments/

V tomto adresári sa nachádza kód použitý pri testovaní efektov útoku v sekcii 3.3.1 – Experimenty.

* **experiments/experimentsTarget** – obsahuje zdrojový kód programu, na ktorý sme útočili.

* **experiments/experimentsGlitch** – obsahuje zdrojový kód programu, ktorý riadil útok (doska Arduino Nano).

* **experiments/STMglitch.zip** – obsahuje archív exportovaného projektu z prostredia STM32CubeIDE. Archív je možné importovať ako projekt do tohto vývojového prostredia. Podstatný je súbor *STMglitch/Core/Src/main.c*, ktorý obsahuje okomentovaný zdrojový kód programu pre dosku STM32 F4 Discovery. Ostatné súbory archívu boli vygenerované automaticky pomocou STM32CubeIDE.

## CTFexamples/

Obsahuje programy z kapitoly 4 – Príklady úloh do súťaží.

* **CTFexamples/CTF-LED** – obsahuje program z príkladu 1 (sekcia 4.1) – Uzamknutý čip.

* **CTFexamples/CTF-RFID** – obsahuje program z príkladu 2 (sekcia 4.2) – Čítačka RFID kariet.

* **CTFexamples/CTF-LED.hex** a **CTFexamples/CTF-RFID.hex** – skompilované HEX obrazy strojového kódu programov z príkladov 1 a 2.

* **CTFexamples/Makefile** – poskytuje príkaz pre nahratie oboch HEX obrazov na mikrokontrolér ATMega328P pomocou softvéru AVRDUDE. (Je potrebné upraviť parameter /dev/ttyUSB0 – cieľový port, kde je mikrokontrolér pripojený.)