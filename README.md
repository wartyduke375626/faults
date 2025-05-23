# Attacking Hardware Using Fault Injection

This repository contains source files related to bachelor's thesis _Attacking hardware using fault injection_.

[Slovak version fo README](README-sk.md)

# Directory structure:

## demoASMBlink/

Contains a simple program that blinks an LED. The program is intended to demonstrate the configuration of input-output ports in Assembly on the AVR architecture.

##  vccOnTheCheap/

This directory contains the code used in Section 3.1. It includes the following subdirectories:

* **vccOnTheCheap/originalCTF/** – original code taken from: https://blog.securitybits.io/2019/06/voltage-glitching-on-the-cheap/

* **vccOnTheCheap/upgradedCTF/** – contains an improved version of the attack (including parts written in C Inline Assembly)

* **vccOnTheCheap/fiesta.hex** – the compiled HEX image of the firmware, which was the target of our attack

* **vccOnTheCheap/Makefile** – provides a command to upload `fiesta.hex` to the ATMega328P microcontroller using the AVRDUDE software (the target device where the microcontroller is connected `/dev/ttyUSB0` needs to be adjusted)

## glitchAnalysis/

The directory contains an auxiliary program that was used to analyze the voltage waveform under an oscilloscope.

## experiments/

This directory contains the code used for testing the effects of the attack during experiments in Section 3.3.1.

* **experiments/experimentsTarget** – the source code of the program that was targeted by the attack

* **experiments/experimentsGlitch** – the source code of the program that controlled the attack (_Arduino Nano_ board)

* **experiments/STMglitch.zip** – an archive of the exported project from _STM32CubeIDE_. The archive can be imported as a project into this IDE. The main file is _STMglitch/Core/Src/main.c_, which contains the source code for the _STM32 F4 Discovery_ board. The other files in the archive were automatically generated by _STM32CubeIDE_.

## CTFexamples/

Contains programs vulnerable to fault injection used as examples in Chapter 4.

* **CTFexamples/CTF-LED** – program from example 1 (Section 4.1) – _Locked Chip_

* **CTFexamples/CTF-RFID** – program from example 2 (Section 4.2) – _RFID Card Reader_

* **CTFexamples/CTF-LED.hex** and **CTFexamples/CTF-RFID.hex** – compiled HEX images of programs from examples 1 and 2

* **CTFexamples/Makefile** – provides a command to upload both HEX images to the ATMega328P microcontroller using the AVRDUDE software (the target device where the microcontroller is connected `/dev/ttyUSB0` needs to be adjusted)
