/*#########################################
  ##Библиотека для работы с I2C.(c)DSuhoi##
  #########################################*/

#ifndef _I2C_H_
#define _I2C_H_

#define F_CPU 8000000UL //частота микроконтроллера

#define ACK 0	
#define NACK 1

#define SDA 1
#define SCL 0
#define I2C_PORT PORTC
#define I2C_PIN PINC
#define I2C_DDR DDRC
#define i2c_delay _delay_us(5);

void i2c_init(void);	//инициализация портов
void i2c_start(void);	//сигнал старта
void i2c_stop(void);	//сигнал окончания
uint8_t i2c_write_byte(uint8_t); //передача байта
uint8_t i2c_read_byte(uint8_t);	 //прием байта (1-прием последнего байта)

#endif 








