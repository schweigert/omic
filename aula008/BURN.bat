cd bin
cd Release
avrdude -c arduino -b 115200 -P COM4 -p atmega328p -U flash:w:avr-blink.hex:i
PAUSE
