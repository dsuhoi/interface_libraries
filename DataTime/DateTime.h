/* Библиотека для работы с форматом даты  в виде строки (dd.mm.yyyy) (char*),
 * день/месяц/год (integer) и кол-ва дней от нулевого года (long).
 * Исчисление ведется с 01.01.0000 по 31.12.9999 (больший диапазон дат не целесообразен).
 * (Библиотека также включает класс для работы с суточным временем (hh:mm:ss) и
 * класс, являющийся производных от класса даты и времени (hh:mm:ss/dd.mm.yyyy).)
 * Created by DSuhoi (2020). */

#ifndef _DateTime_H_
#define _DateTime_H_

#include <iostream>

////////////////DateTime////////////////////////

class DateTime
{                //класс для хранения даты (dd.mm.yyyy) и взаимодействия с ней
protected:
    long full_day;              //кол-во дней от 0 года
    int day;                    //кол-во дней в данном месяце
    int month;                  //кол-во месяцев в данном году
    int year;                   //кол-во лет

    bool CheckDate();            //проверка полученной даты
    bool StringToDate(char*);    //перевод строки в дни, месяцы и годы
    bool DateToFullDays();       //перевод даты в кол-во дней от 0 года
    void FullDaysToDate();       //перевод кол-ва дней от 0 года в дни, месяцы и годы
public:
    DateTime();             //пустой конструктор на дату (01.01.0000)
    DateTime(char*);        //конструктор через строку
    DateTime(long);         //конструктор через кол-во дней от 0 года
    DateTime(int d,int m,int y);  //конструктор через ручную утсановку даты (день, месяц, год)
    ////////////////////////МЕТОДЫ////////////////////////////////
    int& SetDay();          //установка/получение кол-ва дней в данном месяце
    int& SetMonth();        //установка/получение кол-ва месяцев в данном году
    int& SetYear();         //установка/получение кол-ва лет
    long& SetFullDays();    //установка/получение кол-ва дней от 0 года 
    char* DisplayDate();    //вывод даты в формате dd.mm.yyyy
    void WriteDate();       //установка даты через строку
    void SaveDate();        //сохранение даты после ручного ввода через методы (Set)
    ///////////////////////ОПЕРАТОРЫ/////////////////////////////////
    //перегрузка унарных операторов
    const DateTime& operator ++();       //префиксный инкремент
    const DateTime& operator ++(int);    //постфиксный инкремент
    const DateTime& operator --();       //префиксный денкремент
    const DateTime& operator --(int);    //постфиксный денкремент
    //перегрузка операторов "прибавления/вычитания"
    const DateTime& operator +=(const long);     //прибавляем дни
    const DateTime& operator -=(const long);     //вычитаем дни
    const DateTime& operator +=(DateTime&);      //складываем дату
    const DateTime& operator -=(DateTime&);      //вычитаем дату
    //перегрузка операторов сравнения
    bool operator ==(DateTime&);
    bool operator !=(DateTime&);
    bool operator <(DateTime&);
    bool operator <=(DateTime&);
    bool operator >(DateTime&);
    bool operator >=(DateTime&);
    //перегрузка операторов сложения/вычитания
    const DateTime operator +(const long);   //перегрузка оператора сложения даты и дней
    const DateTime operator -(const long);   //перегрузка оператора вычитания даты и дня
    const DateTime operator +(DateTime&);    //перегрузка оператора сложения двух дат
    const DateTime operator -(DateTime&);    //перегрузка оператора вычитания двух дат
    //перегрузка операторов ввода/вывода
    friend std::ostream& operator <<(std::ostream&, DateTime&); //перегрузка оператора вывода
    friend void operator >>(std::istream&, DateTime&);      //перегруза оператора ввода
};

////////////////ClockTime///////////////////////

class ClockTime
{                   //класс для хранения времени (hh:mm:ss) и взаимодействия с ним
protected:
    long full_second;           //кол-во секунд с начала суток(00:00:00) - общие секунды
    int hour;                   //кол-во часов
    int minute;                 //кол-во минут в данном часе
    int second;                 //кол-во секунд в данной минуте

