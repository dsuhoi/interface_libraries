#include <inttypes.h>

// #define LCD_8BIT #define LCD_8BIT

#ifndef LCD
#define LCD

// Указываем порт к которому подключены выводы дисплея LCD DB0...DB7.
#define DPIN  PINB
#define DDDR  DDRB
#define DPORT PORTB

//Пины  МК      LCD
//#define DB0	// DB0
//#define DB1	// DB1
//#define DB2	// DB2
//#define DB3	// DB3
#define DB4 0  // DB4
#define DB5 1  // DB5
#define DB6 2  // DB6
#define DB7 3  // DB7 + BF флаг занятости дисплея.

// Указываем порт к которому подключены выводы дисплея E, RS, R/W.
#define CDDR  DDRD
#define CPORT PORTD

// Указываем номера пинов МК, к которым подключаем дисплей.
#define E  7  // E	 СТРОБ.
#define RW 6  // R/W   R/W=1 читаем из LCD, R/W=0 записываем в LCD.
#define RS 5  // RS=0 посылаем команду в LCD, RS=1 посылаем данные в LCD.

//----Настройки закончены-----

//Пользовательские функции, ими пользуемся в программе.
void LCDinit(void);  //Инициализация LCD
void LCDcommand(uint8_t);  //Отправка команды, настройка дисплея
void LCDGotoXY(uint8_t, uint8_t);  //Устанавливаем курсор в X, Y позицию
void LCDdata(uint8_t);  //Вывести 1 символ на дисплей.
void LCDstring(char* i, uint8_t,
               uint8_t);  //Вывести строку на дисплей в позицию x,y
void LCDstring_of_sram(
    uint8_t*, uint8_t, uint8_t,
    uint8_t);  //Вывести строку на дисплей в позицию x,y из ОЗУ
void LCDstring_of_flash(const uint8_t*, uint8_t,
                        uint8_t);  //Вывести строку в позицию x,y из флеша
void LCDset(void);  //Двухстрочный дисплей 5x8 точек.
void LCDblank(void);  //Сделать невидимым инфо на дисплее
void LCDnblank(
    void);  //Сделать видимой инфо на дисплее + отключение видимых курсоров.
void LCDclear(void);  //Очистить дисплей от инфо + курсор на позицию 0,0
void LCDcursor_bl(void);  //Включить мигающий курсор
void LCDcursor_on(void);  //Включить подчеркивающий курсор
void LCDcursor_vi(void);  //Включить оба курсора
void LCDcursorOFF(void);  //Выключить курсор (любой)
void LCDacr(void);  // Cчетчик адреса AC всегда будет смещаться на n+1
void LCDacl(void);  // Cчетчик адреса AC всегда будет смещаться на n-1
void LCDcursorl(void);  //Сместить курсор влево на 1 символ
void LCDcursorr(void);  //Сместить курсор вправо на 1 символ
void LCDcursorln(uint8_t);  //Сместить курсор влево на n символов
void LCDcursorrn(uint8_t);  //Сместить курсор вправо на n символов
void LCDscreenl(void);  //Сместить экран влево на 1 символ
void LCDscreenr(void);  //Сместить экран вправо на 1 символ
void LCDscreenln(uint8_t);  //Сместить экран влево на n символов
void LCDscreenrn(uint8_t);  //Сместить экран вправо на n символов
void LCDscreenL(void);  //С каждым новым символом экран будет смещаться влево
void LCDscreenR(void);  //С каждым новым символом экран будет смещаться вправо
void LCDresshift(
    void);  //Курсор в позицию 0,0 + сброс всех сдвигов, изображение остается

//Двухстрочный дисплей.
#define LINE0 0x00
#define LINE1 0x40

#endif
