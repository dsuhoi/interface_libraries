/*#########################################
  ##Библиотека для работы с SPI.(c)DSuhoi##
  #########################################*/

#ifndef _SPI_H_
#define _SPI_H_

#define F_CPU 8000000UL //частота микроконтроллера

#define MOSI 3
#define MISO 4
#define SCK 5
#define CS 2
#define SPI_PORT PORTB
#define SPI_PIN PINB
#define SPI_DDR DDRB
#define spi_delay _delay_us(2)

void spi_init(void);			//инициализация spi портов
void spi_start(void);			//сигнал старта 
void spi_stop(void);			//сигнал окончания
void spi_write_byte(uint8_t);		//передача байта
uint8_t spi_read_byte(void);		//прием байта

#endif 
