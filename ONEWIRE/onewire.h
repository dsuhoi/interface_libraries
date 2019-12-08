/*############################################
  ##Библиотека для работы с 1-WIRE.(c)DSuhoi##
  ############################################*/

#ifndef _ONEWIRE_H_
#define _ONEWIRE_H_

#define F_CPU 8000000UL //частота микроконтроллера

#define WIRE_PORT PORTB
#define WIRE_DDR DDRB
#define WIRE_PIN PINB
#define WIRE 0 		//порт интерфейса

uint8_t onewire_init();					//инициализация портов
uint8_t onewire_reset();				//сигнал сброса
void onewire_send_bit(uint8_t bit);		//отправка бита
uint8_t onewire_read_bit();				//прием бита
void onewire_send_byte(uint8_t byte);	//отправка байта
uint8_t onewire_read_byte();			//прием байта
uint8_t onewire_crc(uint8_t crc, uint8_t byte);	//проверка контрольной суммы
uint8_t onewire_skip_rom();						//игнорировать адрес
uint8_t onewire_read_rom(uint8_t * rom_addr);	//чтение адреса устройства
uint8_t onewire_match_rom(uint8_t * rom_addr);	//выбор адреса
uint8_t* onewire_search_rom();					//поиск адресов
uint8_t onewire_last_rom();						//выбор последнего найденного устройства
void search_rom_init();							//настройка поиска адресов

#endif
