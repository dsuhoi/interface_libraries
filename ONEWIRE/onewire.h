/*#############################################
  ##Library for working with 1-WIRE.(c)DSuhoi##
  #############################################*/

#ifndef _ONEWIRE_H_
#define _ONEWIRE_H_

/*########################Constants####################################*/
#define F_CPU 8000000UL // Frequency of the microcontroller

#define WIRE_PORT PORTB
#define WIRE_DDR DDRB
#define WIRE_PIN PINB
#define WIRE 0 		// Port 1-wire

/*#################################Functions#############################################*/
uint8_t onewire_init();				// Initialization port
uint8_t onewire_reset();			// Reset signal
void onewire_send_bit(uint8_t bit);	// Bit transfer
uint8_t onewire_read_bit();			// Bit recieve
void onewire_send_byte(uint8_t byte);		// Byte transfering
uint8_t onewire_read_byte();				// Byte recieving
uint8_t onewire_crc(uint8_t crc, uint8_t byte);	// Check CRC
uint8_t onewire_skip_rom();			// Ignore the address
uint8_t onewire_read_rom(uint8_t* rom_addr);	// Reading the address of the device
uint8_t onewire_match_rom(uint8_t* rom_addr);	// Address selection
uint8_t* onewire_search_rom();		// Address search
uint8_t onewire_last_rom();			// Select of the latter device
void search_rom_init();				// Setting up search address 

#endif
