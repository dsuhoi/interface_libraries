#include <avr/io.h>
#include "twi.h"

// Initialization TWI
void twi_init(unsigned long f_scl)
{   // Data transmission frequency
    TWBR = (((F_CPU)/(f_scl)-16)/2);            
    TWSR = 0;
}

// Start signal
void twi_start(void)
{
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    while(!(TWCR & _BV(TWINT)));
}

// Stop signal
void twi_stop(void)
{
    TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
    while(TWCR & _BV(TWSTO));
}

// Byte transfering
uint8_t twi_write_byte(uint8_t byte)
{
    TWDR = byte;
    TWCR = _BV(TWINT) | _BV(TWEN);
    while(!(TWCR & _BV(TWINT)));
    return TWSR & 0xF8;
}

// Byte recieving (1-receiving the last byte)
uint8_t twi_read_byte(uint8_t final_byte)
{
    if(!final_byte)
        TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
    else
        // If this is the last received byte, then we end the reception
        TWCR = _BV(TWINT) | _BV(TWEN);

    while(!(TWCR & _BV(TWINT)));
    if((TWSR & 0xF8)!=0x58 && (TWSR & 0xF8)!=0x50)
        return 0;
    return TWDR;
}


