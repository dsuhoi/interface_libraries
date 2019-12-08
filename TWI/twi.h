/*########################################################
  ##Library for working with hardware I2C(TWI).(c)DSuhoi##
  ########################################################*/

#ifndef __TWI_H_
#define __TWI_H_

#define F_CPU 8000000UL //frequency of the microcontroller

void twi_init(unsigned long);	 //initialization twi
void twi_start(void);		 //start signal
void twi_stop(void);		 //stop signal
uint8_t twi_write_byte(uint8_t); //byte transfering
uint8_t twi_read_byte(uint8_t);	 //byte recieving (1-receiving the last byte)

#endif
