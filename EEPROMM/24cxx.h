/*############################################################
  ##Library for working with EEPROMM 24C(02-1024). (c)DSuhoi##
  ############################################################*/

#ifndef _24CXX_H_
#define _24CXX_H_


/*########################Functions#####################################*/
void eepromm_write_byte(uint16_t addr, uint8_t byte);			//write byte ("addr" - address)
uint8_t eepromm_read_byte(uint16_t addr);				//read byte from "addr" cell
void eepromm_write_data(uint16_t addr, uint8_t * data, uint16_t size);  //write array byte ("data" - array,"size" - size array) 
uint8_t* eeprom_read_data(uint16_t addr, uint16_t size);		//read array from "addr" cell ("size" - size read array)

#endif
