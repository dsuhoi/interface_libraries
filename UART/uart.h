/*#####################################################################################
  ##Library for working with UART. Supports AVR models: atmega(8/16/32/328(p)/644(p))##
  ##The desired models can be added from #include <avr/io.h>.           (c)DSuhoi##      
  #####################################################################################*/

#ifndef __UART_H__
#define __UART_H__

/*########################Constants####################################*/
#define ISR_COUNT 0     // Parameter of using UART handler and buffer(0-off, 1-on)

#define F_CPU 8000000UL // Frequency of the microcontroller
#define ELEMENTS 512    //UART buffer size
// Erasing the UART buffer
#define BUF_CLEAR {for(uint16_t i=0; i<ELEMENTS; buffer_uart[i++]=0); index_buf=0;}

// The necessary microcontrollers can be added by yourself
#if (__AVR_ATmega328P__) || (__AVR_ATmega328__) || (__AVR_ATmega644P__) || (__AVR_ATmega644__) || (__AVR_ATmega644A__)
#define MKREG
#endif

/*######################################Functions################################################*/
void uart_init(unsigned long baud);     // Initialization uart; baud - speed(4800,9600,19200...)
void uart_tr(uint8_t);                  // Byte transfering
uint8_t uart_receive_byte(void);        // Byte recieving
void uart_send(char*);                  // Send string
void uart_sendln(char*);                // Send string with "\r\n"

#if ISR_COUNT
void uart_receive(void);    // Function is inserted into the interrupt with the vector (USART0_RX_vect)
#endif

#endif
