#include <avr/io.h>
#include "spi.h"
#include <util/delay.h>

////////////////////////////////////////////////
void spi_start(void){
	//spi_delay;
	SPI_PORT &=~(_BV(CS) | _BV(SCK));
	spi_delay;
}
/////////////////////////////////////////////////////
void spi_stop(void){
	//spi_delay;
	SPI_PORT |=_BV(CS);
	spi_delay;
}
//////////////////////////////////////////////////////
void spi_init(void){
	SPI_DDR |=_BV(MOSI) | _BV(SCK) | _BV(CS);
	SPI_DDR &=~_BV(MISO);
	SPI_PORT &=~(_BV(MOSI) | _BV(SCK) | _BV(CS));
	SPI_PORT |=_BV(MISO);
}
//////////////////////////////////////////////////////
void spi_write_byte(uint8_t byte){
	for(uint8_t i=0;i<8;i++){
	if(byte & 0x80) SPI_PORT |=_BV(MOSI);
	else SPI_PORT &=~(MOSI);
	spi_delay;
	SPI_PORT |=_BV(SCK);
	spi_delay;
	SPI_PORT &=~_BV(SCK);
	//spi_delay;
	byte <<=1;}
}
/////////////////////////////////////////////////////
uint8_t spi_read_byte(void){
	uint8_t byte = 0;
	for(uint8_t i=0;i<8;i++){
	byte <<=1;
	SPI_PORT |=_BV(SCK);
	spi_delay;
	if(SPI_PIN &_BV(MISO)) byte |=0x01;
	SPI_PORT &=~_BV(SCK);
	spi_delay;}
	return byte;
}

