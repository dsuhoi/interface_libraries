/*###########################################################
  ##Library for working with EEPROM 24C(02-1024). (c)DSuhoi##
  ###########################################################*/

#ifndef _24CXX_H_
#define _24CXX_H_

/*########################Constants####################################*/
// Master
#define TW_START                    0x08  // START condition
#define TW_REP_START                0x10  // RESTART condition
#define TW_READ                     0xA1  // READ condition
// Master Transmitter
#define TW_MT_SLA_ACK               0x18  // The master sent the address and the recording bit. The slave confirmed his address
#define TW_MT_SLA_NACK              0x20  // The master sent the address and the recording bit. No confirmation of acceptance
#define TW_MT_DATA_ACK              0x28  // The master transmitted the data and the slave confirmed the reception.
#define TW_MT_DATA_NACK             0x30  // The master passed the data. No confirmation of acceptance
#define TW_MT_ARB_LOST              0x38  // Loss of priority
// Master Receiver
#define TW_MR_ARB_LOST              0x38  // Loss of priority
#define TW_MR_SLA_ACK               0x40  // The master sent the address and the read bit. The slave confirmed his address
#define TW_MR_SLA_NACK              0x48  // The master sent the address and the read bit. No confirmation of acceptance
#define TW_MR_DATA_ACK              0x50  // The master accepted the data and passed the confirmation
#define TW_MR_DATA_NACK             0x58  // The master accepted the data and did not pass the confirmation
// Slave Transmitter
#define TW_ST_SLA_ACK               0xA8  // Getting the address and read bit, returning the confirmation
#define TW_ST_ARB_LOST_SLA_ACK      0xB0  // Loss of priority, getting the address and read bit, returning the confirmation
#define TW_ST_DATA_ACK              0xB8  // Data is transmitted, confirmation from the master is accepted
#define TW_ST_DATA_NACK             0xC0  // Data is transmitted. There is no confirmation of reception from the master.
#define TW_ST_LAST_DATA             0xC8  // The last transmitted data byte, acknowledge the receipt of the
// Slave Receiver
#define TW_SR_SLA_ACK               0x60  // Getting the address and record bit, returning the confirmation
#define TW_SR_ARB_LOST_SLA_ACK      0x68  // Loss of priority, getting the address and write bit, returning the confirmation
#define TW_SR_GCALL_ACK             0x70  // Accepting a General request and returning a confirmation
#define TW_SR_ARB_LOST_GCALL_ACK    0x78  // Loss of priority, acceptance of a General request, return of confirmation
#define TW_SR_DATA_ACK              0x80  // Receiving data, returning confirmation
#define TW_SR_DATA_NACK             0x88  // The data was transmitted without confirmation.
#define TW_SR_GCALL_DATA_ACK        0x90  // Receiving data for a General request, and returning a confirmation
#define TW_SR_GCALL_DATA_NACK       0x98  // Receiving data for a General request, without confirmation
#define TW_SR_STOP                  0xA0  // STOP condition
// Misc
#define TW_NO_INFO                  0xF8  // Status information is missing
#define TW_BUS_ERROR                0x00  // Bus error

/*########################Functions#####################################*/
void EEP_write_byte(uint16_t addr, uint8_t byte);           // Write byte ("addr" - address)
uint8_t EEP_read_byte(uint16_t addr);                       // Read byte from "addr" cell
void EEP_write_data(uint16_t addr, uint8_t * data, uint16_t size);      // Write array byte ("data" - write array,"size" - size write array) 
uint8_t EEP_read_data(uint16_t addr, uint8_t* data, uint16_t size);     // Read array from "addr" cell ("data" - read array, "size" - size read array)

#endif
