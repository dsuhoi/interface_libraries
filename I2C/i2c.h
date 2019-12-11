/*##########################################
  ##Library for working with I2C.(c)DSuhoi##
  ##########################################*/

#ifndef _I2C_H_
#define _I2C_H_

#define F_CPU 8000000UL //frequency of the microcontroller

#define ACK 0	
#define NACK 1

#define SDA 1
#define SCL 0
#define I2C_PORT PORTC
#define I2C_PIN PINC
#define I2C_DDR DDRC
#define i2c_delay _delay_us(5);

/*#################################Functions#############################################*/
void i2c_init(void);	//initialization port
void i2c_start(void);	//start signal
void i2c_stop(void);	//stop signal
uint8_t i2c_write_byte(uint8_t); //byte transfering
uint8_t i2c_read_byte(uint8_t);	 //byte recieving (1-receiving the last byte)

#endif 








