#include <avr/io.h>
#include "twi.h"

///////////////////////////////////////////////////////
void twi_init(unsigned long f_scl){		 //data transmission frequency
	TWBR = (((F_CPU)/(f_scl)-16)/2);			
	TWSR = 0;
}
//////////////////////////////////////////////////////
void twi_start(void){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}
//////////////////////////////////////////////////////
void twi_stop(void){
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	while(TWCR & (1<<TWSTO));
}
//////////////////////////////////////////////////////
uint8_t twi_write_byte(uint8_t byte){
	TWDR = byte;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	return TWSR & 0xF8;
}
//////////////////////////////////////////////////////
uint8_t twi_read_byte(uint8_t final_byte){
	if(!final_byte)
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	else {
	TWCR = (1<<TWINT) | (1<<TWEN);}

	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8)!=0x58) return 0;
	return TWDR;
}


