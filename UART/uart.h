/*######################################################
  ##Библиотека создана для работы с UART. Поддерживает##
  ##модели МК AVR:    atmega(8/16/32/328(p)/644(p))   ##
  ##Нужные модели можно добавить из avr/io.h (c)DSuhoi##      
  ######################################################*/

#ifndef __UART_H__
#define __UART_H__

#define ISR_COUNT 1//параметр использования UART обработчика и буфера(0-off, 1-on)

#define F_CPU 8000000UL	//частота микроконтроллера
#define ELEMENTS 512    // объем uart буфера
//очистка UART буфера
#define BUF_CLEAR {for(uint16_t i=0; i<ELEMENTS; buffer_uart[i++]=0); index_buf=0;}

//нужные микроконтроллеры можно добавить самим
#if (__AVR_ATmega328P__) || (__AVR_ATmega328__) || (__AVR_ATmega644P__) || (__AVR_ATmega644__) || (__AVR_ATmega644A__)
#define MKREG
#endif

void uart_init(unsigned long baud); //инициализация uart'а; baud - скорость(4800,9600,19200...)
void uart_tr(uint8_t); //передача байта
uint8_t uart_receive_byte(void); //прием байта
void uart_send(char*); //отправка строки
void uart_sendln(char*); //отправка строки с переходом на новую

#if ISR_COUNT
void uart_receive(void); //функция подставляется в прерывание с вектрором (USART0_RX_vect)
#endif

#endif
