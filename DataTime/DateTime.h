/* Библиотека для работы с форматом даты  в виде строки (dd.mm.yyyy) (char*),
 * день/месяц/год (integer) и кол-ва дней от нулевого года (long).
 * Исчисление ведется с 01.01.0000 по 31.12.9999 (больший диапазон дат не целесообразен).
 * (Библиотека также включает класс для работы с суточным временем (hh:mm:ss) и
 * класс, являющийся производных от класса даты и времени (hh:mm:ss/dd.mm.yyyy).)
 * Created by DSuhoi (2020). */

#ifndef _DATATIME_H_
#define _DATATIME_H_


////////////////CONSTANTS///////////////////////

const int DATA_LEN = 11;  //размер символьного массива даты (НЕ МЕНЕЕ 11 символов включая '\0')
const int TIME_LEN = 9;   //размер символьного массива времени (НЕ МЕНЕЕ 9 символов включая '\0')
const int ALLDATA_LEN = 20; //размер символьного массива полного времени (НЕ МЕНЕЕ 20 символов)

////////////////DataTime////////////////////////

class DataTime
{                //класс для хранения даты (dd.mm.yyyy) и взаимодействия с ней
protected:
    char data_str[DATA_LEN];    //символьный массив для даты
    long full_day;              //кол-во дней от 0 года
    int day;                    //кол-во дней в данном месяце
    int month;                  //кол-во месяцев в данном году
    int year;                   //кол-во лет

    inline void DATA_CLEAN();    //функия очистки символьного массива
    inline void DATA_INLINE();   //функция обработки принятой даты (строки)

    void StringToData();         //перевод строки в дни, месяцы и годы
    void DataToString();         //перевод в формат dd.mm.yyyy
    void DataToFullDays();       //перевод даты в кол-во дней от 0 года
    void FullDaysToData();       //перевод кол-ва дней от 0 года в дни, месяцы и годы
public:
    DataTime();             //пустой конструктор на дату (01.01.0000)
    DataTime(char*);        //конструктор через строку
    DataTime(long);         //конструктор через кол-во дней от 0 года
    DataTime(int d,int m,int y);  //конструктор через ручную утсановку даты (день, месяц, год)
    ////////////////////////МЕТОДЫ////////////////////////////////
    int& SetDay();          //установка/получение кол-ва дней в данном месяце
    int& SetMonth();        //установка/получение кол-ва месяцев в данном году
    int& SetYear();         //установка/получение кол-ва лет
    long& SetFullDays();    //установка/получение кол-ва дней от 0 года
    char* DisplayData();    //вывод даты в формате dd.mm.yyyy
    void WriteData();       //установка даты через строку
    void SaveData();        //сохранение даты после ручного ввода через методы (Set)
    ///////////////////////ОПЕРАТОРЫ/////////////////////////////////
    //перегрузка унарных операторов
    const DataTime& operator ++();       //префиксный инкремент
    const DataTime& operator ++(int);    //постфиксный инкремент
    const DataTime& operator --();       //префиксный денкремент
    const DataTime& operator --(int);    //постфиксный денкремент
    //перегрузка операторов "прибавления/вычитания"
    const DataTime& operator +=(const long);     //прибавляем дни
    const DataTime& operator -=(const long);     //вычитаем дни
    const DataTime& operator +=(DataTime&);      //складываем дату
    const DataTime& operator -=(DataTime&);      //вычитаем дату
    //перегрузка операторов сравнения
    bool operator ==(DataTime&);
    bool operator !=(DataTime&);
    bool operator <(DataTime&);
    bool operator <=(DataTime&);
    bool operator >(DataTime&);
    bool operator >=(DataTime&);
    //перегрузка операторов сложения/вычитания
    const DataTime operator +(const long);   //перегрузка оператора сложения даты и дней
    const DataTime operator -(const long);   //перегрузка оператора вычитания даты и дня
    const DataTime operator +(DataTime&);    //перегрузка оператора сложения двух дат
    const DataTime operator -(DataTime&);    //перегрузка оператора вычитания двух дат
};

////////////////ClockTime///////////////////////

class ClockTime
{                   //класс для хранения времени (hh:mm:ss) и взаимодействия с ним
protected:
    char time_str[TIME_LEN];    //символьный массив для времени
    long full_second;           //кол-во секунд с начала суток(00:00:00) - общие секунды
    int second;                 //кол-во секунд в данной минуте
    int minute;                 //кол-во минут в данном часе
    int hour;                   //кол-во часов

