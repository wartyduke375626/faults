.PHONY: flash dump clean

flash: fiesta.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 115200 -U flash:w:fiesta.hex

dump: fiesta.hex
	avr-objdump -j .sec1 -d -m avr5 fiesta.hex > fiesta.dump

clean:
	rm fiesta.dump
