/*#############################################
  ##Library for working with 1-WIRE.(c)DSuhoi##
  #############################################*/

#ifndef _ONEWIRE_H_
#define _ONEWIRE_H_

#define F_CPU 8000000UL //frequency of the microcontroller

#define WIRE_PORT PORTB
#define WIRE_DDR DDRB
#define WIRE_PIN PINB
#define WIRE 0 		//port 1-wire

uint8_t onewire_init();				//initialization port
uint8_t onewire_reset();			//reset signal
void onewire_send_bit(uint8_t bit);		//bit transfer
uint8_t onewire_read_bit();			//bit recieve
void onewire_send_byte(uint8_t byte);		//byte transfering
uint8_t onewire_read_byte();			//byte recieving
uint8_t onewire_crc(uint8_t crc, uint8_t byte);	//check CRC
uint8_t onewire_skip_rom();			//ignore the address
uint8_t onewire_read_rom(uint8_t * rom_addr);	//reading the address of the device
uint8_t onewire_match_rom(uint8_t * rom_addr);	//address selection
uint8_t* onewire_search_rom();			//address search
uint8_t onewire_last_rom();			//select of the latter device
void search_rom_init();				//setting up search address 

#endif