    inline void TIME_CLEAN();     //функия очистки символьного массива
    inline void TIME_INLINE();    //функция обработки принятого времени (строки)

    void StringToTime();        //перевод строки в часы, минуты и секунды
    void TimeToString();        //перевод времени в строку
    void TimeToFullSecond();    //перевод времени в общие секунды
    virtual void FullSecondToTime();    //перевод общих секунд в часы, минуты и секунды
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
};

///////////////AllDataTime//////////////////////

class AllDataTime : public DataTime, public ClockTime
{                   //класс для хранения полной даты (hh:mm:ss/dd.mm.yyyy) и взаимодействия с ней
private:
    char alldata_str[ALLDATA_LEN];      //символьный массив для даты и времени
protected:
    inline void ALLDATA_CLEAN();        //функия очистки символьного массива
    inline void STR_INLINE();           //функция обработки принятой полной даты (строки)

    void StringToAllData();             //перевод строки в дату и время (полную дату)
    void AllDataToString();             //перевод даты и времени в строку
    void AllDataToFullParam();          //перевод полной даты в обшие секунды и дни с 0 года
    void FullParamToAllData();          //перевод общих параметров в полную дату
    virtual void FullSecondToTime();    //переопределение метода перевода общих секунд во время
public:
    AllDataTime();          //пустой конструктор на полную дату (00:00:00/01.01.0000)
    AllDataTime(int h, int mi, int s, int d, int mo, int y);    //конструктор через время и дату
    AllDataTime(int d, int mo, int y);      //конструктор через дату (00:00:00/dd.mm.yyyy)
    AllDataTime(long t, long d);        //конструктор через общие параметры (t - секунды, d - дни)
    ////////////////////////МЕТОДЫ////////////////////////////////
    char* DisplayAllData();      //вывод полной даты в формате (hh:mm:ss/dd.mm.yyyy)
    void WriteAllData();         //установка полной даты через строку
    void SaveAllData();          //сохранение полной даты после ручного ввода через методы (Set)
    ///////////////////////ОПЕРАТОРЫ/////////////////////////////////
    //перегрузка унарных операторов
    const AllDataTime& operator ++();       //префиксный инкремент
    const AllDataTime& operator ++(int);    //постфиксный инкремент
    const AllDataTime& operator --();       //префиксный денкремент
    const AllDataTime& operator --(int);    //постфиксный денкремент
    //перегрузка операторов "прибавления/вычитания"
    const AllDataTime& operator +=(const long);     //прибавляем секунды
    const AllDataTime& operator -=(const long);     //вычитаем секунды
    const AllDataTime& operator +=(DataTime&);      //складываем время
    const AllDataTime& operator -=(DataTime&);      //вычитаем время
    const AllDataTime& operator +=(ClockTime&);     //складываем дату
    const AllDataTime& operator -=(ClockTime&);     //вычитаем дату
    const AllDataTime& operator +=(AllDataTime&);   //складываем полную дату
    const AllDataTime& operator -=(AllDataTime&);   //вычитаем полную дату
    //перегрузка операторов сравнения
    bool operator==(AllDataTime&);
    bool operator!=(AllDataTime&);
    bool operator<(AllDataTime&);
    bool operator<=(AllDataTime&);
    bool operator>(AllDataTime&);
    bool operator>=(AllDataTime&);
    //перегрузка операторов сложения/вычитания
    const AllDataTime operator +(const long);  //перегрузка оператора сложения полной даты и секунд
    const AllDataTime operator -(const long);  //перегрузка оператора вычитания полной даты и секунд
    const AllDataTime operator +(DataTime&);   //перегрузка оператора сложения полной даты и даты
    const AllDataTime operator -(DataTime&);   //перегрузка оператора вычитания полной даты и даты
    const AllDataTime operator +(ClockTime&);  //перегрузка оператора сложения полной даты и времени
    const AllDataTime operator -(ClockTime&);  //перегрузка оператора вычитания полной даты и времени
    const AllDataTime operator +(AllDataTime&);   //перегрузка оператора сложения двух полных дат
    const AllDataTime operator -(AllDataTime&);   //перегрузка оператора вычитания двух полных дат
};


#endif // _DATATIME_H_
