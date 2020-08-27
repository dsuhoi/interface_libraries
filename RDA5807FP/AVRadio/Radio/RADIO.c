#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "../LCD/LCD.h"
#include "../../RDA5807FP.h"
#include "RADIO.h"


uint16_t frequency = 1000;      // Частота
uint8_t selectStation = 1;      // Номер радиостанции
uint8_t selectVolume = 5;       // Звук
uint8_t pausa;                  // Задержка
uint8_t currentButton;          // Нажатая кнопка
uint8_t station_ee EEMEM;       // Номер радиостанции в EEPROMM

// Обработчик нажатых кнопок
void button_handler(void)
{
    char button = 0;
    // Определение кнопки
    if((PINC & UP) == 0)
        button = 1;
    else if((PINC & DOWN) == 0)
        button = 2;
    else if((PINC & MODE) == 0)
        button = 3;
    else if((PINC & EXIT) == 0)
        button = 4;
    
    // Создание задержки для обработки нажатий
    if(button) {
        char long_hold = 10;
        if(pausa > long_hold) {
            pausa = long_hold - 2;
            currentButton = button;
            return;
        }
        pausa++;
        char short_hold = 3;
        if(pausa == short_hold) {
            currentButton = button;
            return;
        }
    } else { 
        pausa = 0;
    }
}


uint8_t get_button()
{
    uint8_t reg = currentButton;
    // Обнуление кнопки для дальнейшего считывания
    currentButton = 0;  
    return reg;
}

// Установка станции
void set_station (uint8_t station)
{
    switch(station) {
    case 1:
        setFreq(LOVE_RADIO);
        frequency = LOVE_RADIO;
        LCDstring("Love Radio", 0, 1);
        break;
    case 2:
        setFreq(RADIO_VANYA);  
        frequency = RADIO_VANYA;    
        LCDstring("Radio Vanya", 0, 1);
        break;
    case 3:
        setFreq(YUMOR_FM);
        frequency = YUMOR_FM;
        LCDstring("Yumor FM", 0, 1);
        break;
    case 4:
        setFreq(NOVOE_RADIO);  
        frequency = NOVOE_RADIO;    
        LCDstring("Novoe Radio", 0, 1);
        break;
    case 5:
        setFreq(RADIO_RECORD); 
        frequency = RADIO_RECORD;   
        LCDstring("Radio Record", 0, 1);
        break;
    case 6:
        setFreq(VESTI_FM);     
        frequency=VESTI_FM;       
        LCDstring("Vesti FM", 0, 1);
        break;
    case 7:
        setFreq(RADIO_DFM);    
        frequency = RADIO_DFM;      
        LCDstring("Radio DFM", 0, 1);
        break;
    case 8:
        setFreq(RUS_RADIO);    
        frequency = RUS_RADIO;      
        LCDstring("Russkoe Radio", 0, 1);
        break;
    case 9:
        setFreq(DOROG_RADIO);  
        frequency = DOROG_RADIO;    
        LCDstring("Dorognoe Radio", 0, 1);
        break;
    case 10:
        setFreq(AUTORADIO);   
        frequency = AUTORADIO;      
        LCDstring("AutoRadio", 0, 1);
        break;
    case 11:
        setFreq(RETRO_FM);    
        frequency = RETRO_FM;
        LCDstring("Retro FM", 0, 1);
        break;
    case 12:
        setFreq(EUROPlUS);    
        frequency = EUROPlUS;
        LCDstring("EuroPlus", 0, 1);
        break;
    case 13:
        setFreq(STUDIO21);    
        frequency = STUDIO21;
        LCDstring("Studio21", 0, 1);
        break;
    case 14:
        setFreq(RADIO_BRYANSK); 
        frequency = RADIO_BRYANSK; 
        LCDstring("Radio Bryansk", 0, 1);
        break;
    case 15:
        setFreq(RADIO_7); 
        frequency = RADIO_7;  
        LCDstring("Radio 7", 0, 1);
        break;
    case 16:
        setFreq(RADIO_MAYAK);   
        frequency = RADIO_MAYAK;  
        LCDstring("Radio Mayak", 0, 1);
        break;
    case 17:
        setFreq(RADIO_DACHA);   
        frequency = RADIO_DACHA;  
        LCDstring("Radio Dacha", 0, 1);
        break;
    case 18:
        setFreq(RADIO_32);      
        frequency = RADIO_32;   
        LCDstring("Radio 32", 0, 1);
        break;
    };
    // Сохранение номера станции в EEPROMM
    eeprom_write_byte(&station_ee, station);
}

// Настройка уровня громкости динамиков
void volume_mod(void)
{
    LCDclear();
    LCDstring("Volume:", 0, 1);
    uint8_t select = 1;
    while(select) {
        switch((uint8_t)get_button()) {
        case 1: // Настройка громкости
            selectVolume++; 
            if(selectVolume > 15)
                selectVolume = 15;
            set_volume(selectVolume); 
            break;
        case 2: 
            selectVolume--; 
            if(selectVolume < 1)
                selectVolume = 1;
            set_volume(selectVolume); 
            break;
        case 3: // Включение подсветки дисплея
            if(PORTB & (1<<4))
                PORTB &=~(1<<4);
            else
                PORTB |=(1<<4);
            break;
        case 4: // Выход из цикла
            select = 0; 
            break;
        };

        LCDGotoXY(7, 1);
        LCDdata(selectVolume/10 + '0');
        if(selectVolume >= 10)
            LCDdata((selectVolume - 10) + '0');
        else
            LCDdata(selectVolume + '0');
        _delay_ms(100);
    }
    return;
}

// Главное Меню
void menu(void)
{
    uint8_t select = 1;
    while(select) {
        LCDstring("*Freq:", 0, 0);
        LCDstring("MHz", 13, 0);
        // Вывод частоты на дисплей по разрядам
        uint8_t f1 = frequency/1000;
        uint8_t f2 = frequency/100 - f1*10;
        uint8_t f3 = frequency/10 - f1*100-f2*10;
        uint8_t f4 = frequency - f1*1000 - f2*100 - f3*10;
        
        LCDGotoXY(7, 0);
        if(f1 > 0)
            LCDdata(f1 + '0');
        else
            LCDdata(' ');

        LCDdata(f2 + '0');
        LCDdata(f3 + '0');
        LCDdata('.');
        LCDdata(f4 + '0');

        switch((uint8_t)get_button()) {
        case 1: // Выбор станции
            --selectStation; 
            if(selectStation < 1)
                selectStation = 18;
            LCDclear(); 
            set_station(selectStation);  
            break;
        case 2: 
            ++selectStation; 
            if(selectStation > 18)
                selectStation = 1;
            LCDclear(); 
            set_station(selectStation);  
            break;
        case 3: // Выход из цикла
            select = 0; 
            break;
        case 4: // Настройка звука
            volume_mod(); 
            break;
        };
        _delay_ms(100);
    }
}

// Настройка портов и таймеров
void init_timer_port(void)
{
    TCCR0 |= 0x05;
    TIMSK |= 0x01;
    TCNT0 = 0;
    DDRC = 0x00;
    DDRB |=0x10;
    PORTC |= UP | DOWN | EXIT | MODE;
}
