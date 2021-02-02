#ifndef _RADIO
#define _RADIO

#include <stdint.h>

// Станции
typedef struct
{
    const char* name;
    uint16_t id;
} station_t;

// Кнопки
#define UP   (1 << 0)
#define DOWN (1 << 1)
#define MODE (1 << 2)
#define EXIT (1 << 3)

// Функции
void button_handler();  // Обработчик нажатых кнопок
uint8_t get_button();   // Получение нажатой кнопки
void volume_mod();      // Настройка уровня громкости
void menu();            // Главное Меню
void set_station(uint8_t);  // Установка станции
void init_timer_port();  // Настройка портов и таймеров

#endif
