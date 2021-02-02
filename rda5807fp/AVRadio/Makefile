CC = avr-gcc
INST = avrdude
OBJC = avr-objcopy
SIZE = avr-size

PROG = usbasp
HEAD = LCD/LCD.h ../rda5807fp.h ../../i2c/i2c.h radio/radio.h
OBJ = main.o LCD.o rda5807fp.o i2c.o radio.o
PROJECT = avradio
MCU = atmega8
MCU_P = m8
#fuses
LFUSES = 0xd4
HFUSES = 0xd1
FREQ = 8000000UL

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(FREQ) -Wall -g -Os --param=min-pagesize=0
PFLAGS = -c $(PROG) -p $(MCU_P)


.PHONY: help object hex size flash clean erase

all: object hex size

help:
	@echo 'clean      Delete automatically created files.'
	@echo 'erase      Do erasing to controller.'
	@echo 'flash      Do programming to controller.'
	@echo 'help       Show this text.'
	@echo 'hex        Create hex file.'
	@echo 'object     Create ".o" file.'
	@echo 'size       Show size ".hex" file.'


object: $(OBJ)
	$(CC) $(CFLAGS) -o $(PROJECT).o $(OBJ)

#################################################

main.o: $(HEAD)
	$(CC) $(CFLAGS) -c main.c

LCD.o: $(HEAD)
	$(CC) $(CFLAGS) -c LCD/LCD.c

rda5807fp.o: $(HEAD)
	$(CC) $(CFLAGS) -c ../rda5807fp.c

i2c.o: $(HEAD)
	$(CC) $(CFLAGS) -c ../../i2c/i2c.c

radio.o: $(HEAD)
	$(CC) $(CFLAGS) -c radio/radio.c

################################################

hex: object
	$(OBJC) -j .text -j .data -O ihex $(PROJECT).o $(PROJECT).hex

size:
	$(SIZE) $(PROJECT).hex

flash:
	$(INST) $(PFLAGS) -v -U flash:w:$(PROJECT).hex -U lfuse:w:$(LFUSES):m -U hfuse:w:$(HFUSES):m

clean:
	rm *.o *.hex

erase:
	$(INST) $(PFLAGS) -e
