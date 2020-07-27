#include <avr/io.h>
#include "../TWI/twi.h"
#include "24cxx.h"


// Write byte ("addr" - address)
void EEP_write_byte(uint16_t addr, uint8_t byte)]
{
	// Waiting for a device
	do{
		twi_start();
		twi_write_byte(TW_SR_STOP);
	}while((TWSR & TW_NO_INFO) != TW_MT_SLA_ACK);
	// Sending address
	twi_write_byte(addr>>8);
	twi_write_byte(addr);
	// Sending byte
	twi_write_byte(byte);
	// Stop transfer
	twi_stop();
}

// Read byte from "addr" cell
uint8_t EEP_read_byte(uint16_t addr)
{
	// Waiting for a device
	do{
		twi_start();
		twi_write_byte(TW_SR_STOP);
	}while((TWSR & TW_NO_INFO) != TW_MT_SLA_ACK);
	// Sending address
	twi_write_byte(addr>>8);
	twi_write_byte(addr);
	// Start recieve of bytes
	twi_start();
	twi_write_byte(TW_READ);
	uint8_t byte = twi_read_byte(1);
	// Stop transfer
	twi_stop();
	
	return byte;
}

// Write array byte ("data" - write array,"size" - size write array)
void EEP_write_data(uint16_t addr, uint8_t* data, uint16_t size)
{
	// Waiting for a device
	do{
		twi_start();
		twi_write_byte(TW_SR_STOP);
	}while((TWSR & TW_NO_INFO) != TW_MT_SLA_ACK);
	// Sending address
	twi_write_byte(addr>>8);
	twi_write_byte(addr);
	// Sending bytes
	for(uint16_t i = 0; i < size; i++){
		twi_write_byte(*(data++));
	}
	// Stop transfer
	twi_stop();
}

// Read array from "addr" cell ("data" - read array, "size" - size read array)
uint8_t EEP_read_data(uint16_t addr, uint8_t* data, uint16_t size)
{
	// Waiting for a device
	do{
		twi_start();
		twi_write_byte(TW_SR_STOP);
	}while((TWSR & TW_NO_INFO) != TW_MT_SLA_ACK);
	// Sending address
	twi_write_byte(addr>>8);
	twi_write_byte(addr);
	// Start recieve of bytes
	twi_start();
	twi_write_byte(TW_READ);
	
	if(size<2){ 
		return 0;
	}
	
	for(uint16_t i = 0; i < size - 1;i++){
		*data++ = twi_read_byte(0);
	}
	
	*data = twi_read_byte(1);
	twi_stop();
	return data[size];
}
