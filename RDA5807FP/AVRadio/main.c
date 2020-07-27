#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "../../I2C/i2c.h"
#include "LCD/LCD.h"
#include "../RDA5807FP.h"
#include "Radio/RADIO.h"

extern uint8_t selectStation;
extern uint8_t selectVolume;
extern uint16_t frequency;
extern uint8_t station_ee EEMEM;

// Прерывание для обработки нажатых кнопок
ISR (TIMER0_OVF_vect)
{
	button_handler();
}

int main(void)
{
	init_timer_port();	// Настройка портов и таймеров
	i2c_init();		// Настройка I2C интерфейса
	FM_init();		// Инициализация радиомодуля
	LCDinit();		// Инициализация дисплея
	LCDstring("AVRadio FM",0,0);
	LCDstring("by DSuhoi (2019)",0,1);
	_delay_ms(1500);	// Задержка для ожидания радиомодуля

	selectStation = eeprom_read_byte(&station_ee); // Чтение номера станции из EEPROMM
	set_station(selectStation);	// Установка радиостанции
	Set_volume(selectVolume);	// Установка уровня громкости
	sei();				// Включение обработки глобальных прерываний

	while(1){
		LCDstring("Freq: ",1,0);
		LCDstring("MHz",13,0);

		switch((uint8_t)get_button()){
		case 1: 	// Настройка частоты радиоприёмника
			frequency++; 
			if(frequency > 1080){
				frequency=870;
			} 
			SetFreq(frequency); 
			break; 
		case 2: 
			frequency--; 
			if(frequency < 870){
				frequency = 1080;
			} 
			SetFreq(frequency); 
			break;
		case 3: // Меню для настройка радиостанции
			LCDclear(); 
			menu(); 
			break; 
		case 4: // Настройка звука
			volume_mod(); 
			break; 
		};
		// Расчёт частоты принимаемой волны
		uint8_t f1=frequency/1000;			
		uint8_t f2=frequency/100-f1*10;
		uint8_t f3=frequency/10-f1*100-f2*10;
		uint8_t f4=frequency-f1*1000-f2*100-f3*10;
		// Вывод частоты на дисплей
		LCDGotoXY(7,0);
		if(f1 > 0){
			LCDdata(f1+'0');
		} 
		else{
			LCDdata(' ');
		}
		LCDdata(f2+'0');
		LCDdata(f3+'0');
		LCDdata('.');
		LCDdata(f4+'0');

		_delay_ms(100);
		LCDclear();
	} 
}
