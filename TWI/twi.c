﻿#include <avr/io.h>
#include "twi.h"

///////////////////////////////////////////////////////
void twi_init(unsigned long f_scl){		 //data transmission frequency
	TWBR = (((F_CPU)/(f_scl)-16)/2);			
	TWSR = 0;
}
//////////////////////////////////////////////////////
void twi_start(void){
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	while(!(TWCR & _BV(TWINT)));
}
//////////////////////////////////////////////////////
void twi_stop(void){
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
	while(TWCR & _BV(TWSTO));
}
//////////////////////////////////////////////////////
uint8_t twi_write_byte(uint8_t byte){
	TWDR = byte;
	TWCR = _BV(TWINT) | _BV(TWEN);
	while(!(TWCR & _BV(TWINT)));
	return TWSR & 0xF8;
}
//////////////////////////////////////////////////////
uint8_t twi_read_byte(uint8_t final_byte){
	if(!final_byte)
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
	else {
	TWCR = _BV(TWINT) | _BV(TWEN);}

	while(!(TWCR & _BV(TWINT)));
	if((TWSR & 0xF8)!=0x58 && (TWSR & 0xF8)!=0x50) return 0;
	return TWDR;
}


