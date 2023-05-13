.PHONY: flash-LED flash-RFID

flash-LED: CTF-LED.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 115200 -U flash:w:CTF-LED.hex

flash-RFID: CTF-RFID.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 115200 -U flash:w:CTF-RFID.hex