    bool CheckTime();           //проверка полученного времени
    bool StringToTime(char*);   //перевод строки в часы, минуты и секунды
    bool TimeToFullSecond();    //перевод времени в общие секунды
    int FullSecondToTime();     //перевод общих секунд в часы, минуты и секунды
public:
    ClockTime();                    //пустой конструктор на время (00:00:00)
    ClockTime(char*);               //конструктор через строку
    ClockTime(long);                //конструктор через общие секунды
    ClockTime(int h,int m);         //конструктор через часы и минуты (секунды обнулены)
    ClockTime(int h,int m,int s);   //конструктор через часы, минуты и секунды
    ////////////////////////МЕТОДЫ////////////////////////////////
    int& SetSecond();       //установка/получение кол-ва секунд в данной минуте
    int& SetMinute();       //установка/получение кол-ва минут в данном часе
    int& SetHour();         //установка/получение кол-ва часов
    long& SetFullSecond();  //установка/получение кол-ва общих секунд
    char* DisplayTime();    //вывод времени в формате (hh:mm:ss)
    void WriteTime();       //установка времени через строку
    void SaveTime();        //сохранение времени после ручного ввода через методы (Set)
    ///////////////////////ОПЕРАТОРЫ/////////////////////////////////
    //перегрузка унарных операторов
    const ClockTime& operator ++();       //префиксный инкремент
    const ClockTime& operator ++(int);    //постфиксный инкремент
    const ClockTime& operator --();       //префиксный денкремент
    const ClockTime& operator --(int);    //постфиксный денкремент
    //перегрузка операторов "прибавления/вычитания"
    const ClockTime& operator +=(const long);    //прибавляем секунды
    const ClockTime& operator -=(const long);    //вычитаем секунды
    const ClockTime& operator +=(ClockTime&);    //складываем время
    const ClockTime& operator -=(ClockTime&);    //вычитаем время
    //перегрузка операторов сравнения
    bool operator ==(ClockTime&);
    bool operator !=(ClockTime&);
    bool operator <(ClockTime&);
    bool operator <=(ClockTime&);
    bool operator >(ClockTime&);
    bool operator >=(ClockTime&);
    //перегрузка операторов сложения/вычитания
    const ClockTime operator +(const long);    //перегрузка оператора сложения времени и секунд
    const ClockTime operator -(const long);    //перегрузка оператора вычитания времени и секунд
    const ClockTime operator +(ClockTime&);    //перегрузка оператора сложения двух времен
    const ClockTime operator -(ClockTime&);    //перегрузка оператора вычитания двух времен
    //перегрузка операции ввода/вывода
    friend std::ostream& operator <<(std::ostream, ClockTime&); //перегрузка оператора вывода
    friend void operator >>(std::istream&, ClockTime&);     //перегрузка оператора ввода
};

///////////////AllDateTime//////////////////////

class AllDateTime : public DateTime, public ClockTime
{                   //класс для хранения полной даты (hh:mm:ss/dd.mm.yyyy) и взаимодействия с ней
protected:
    bool CheckAllDate();                //проверка полученной полной даты
    bool StringToAllDate(char*);        //перевод строки в дату и время (полную дату)
    bool AllDateToFullParam();          //перевод полной даты в обшие секунды и дни с 0 года
    void FullParamToAllDate();          //перевод общих параметров в полную дату
public:
    AllDateTime();          //пустой конструктор на полную дату (00:00:00/01.01.0000)
    AllDateTime(char*);     //конструктор через строку
    AllDateTime(int h, int mi, int s, int d, int mo, int y);    //конструктор через время и дату
    AllDateTime(int d, int mo, int y);      //конструктор через дату (00:00:00/dd.mm.yyyy)
    AllDateTime(long t, long d);        //конструктор через общие параметры (t - секунды, d - дни)
    ////////////////////////МЕТОДЫ////////////////////////////////
    char* DisplayAllDate();      //вывод полной даты в формате (hh:mm:ss/dd.mm.yyyy)
    void WriteAllDate();         //установка полной даты через строку
    void SaveAllDate();          //сохранение полной даты после ручного ввода через методы (Set)
    ///////////////////////ОПЕРАТОРЫ/////////////////////////////////
    //перегрузка унарных операторов
    const AllDateTime& operator ++();       //префиксный инкремент
    const AllDateTime& operator ++(int);    //постфиксный инкремент
    const AllDateTime& operator --();       //префиксный денкремент
    const AllDateTime& operator --(int);    //постфиксный денкремент
    //перегрузка операторов "прибавления/вычитания"
    const AllDateTime& operator +=(const long);     //прибавляем секунды
    const AllDateTime& operator -=(const long);     //вычитаем секунды
    const AllDateTime& operator +=(DateTime&);      //складываем время
    const AllDateTime& operator -=(DateTime&);      //вычитаем время
    const AllDateTime& operator +=(ClockTime&);     //складываем дату
    const AllDateTime& operator -=(ClockTime&);     //вычитаем дату
    const AllDateTime& operator +=(AllDateTime&);   //складываем полную дату
    const AllDateTime& operator -=(AllDateTime&);   //вычитаем полную дату
    //перегрузка операторов сравнения
    bool operator ==(AllDateTime&);
    bool operator !=(AllDateTime&);
    bool operator <(AllDateTime&);
    bool operator <=(AllDateTime&);
    bool operator >(AllDateTime&);
    bool operator >=(AllDateTime&);
    //перегрузка операторов сложения/вычитания
    const AllDateTime operator +(const long);  //перегрузка оператора сложения полной даты и секунд
    const AllDateTime operator -(const long);  //перегрузка оператора вычитания полной даты и секунд
    const AllDateTime operator +(DateTime&);   //перегрузка оператора сложения полной даты и даты
    const AllDateTime operator -(DateTime&);   //перегрузка оператора вычитания полной даты и даты
    const AllDateTime operator +(ClockTime&);  //перегрузка оператора сложения полной даты и времени
    const AllDateTime operator -(ClockTime&);  //перегрузка оператора вычитания полной даты и времени
    const AllDateTime operator +(AllDateTime&);   //перегрузка оператора сложения двух полных дат
    const AllDateTime operator -(AllDateTime&);   //перегрузка оператора вычитания двух полных дат
    //перегрузка операторов ввода/вывода
    friend std::ostream& operator <<(std::ostream&, AllDateTime&);  //перегрузка оператора вывода
    friend void operator >>(std::istream&, AllDateTime&);       //перегрузка оператора ввода
};


#endif // _DateTime_H_
