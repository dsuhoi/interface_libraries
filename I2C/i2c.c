#include <avr/io.h>
#include "i2c.h"
#include <util/delay.h>

// Initialization ports
void i2c_init(void)
{
    I2C_DDR &=~(_BV(SDA) | _BV(SCL));
    I2C_PORT &=~(_BV(SDA) | _BV(SCL));

    i2c_stop();
    i2c_stop();
}

// Stop signal
void i2c_stop(void)
{
    I2C_DDR &=~_BV(SCL);
    i2c_delay;
    I2C_DDR |=_BV(SDA);
    i2c_delay;
    I2C_DDR &=~_BV(SDA);
    i2c_delay;
}

// Start signal
void i2c_start(void)
{
    I2C_DDR &=~(_BV(SDA) | _BV(SCL));
    i2c_delay;
    I2C_DDR |=_BV(SDA);
    i2c_delay;
    I2C_DDR |=_BV(SCL);
    i2c_delay;
}

// Byte transfering
uint8_t i2c_write_byte(uint8_t byte)
{
    uint8_t ask = ACK;
    // Bitwise sending a byte
    for(uint8_t i = 0;i < 8; i++) {
        if(byte & 0x80)
            I2C_DDR &=~_BV(SDA);
        else
            I2C_DDR |=_BV(SDA);
        i2c_delay;
        I2C_DDR &=~_BV(SCL);
        i2c_delay;
        I2C_DDR |=_BV(SCL);
        byte <<=1;
    }

    I2C_DDR &=~_BV(SDA);
    i2c_delay;
    I2C_DDR &=~_BV(SCL);
    i2c_delay;

    if((I2C_PIN & _BV(SDA)) == NACK)
        ask=NACK;
    else
        ask = ACK;

    I2C_DDR |=_BV(SCL);
    I2C_DDR |=_BV(SDA);
    
    return ask;
}

// Byte recieving (1-receiving the last byte)
uint8_t i2c_read_byte(uint8_t final_byte)
{
    I2C_DDR &=~_BV(SDA);
    uint8_t byte = 0;
    // Bitwise reading
    for(uint8_t i = 0;i < 8; i++) {
        byte<<=1;
        I2C_DDR &=~_BV(SCL);
        i2c_delay;
        
        if(I2C_PIN & _BV(SDA))
            byte |= 0x01;
        I2C_DDR |=_BV(SCL);
        i2c_delay;
    }
    // If this is the last received byte, then we end the reception
    if(final_byte == ACK)
        I2C_DDR |=_BV(SDA);
    else
        I2C_DDR &=~_BV(SDA);
    
    i2c_delay;
    I2C_DDR &=~_BV(SCL);
    i2c_delay;
    I2C_DDR |=_BV(SCL);
    
    return byte;
}
