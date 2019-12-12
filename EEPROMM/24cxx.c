#include <avr/io.h>
#include <stdlib.h>
#include "../TWI/twi.h"
#include "24cxx.h"


////////////////////////////////////////////////////////////////
void EEP_write_byte(uint16_t addr, uint8_t byte){
do{
twi_start();
twi_write_byte(0xA0);
}while((TWSR & 0xF8) != 0x18);
twi_write_byte(addr>>8);
twi_write_byte(addr);
twi_write_byte(byte);
twi_stop();
return;
}

///////////////////////////////////////////////////////////
uint8_t EEP_read_byte(uint16_t addr){
do{
twi_start();
twi_write_byte(0xA0);
}while((TWSR & 0xF8) != 0x18);
twi_write_byte(addr>>8);
twi_write_byte(addr);
twi_start();
twi_write_byte(0xA1);
uint8_t byte = twi_read_byte(1);
twi_stop();
return byte;
}

/////////////////////////////////////////////////////////////////////////
void EEP_write_data(uint16_t addr, uint8_t* data, uint16_t size){
do{
twi_start();
twi_write_byte(0xA0);
}while((TWSR & 0xF8) != 0x18);
twi_write_byte(addr>>8);
twi_write_byte(addr);
for(uint16_t i = 0; i<size; i++)
twi_write_byte(*(data++));
twi_stop();
}

//////////////////////////////////////////////////////////////////////
uint8_t EEP_read_data(uint16_t addr, uint8_t* data, uint16_t size){
do{
twi_start();
twi_write_byte(0xA0);
}while((TWSR & 0xF8) != 0x18);
twi_write_byte(addr>>8);
twi_write_byte(addr);
twi_start();
twi_write_byte(0xA1);
if(size<2) return 0;
for(uint16_t i = 0; i<size-1;i++)
*data++ = twi_read_byte(0);
*data = twi_read_byte(1);
twi_stop();
return data[size];
}