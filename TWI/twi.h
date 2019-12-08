/*########################################################
  ##Library for working with hardware I2C(TWI).(c)DSuhoi##
  ########################################################*/

#ifndef __TWI_H_
#define __TWI_H_

#define F_CPU 8000000UL //frequency of the microcontroller

void i2c_init(unsigned long);	 //initialization twi
void i2c_start(void);		 //start signal
void i2c_stop(void);		 //stop signal
uint8_t i2c_write_byte(uint8_t); //byte transfering
uint8_t i2c_read_byte(uint8_t);	 //byte recieving (1-receiving the last byte)

#endif
