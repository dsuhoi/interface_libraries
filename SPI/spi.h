﻿/*##########################################
  ##Library for working with SPI.(c)DSuhoi##
  ##########################################*/

#ifndef _SPI_H_
#define _SPI_H_

/*########################Constants####################################*/
#define F_CPU 8000000UL //frequency of the microcontroller

#define MOSI 3
#define MISO 4
#define SCK 5
#define CS 2
#define SPI_PORT PORTB
#define SPI_PIN PINB
#define SPI_DDR DDRB
#define spi_delay _delay_us(2)

/*#################################Functions#############################################*/
void spi_init(void);			// Initialization port
void spi_start(void);			// Start signal
void spi_stop(void);			// Stop signal
void spi_write_byte(uint8_t);	// Byte transfering
uint8_t spi_read_byte(void);	// Byte recieving

#endif 
