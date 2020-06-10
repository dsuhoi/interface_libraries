CC = avr-gcc
INST = avrdude
OBJC = avr-objcopy
SIZE = avr-size

#программатор
PROG = usbasp
#заголовочные файлы
HEAD = LCD/LCD.h ../RDA5807FP.h ../../I2C/i2c.h Radio/RADIO.h
#объектные файлы
OBJ = main.o LCD.o RDA5807FP.o i2c.o RADIO.o
#название проекта
COMP = avradio
#Название микроконтроллера
MCU = atmega8
#AvrDude МК
MCU_P = m8
#fuses
LFUSES = 0xd4
HFUSES = 0xd1
#рабочая частота МК
FREQ = 8000000UL

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(FREQ) -Wall -Werror -Wextra -g -Os 
PFLAGS = -c $(PROG) -p $(MCU_P)


.PHONY: help object hex size flash clean erase

all: object hex size

help:
	@echo 'clean      Delete automatically created files.'
	@echo 'erase      Do erasing to controller.'
	@echo 'flash      Do programming to controller.'
	@echo 'help       Show this text.'
	@echo 'hex        Create hex file.'
	@echo 'object	   Create ".o" file.'
	@echo 'size       Show size ".hex" file.'


object: main lcd rda i2c radio
	$(CC) $(CFLAGS) -o $(COMP).o $(OBJ)

#################################################

main: $(HEAD)
	$(CC) $(CFLAGS) -c main.c

lcd: $(HEAD)
	$(CC) $(CFLAGS) -c LCD/LCD.c

rda: $(HEAD)
	$(CC) $(CFLAGS) -c ../RDA5807FP.c

i2c: $(HEAD)
	$(CC) $(CFLAGS) -c ../../I2C/i2c.c
	
radio: $(HEAD)
	$(CC) $(CFLAGS) -c Radio/RADIO.c

################################################

hex: object
	$(OBJC) -j .text -j .data -O ihex $(COMP).o $(COMP).hex

size:
	$(SIZE) $(COMP).hex

flash:
	$(INST) $(PFLAGS) -v -U flash:w:$(COMP).hex -U lfuse:w:$(LFUSES):m -U hfuse:w:$(HFUSES):m

clean:
	rm *.o *.hex

erase:
	$(INST) $(PFLAGS) -e
