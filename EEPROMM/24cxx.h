/*############################################################
  ##Library for working with EEPROMM 24C(02-1024). (c)DSuhoi##
  ############################################################*/

#ifndef _24CXX_H_
#define _24CXX_H_


/*########################Functions#####################################*/
void EEP_write_byte(uint16_t addr, uint8_t byte);			//write byte ("addr" - address)
uint8_t EEP_read_byte(uint16_t addr);				//read byte from "addr" cell
void EEP_write_data(uint16_t addr, uint8_t * data, uint16_t size);  //write array byte ("data" - write array,"size" - size write array) 
uint8_t EEP_read_data(uint16_t addr, uint8_t* data, uint16_t size);	//read array from "addr" cell ("data" - read array, "size" - size read array)

#endif
