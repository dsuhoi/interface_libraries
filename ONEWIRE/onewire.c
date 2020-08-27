#include <avr/io.h>
#include "onewire.h"
#include <util/delay.h>

// Reset signal
uint8_t onewire_reset(void)
{
    WIRE_DDR |=_BV(WIRE);
    _delay_us(650);     // Pause 480..960 microseconds
    WIRE_DDR &=~_BV(WIRE);
    // The time required for the pull-up resistor to return a high level on the bus
    _delay_us(3);
    // Wait at least 60 microseconds before the presence pulse appears
    for(uint8_t i = 0; i < 80; i++){
        // If a presence pulse is detected, we wait for it to end
        if(!(WIRE_PIN & _BV(WIRE))){
            // Waiting for the end of the presence signal
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
    if(bit) {
        // Low pulse, from 1 to 15 microseconds (taking into account the recovery time of the level)
        _delay_us(8);   
        WIRE_DDR &=~_BV(WIRE);
        // Waiting until the end of the time slot (at least 60 microseconds)
        _delay_us(80);
    } else {
        // Low level for the entire time slot (no less than 60 microseconds, no more than 120 microseconds)
        _delay_us(80);
        WIRE_DDR &=~_BV(WIRE);
        // High level recovery time on the bus
        _delay_us(8);
    }
}

// Bit recieve
uint8_t onewire_read_bit(void)
{
    WIRE_DDR |=_BV(WIRE);
    // Low level duration (minimum 1 microseconds)
    _delay_us(3);
    WIRE_DDR &=~_BV(WIRE);
    // Pause until sampling, no more than microseconds in total
    _delay_us(8);
    uint8_t bit = 0;
    if(WIRE_PIN & _BV(WIRE))
        bit = 0x01;
    // Waiting until the next time slot, at least 60 microseconds from the beginning of the low level
    _delay_ms(80);
    return bit;
}

// Byte transfering
void onewire_send_byte(uint8_t byte)
{
    for(uint8_t i = 0; i < 8; i++) {
        onewire_send_bit(byte & 0x01);
        byte >>= 1;
    }
}

// Byte recieving
uint8_t onewire_read_byte(void)
{
    uint8_t byte = 0;
    for(uint8_t i = 0; i < 8; i++) {
        byte >>=1;
        if(onewire_read_bit())
            byte |= 0x80;
    }
    return byte;
}

// Check CRC
uint8_t onewire_crc(uint8_t crc, uint8_t byte)
{
    for(uint8_t i = 0; i < 8; i++) {
        crc = ((crc ^ byte) & 1) ? (crc >> 1) ^ 0b10001100 : (crc >> 1);
        byte >>=1;
    }
    // Returns the updated checksum value
    return crc;
}

// Ignore the address
uint8_t onewire_skip_rom(void)
{
    // Performs an initialization sequence (reset + waits for a presence pulse)
    if(onewire_reset())
        return 1;
    // If a presence pulse is received, executes the SKIP ROM command
    onewire_send_byte(0xCC);
    return 0;
}

// Reading the address of the device
uint8_t onewire_read_rom(uint8_t* rom_addr)
{
    // Performs an initialization sequence (reset + waits for a presence pulse)
    if(onewire_reset())
        return 1;
    // If a presence pulse is received, executes the READ ROM command, then reads the 8-byte device code
    onewire_send_byte(0x33);
    for(uint8_t i = 0; i < 8; i++)
        *(rom_addr++) = onewire_read_byte();
    return 0;
}

// Address selection
uint8_t onewire_match_rom(uint8_t* rom_addr)
{
    // Performs an initialization sequence (reset + waits for a presence pulse)
    if(onewire_reset())
        return 1;
    // If a presence pulse is received, executes the MATCH ROM command 
    onewire_send_byte(0x55);
    // and sends an 8-byte code  by the data pointer (the smallest byte forward)
    for(uint8_t i = 0; i < 8; i++)
        onewire_send_byte(*(rom_addr++));
    return 0;
}

// Variables for the search
uint8_t onewire_rom_addr[8];    // Eight-byte address
uint8_t onewire_right_bit;      // The last zero bit where there was ambiguity (numbering from one)
uint8_t search_rom_init_count = 0;  // Variable initialization status counter search_rom_init()

// Address search
void search_rom_init(void)
{
    for(uint8_t i = 0; i < 8; i++)
        onewire_rom_addr[i] = 0;
    onewire_right_bit = 65;     // Maximum value
    search_rom_init_count = 1;  // Initialization was successful
}

// Select of the latter device
uint8_t onewire_last_rom(void)
{
    return onewire_match_rom(&onewire_rom_addr[0]);
}

// Setting up search address
// Returns a pointer to a buffer containing an eight-byte address value, or NULL if the search is complete
uint8_t* onewire_search_rom()
{
    if(!search_rom_init_count)
        search_rom_init();
    if(!(onewire_right_bit && onewire_reset())) {    // If there were no disagreements in the previous step
        search_rom_init_count = 0; 
        return 0;
    }
    
    uint8_t* prev_addr = &onewire_rom_addr[0];
    uint8_t count = 8;
    uint8_t prev_byte = *prev_addr;
    uint8_t next_byte = 0;
    uint8_t place = 1;
    uint8_t error = 0;
    
    onewire_send_byte(0xF0);
    
    while(1) {
        uint8_t bit0 = onewire_read_bit();
        uint8_t bit1 = onewire_read_bit();

        if(!bit0) {      // If bit zero is present in addresses
            if(!bit1) {  // But there is also bit 1 (fork)
                // If we are to the left of the previous right conflict bit,
                if(place < onewire_right_bit) {  
                    if(prev_byte & 1)
                        // then copy the bit value from the previous pass
                        next_byte |=0x80;
                    else
                        // If zero, then remember the conflict location
                        error = place;
                } else if(place == onewire_right_bit) {
                    // If there was a right conflict with zero at this point last time, output 1
                    next_byte |=0x80;
                } else {
                    // If more to the right, pass zero and remember the location of the conflict
                    error = place;
                }
            }
        } else {
            // Otherwise, go by selecting zero in the address
            if(!bit1)  // Present unit
                next_byte |=0x80;
            else
                // There are no zeros or ones - an erroneous situation
                return 0;
        }

        onewire_send_bit(next_byte & 0x80);
        count--;
        if(!count) {
            *prev_addr = next_byte;
            if(place >= 64)
                break;
            prev_byte = *(++prev_addr);
            count = 8;
        } else {
            if(place>=64)
                break;
            next_byte >>=1; 
            prev_byte >>=1;
        }
        place++;
    }

    onewire_right_bit = error;
    return &onewire_rom_addr[0];
}
