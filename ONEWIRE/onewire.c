#include <avr/io.h>
#include "onewire.h"
#include <util/delay.h>

// Reset signal
uint8_t onewire_reset(void)
{
	WIRE_DDR |=_BV(WIRE);
	_delay_us(650);
	WIRE_DDR &=~_BV(WIRE);
	_delay_us(3);

	for(uint8_t i = 0; i < 80; i++){
		if(!(WIRE_PIN & _BV(WIRE))){
			while(!(WIRE_PIN & _BV(WIRE)));
			return 0;
		} 
		_delay_us(1);
	}
	return 1;
}

// Initialization port
uint8_t onewire_init(void)
{
	WIRE_DDR &=~_BV(WIRE);
	WIRE_PORT &=~_BV(WIRE);
	return onewire_reset();
}

// Bit transfer
void onewire_send_bit(uint8_t bit)
{
	WIRE_DDR |=_BV(WIRE);
	if(bit){
		_delay_us(8);
		WIRE_DDR &=~_BV(WIRE);
		_delay_us(80);
	}
	else{
		_delay_us(80);
		WIRE_DDR &=~_BV(WIRE);
		_delay_us(8);
	}
}

// Bit recieve
uint8_t onewire_read_bit(void)
{
	WIRE_DDR |=_BV(WIRE);
	_delay_us(3);
	WIRE_DDR &=~_BV(WIRE);
	_delay_us(8);
	uint8_t bit = 0;
	if(WIRE_PIN & _BV(WIRE)){ 
		bit = 0x01;
	}
	_delay_ms(80);
	return bit;
}

// Byte transfering
void onewire_send_byte(uint8_t byte)
{
	for(uint8_t i = 0; i < 8; i++){
		onewire_send_bit(byte & 0x01);
		byte >>=1;
	}
}

// Byte recieving
uint8_t onewire_read_byte(void)
{
	uint8_t byte = 0;
	for(uint8_t i = 0; i < 8; i++){
		byte >>=1;
		if(onewire_read_bit()){ 
			byte |= 0x80;
		}
	}
	return byte;
}

// Check CRC
uint8_t onewire_crc(uint8_t crc, uint8_t byte)
{
	for(uint8_t i = 0; i < 8; i++){
		crc = ((crc ^ byte) & 1) ? (crc >> 1) ^ 0b10001100 : (crc >> 1);
		byte >>=1;
	}
	return crc;
}

// Ignore the address
uint8_t onewire_skip_rom(void)
{
	if(onewire_reset()){ 
		return 1;
	}
	onewire_send_byte(0xCC);
	return 0;
}

// Reading the address of the device
uint8_t onewire_read_rom(uint8_t* rom_addr)
{
	if(onewire_reset()){ 
		return 1;
	}
	onewire_send_byte(0x33);
	for(uint8_t i = 0; i < 8; i++){
		*(rom_addr++) = onewire_read_byte();
	}
	return 0;
}

// Address selection
uint8_t onewire_match_rom(uint8_t* rom_addr)
{
	if(onewire_reset()){ 
		return 1;
	}
	onewire_send_byte(0x55);
	for(uint8_t i = 0; i < 8; i++){
		onewire_send_byte(*(rom_addr++));
	}
	return 0;
}

// Variables for the search
uint8_t onewire_rom_addr[8];
uint8_t onewire_right_bit;
uint8_t search_rom_count = 0;

// Address search
void search_rom_init(void)
{
	for(uint8_t i = 0; i < 8; i++){
		onewire_rom_addr[i] = 0;
	} 
	onewire_right_bit = 65;
}

// Select of the latter device
uint8_t onewire_last_rom(void)
{
	return onewire_match_rom(&onewire_rom_addr[0]);
}

// Setting up search address
uint8_t* onewire_search_rom()
{
	if(!search_rom_count){
		search_rom_init(); 
		search_rom_count = 1;
	}
	if(!onewire_right_bit){
		search_rom_count = 0; 
		return 0;
	}
	if(onewire_reset()){
		search_rom_count = 0; 
		return 0;
	}
	
	uint8_t* prev_addr = &onewire_rom_addr[0];
	uint8_t count = 8;
	uint8_t prev_byte = *prev_addr;
	uint8_t next_byte = 0;
	uint8_t place = 1;
	uint8_t error = 0;
	
	onewire_send_byte(0xF0);
	
	while(1){
		uint8_t bit0 = onewire_read_bit();
		uint8_t bit1 = onewire_read_bit();

		if(!bit0){
			if(!bit1){
				if(place< onewire_right_bit){
					if(prev_byte & 1){
						next_byte |=0x80;
					}
					else{
						error = place;
					}
				}
				else if(place == onewire_right_bit){
					next_byte |=0x80;
				}
				else{
					error = place;
				}
			}
		}
		else{ 
			if(!bit1){
				next_byte |=0x80;
			}
			else{ 
				return 0;
			}
		}

		onewire_send_bit(next_byte & 0x80);
		count--;
		if(!count){
			*prev_addr = next_byte;
			if(place>=64){ 
				break;
			}
			prev_byte = *(++prev_addr);
			count = 8;
		}
		else{
			if(place>=64){ 
				break;
			}
			next_byte >>=1; 
			prev_byte >>=1;
		}
		place++;
	}
	onewire_right_bit = error;
	
	return &onewire_rom_addr[0];
}
