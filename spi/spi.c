#include "spi.h"

#include <avr/io.h>
#include <util/delay.h>

// Start signal
void spi_start()
{
    // Extra delays can be added to improve data transmission reliability
    // spi_delay;
    SPI_PORT &= ~(_BV(CS) | _BV(SCK));
    spi_delay;
}

// Stop signal
void spi_stop()
{
    // spi_delay;
    SPI_PORT |= _BV(CS);
    spi_delay;
}

// Initialization port
void spi_init()
{
    SPI_DDR |= _BV(MOSI) | _BV(SCK) | _BV(CS);
    SPI_DDR &= ~_BV(MISO);
    SPI_PORT &= ~(_BV(MOSI) | _BV(SCK) | _BV(CS));
    SPI_PORT |= _BV(MISO);
}

// Byte transfering
void spi_write_byte(uint8_t byte)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (byte & 0x80)
            SPI_PORT |= _BV(MOSI);
        else
            SPI_PORT &= ~(MOSI);
        spi_delay;
        SPI_PORT |= _BV(SCK);
        spi_delay;
        SPI_PORT &= ~_BV(SCK);
        // spi_delay;
        byte <<= 1;
    }
}

// Byte recieving
uint8_t spi_read_byte()
{
    uint8_t byte = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        byte <<= 1;
        SPI_PORT |= _BV(SCK);
        spi_delay;
        if (SPI_PIN & _BV(MISO)) byte |= 0x01;
        SPI_PORT &= ~_BV(SCK);
        spi_delay;
    }
    return byte;
}
