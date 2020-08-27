/*########################################################
  ##Library for working with hardware I2C(TWI).(c)DSuhoi##
  ########################################################*/

#ifndef __TWI_H_
#define __TWI_H_

#define F_CPU 8000000UL           // Frequency of the microcontroller

/*#################################Functions#############################################*/
void twi_init(unsigned long);    // Initialization TWI
void twi_start(void);            // Start signal
void twi_stop(void);             // Stop signal
uint8_t twi_write_byte(uint8_t); // Byte transfering
uint8_t twi_read_byte(uint8_t);  // Byte recieving (1-receiving the last byte)

#endif
