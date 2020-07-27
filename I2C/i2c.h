/*##########################################
  ##Library for working with I2C.(c)DSuhoi##
  ##########################################*/

#ifndef _I2C_H_
#define _I2C_H_

/*########################Constants####################################*/
#define F_CPU 8000000UL // Frequency of the microcontroller

#define ACK 0	
#define NACK 1
// I2C interface ports
#define SDA 4
#define SCL 5
#define I2C_PORT PORTC
#define I2C_PIN PINC
#define I2C_DDR DDRC
// Delay
#define i2c_delay _delay_us(5);

/*#################################Functions#############################################*/
void i2c_init(void);	// Initialization ports
void i2c_start(void);	// Start signal
void i2c_stop(void);	// Stop signal
uint8_t i2c_write_byte(uint8_t); // Byte transfering
uint8_t i2c_read_byte(uint8_t);	 // Byte recieving (1-receiving the last byte)

#endif 
