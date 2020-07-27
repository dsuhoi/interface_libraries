/*******************************************
 * Библиотека для работы с радиоприёмником.*
 * (c) DSuhoi                              *
 *******************************************/

#ifndef _RADIO
#define _RADIO

// Станции
#define LOVE_RADIO 1076
#define RADIO_VANYA 1070
#define YUMOR_FM 1065
#define NOVOE_RADIO 1060
#define RADIO_RECORD 1045
#define VESTI_FM 1040
#define RADIO_DFM 1035
#define RUS_RADIO 1026
#define DOROG_RADIO 1020
#define AUTORADIO 1015
#define RETRO_FM 1008
#define EUROPlUS 1003
#define STUDIO21 991
#define RADIO_BRYANSK 916
#define RADIO_7 911
#define RADIO_MAYAK 906
#define RADIO_DACHA 902
#define RADIO_32 879

// Кнопки
#define UP (1<<0)
#define DOWN (1<<1)
#define MODE (1<<2)
#define EXIT (1<<3)

// Функции
void button_handler(void);	// Обработчик нажатых кнопок
uint8_t get_button(void);	// Получение нажатой кнопки
void volume_mod(void);		// Настройка уровня громкости
void menu(void);			// Главное Меню
void set_station(uint8_t);	// Установка станции
void init_timer_port(void);	// Настройка портов и таймеров

#endif
