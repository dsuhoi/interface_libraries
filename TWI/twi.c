#include <avr/io.h>
#include "twi.h"

///////////////////////////////////////////////////////
void i2c_init(unsigned long f_scl){		 //частота передачи данных
	TWBR = (((F_CPU)/(f_scl)-16)/2);			
	TWSR = 0;
}
//////////////////////////////////////////////////////
void i2c_start(void){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & _BV(TWINT)));
}
//////////////////////////////////////////////////////
void i2c_stop(void){
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	while(!(TWCR & _BV(TWSTO)));
}
//////////////////////////////////////////////////////
uint8_t i2c_write_byte(uint8_t byte){
	TWDR = byte;
	TWCR = _BV(TWINT) | _BV(TWEN);
	while(!(TWCR & _BV(TWINT)));
	return TWSR & 0xF8;
}
//////////////////////////////////////////////////////
uint8_t i2c_read_byte(uint8_t final_byte){
	if(!final_byte)
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
	else {
	TWCR = _BV(TWINT) | _BV(TWEN);}

	while(!(TWCR & _BV(TWINT)));
	if((TWSR & 0xF8)!=0x58) return 0;
	return TWDR;
}


