//Created by DSuhoi (2020).//
#include <iostream>
#include <cstring>
#include "DateTime.h"


//////////////////////DataTime//////////////////////////////
///////////////////////МЕТОДЫ//////////////////////////////

    //функия очистки символьного массива
inline void DataTime::DATA_CLEAN()
{
     for(int i=0;i<DATA_LEN; data_str[i++]=0);   //очистка массива
}

    //функция обработки принятой даты (строки)
inline void DataTime::DATA_INLINE()
{
    for(;;) //пока не будет соблюден формат введенной даты
    {
        DATA_CLEAN();
        scanf("%s",data_str);
        if(data_str[2]!='.' || data_str[5]!='.' || data_str[10]!=0)
        { std::cout << "ERROR: Print Date(dd.mm.yyyy)!" <<std::endl; }
        else    //если все принято, то выходим из цикла
        { break; }
    }
}


    //пустой конструктор на дату (01.01.0000)
DataTime::DataTime()
{
    day = 1; month = 1; year = 0; full_day = 1; //установка по умолчанию всех данных
    DataToString();
}

    //конструктор через кол-во дней от 0 года
DataTime::DataTime(long l) : full_day(l)
{ FullDaysToData(); DataToString(); }

    //конструктор через ручную утсановку даты (день, месяц, год)
DataTime::DataTime(int d, int m, int y) : day(d), month(m), year(y)
{ DataToFullDays(); DataToString(); }

    //конструктор через строку
DataTime::DataTime(char *buff)
{
    strcpy(data_str,buff);  //копируем строку в массив для даты
    StringToData();
    DataToFullDays();
}

    //установка/получение кол-ва дней в данном месяце
int& DataTime::SetDay()
{
    return day;
}

    //установка/получение кол-ва месяцев в данном году
int& DataTime::SetMonth()
{
    return month;
}

    //установка/получение кол-ва лет
int& DataTime::SetYear()
{
    return year;
}

    //установка/получение кол-ва дней от 0 года
long& DataTime::SetFullDays()
{
    DataToFullDays();
    return full_day;
}

    //вывод даты в формате dd.mm.yyyy
char* DataTime::DisplayData()
{
    DataToString();
    return data_str;
}

/////////////////////ФУНКЦИИ ПРИВЕДЕНИЯ///////////////////////////

    //перевод строки в дни, месяцы и годы
void DataTime::StringToData()
{
    day = (data_str[0]-'0')*10 + (data_str[1]-'0');
    month = (data_str[3]-'0')*10 + (data_str[4]-'0');
    year = (data_str[6]-'0')*1000 + (data_str[7]-'0')*100 + (data_str[8]-'0')*10 + (data_str[9]-'0');
}

    //перевод в формат dd.mm.yyyy
void DataTime::DataToString()
{
    DATA_CLEAN();
    data_str[2]=data_str[5]='.';
    data_str[0] = day/10 + '0';
    data_str[1] = (day%10) + '0';
    data_str[3] = month/10 + '0';
    data_str[4] = (month%10) + '0';
    data_str[6] = year/1000 + '0';
    data_str[7] = (year/100 - (year/1000)*10) + '0';
    if(year>99)
    {
    data_str[8] = (year/10 - (year/100)*10) + '0';
    data_str[9] = (year - (year/10)*10) + '0';
    }
    else
    {
    data_str[8] = year/10 + '0';
    data_str[9] = (year - (year/10)*10) + '0';
    }
}

    //перевод даты в кол-во дней от 0 года
void DataTime::DataToFullDays()
{
    full_day = 0;   //сбрасываем кол-во дней
    bool visokos_count = (((!(year%4))&&(year%100)) || (!(year%400)))&&year; //определение високосного года
    int visokos_num = year/4 - (year/100 - year/400); //кол-во високосных лет

    switch (month)
    {               //определение кол-ва дней через месяц
    case 1:
        full_day += day;
        break;
    case 2:
        full_day += day + 31;
        break;
    case 3:
        if(visokos_count) full_day += day + 60;  //счет дней по високосным годам
            else full_day += day + 59;
        break;
    case 4:
        if(visokos_count) full_day += 91 + day;
            else full_day += 90+day;
        break;
    case 5:
        if(visokos_count) full_day += 121 + day;
            else full_day += 120 + day;
        break;
    case 6:
        if(visokos_count) full_day += 152 + day;
            else full_day += 151 + day;
        break;
    case 7:
        if(visokos_count) full_day += 182 + day;
            else full_day += 181 + day;
        break;
    case 8:
        if(visokos_count) full_day += 213 + day;
            else full_day += 212 + day;
        break;
    case 9:
        if(visokos_count) full_day += 244 + day;
            else full_day += 243 + day;
        break;
    case 10:
        if(visokos_count) full_day += 274 + day;
            else full_day += 273 + day;
        break;
    case 11:
        if(visokos_count) full_day += 305 + day;
            else full_day += 304 + day;
        break;
    case 12:
        if(visokos_count) full_day += 335 + day;
            else full_day += 334 + day;
        break;
    default: std::cout << "ERROR: MONTH!" << std::endl; //если как-то ввели неправильный месяц...
        break;
    }

    if(visokos_count) visokos_num--;  //погрешность на 0 високосный год

    full_day +=365*(year - visokos_num) + 366*visokos_num;  //прибавление дней по годам
}

    //перевод кол-ва дней от 0 года в дни, месяцы и годы
void DataTime::FullDaysToData()
{
    long data_x = full_day;     //создаем переменную для временного хранения данных
    int year_x = 0, month_x = 0;    //переменные для хранения года и месяца
    bool vesokos_count = 0;         //счетчик високосного года

    //определяем год
    for(year_x = 0; data_x > 365; year_x++)
    {
    if((((!(year_x%4))&&(year_x%100))||(!(year_x%400)))&&year_x) //если идет високосный год...
        data_x -=366;
    else
        data_x -=365;   //если не високосный...
    }

    ( (((!(year_x%4))&&(year_x%100))||(!(year_x%400)))&&year_x )
            ? vesokos_count = 1 : vesokos_count = 0;

    //определяем месяц и день
    if((!(vesokos_count)&&(data_x >= 335)) || (data_x > 335))
    {
        month_x = 12;
        (vesokos_count) ? data_x -=335 : data_x -=334;
    }
    else if(((!vesokos_count)&&(data_x >= 305)) || (data_x > 305))
    {
        month_x = 11;
        (vesokos_count) ? data_x -=305 : data_x -=304;
    }
    else if(((!vesokos_count)&&(data_x >= 274)) || (data_x > 274))
    {
        month_x = 10;
        (vesokos_count) ? data_x -=274 : data_x -=273;
    }
    else if(((!vesokos_count)&&(data_x >= 244)) || (data_x > 244))
    {
        month_x = 9;
        (vesokos_count) ? data_x -=244 : data_x -=243;
    }
    else if(((!vesokos_count)&&(data_x >= 213)) || (data_x > 213))
    {
        month_x = 8;
        (vesokos_count) ? data_x -=213 : data_x -=212;
    }
    else if(((!vesokos_count)&&(data_x >= 182)) || (data_x > 182))
    {
        month_x = 7;
        (vesokos_count) ? data_x -=182 : data_x -=181;
    }
    else if(((!vesokos_count)&&(data_x >= 152)) || (data_x > 152))
    {
        month_x = 6;
        (vesokos_count) ? data_x -=152 : data_x -=151;
    }
    else if(((!vesokos_count)&&(data_x >= 121)) || (data_x > 121))
    {
        month_x = 5;
        (vesokos_count) ? data_x -=121 : data_x -=120;
    }
    else if(((!vesokos_count)&&(data_x >= 91)) || (data_x > 91))
    {
        month_x = 4;
        (vesokos_count) ? data_x -=91 : data_x -=90;
    }
    else if(((!vesokos_count)&&(data_x >= 60)) || (data_x > 60))
    {
        month_x = 3;
        (vesokos_count) ? data_x -=60 : data_x -=59;
    }
    else if(data_x > 31)
    {
        month_x = 2;
        data_x -=31;
    }
    else if(data_x > 0)
    {
        month_x = 1;
    }
    else
    { std::cout << "ERROR DATA!"<<std::endl; }

    day = data_x;   //сохраняем результаты вычислений
    month = month_x;
    year = year_x;
}

//////////////////////////////////////////////////////////////////
    //установка даты через строку
void DataTime::WriteData()
{
    DATA_INLINE();       //принимаем строку
    StringToData();     //переводим строку в дату
    DataToFullDays();   //определяем кол-во дней с 0 года
}

    //сохранение даты после ручного ввода через методы (Set)
void DataTime::SaveData()
{
    if(full_day <= 1)       //если меняли дату,
        DataToFullDays();   //то сохраняем кол-во дней с 0 года
    else                    //если меняли кол-во дней с 0 года,
        FullDaysToData();   //то сохраняем дату
    DataToString();         //и строку
}


///////////////////////ОПЕРАТОРЫ/////////////////////////////////
//////////////Перегрузка унарных операторов//////////////////////

    //префиксный инкремент
const DataTime& DataTime::operator ++()
{
    this->SetFullDays()++;
    this->FullDaysToData();
    return *this;
}

    //постфиксный инкремент
const DataTime& DataTime::operator ++(int)
{
    DataTime* tmp = this;
    this->SetFullDays()++;
    this->FullDaysToData();
    return *tmp;
}

    //префиксный денкремент
const DataTime& DataTime::operator --()
{
    this->SetFullDays()--;
    this->FullDaysToData();
    return *this;
}

    //постфиксный денкремент
const DataTime& DataTime::operator --(int)
{
    DataTime* tmp = this;
    this->SetFullDays()--;
    this->FullDaysToData();
    return *tmp;
}

/////////Перегрузка операторов "прибавления/вычитания"////////////

    //прибавляем дни
const DataTime& DataTime::operator +=(const long d)
{
    this->SetFullDays() += d;
    this->FullDaysToData();
    return *this;
}

    //вычитаем дни
const DataTime& DataTime::operator -=(const long d)
{
    this->SetFullDays() -= d;
    this->FullDaysToData();
    return *this;
}

    //складываем дату
const DataTime& DataTime::operator +=(DataTime& d)
{
    this->SetFullDays() += d.SetFullDays();
    this->FullDaysToData();
    return *this;
}

    //вычитаем дату
const DataTime& DataTime::operator -=(DataTime& d)
{
    this->SetFullDays() -= d.SetFullDays();
    this->FullDaysToData();
    return *this;
}

///////////////Перегрузка операторов сравнения/////////////////////

bool DataTime::operator ==(DataTime& d)
{
    return (this->SetFullDays() == d.SetFullDays()) ? true : false;
}

bool DataTime::operator !=(DataTime& d)
{
    return (*this == d) ? false : true;
}

bool DataTime::operator <(DataTime& d)
{
    return (this->SetFullDays() < d.SetFullDays()) ? true : false;
}

bool DataTime::operator <=(DataTime& d)
{
    return ((*this < d) || (*this == d)) ? true : false;
}

bool DataTime::operator >(DataTime& d)
{
    return ((*this == d) || (*this < d)) ? false : true;
}

bool DataTime::operator >=(DataTime& d)
{
    return ((*this > d) || (*this == d)) ? true : false;
}

/////////////Перегрузка операторов сложения/вычитания///////////////

    //перегрузка оператора сложения даты и дней
const DataTime DataTime::operator +(const long d)
{
    return DataTime(this->SetFullDays() + d);
}

    //перегрузка оператора вычитания даты и дня
const DataTime DataTime::operator -(const long d)
{
    return DataTime(this->SetFullDays() - d);
}

    //перегрузка оператора сложения дат
const DataTime DataTime::operator +(DataTime& d)
{
    return DataTime(this->SetFullDays() + d.SetFullDays());
}

    //перегрузка оператора вычитания двух дат
const DataTime DataTime::operator -(DataTime& d)
{
    return DataTime(this->SetFullDays() - d.SetFullDays());
}


//////////////////////////////////////////////////////////////////////


////////////////////////ClockTime///////////////////////////////////
/////////////////////////МЕТОДЫ////////////////////////////////////

    //функия очистки символьного массива
inline void ClockTime::TIME_CLEAN()
{
    for(int i=0;i<TIME_LEN; time_str[i++]=0);   //очистка массива
}

    //функция обработки принятого времени (строки)
inline void ClockTime::TIME_INLINE()
{
    for(;;) //пока не будет соблюден формат введенного времени
    {
        TIME_CLEAN();
        scanf("%s",time_str);
        if(time_str[2]!=':' || time_str[5]!=':' || time_str[8]!=0)
        { std::cout << "ERROR: Print Time(hh.mm.ss)!" <<std::endl; }
        else    //если все принято, то выходим из цикла
        { break; }
    }
}


    //пустой конструктор на время (00:00:00)
ClockTime::ClockTime()
{
    second = 0; minute = 0; hour = 0, full_second = 0;  //установка по умолчанию всех данных
    TimeToString();
}

    //конструктор через строку
ClockTime::ClockTime(char* buff)
{
    strcpy(time_str,buff);  //копируем строку в массив для времени
    TimeToString();
    TimeToFullSecond();
}

    //конструктор через общие секунды
ClockTime::ClockTime(long t) : full_second(t)
{
    FullSecondToTime();
    TimeToString();
}

    //конструктор через часы и минуты (секунды обнулены)
ClockTime::ClockTime(int h, int m) : hour(h), minute(m)
{
    second = 0;
    TimeToFullSecond();
    TimeToString();
}

    //конструктор через часы, минуты и секунды
ClockTime::ClockTime(int h, int m, int s) : hour(h), minute(m), second(s)
{
    TimeToFullSecond();
    TimeToString();
}

    //установка/получение кол-ва секунд в данной минуте
int& ClockTime::SetSecond()
{
    return second;
}

    //установка/получение кол-ва минут в данном часе
int& ClockTime::SetMinute()
{
    return minute;
}

    //установка/получение кол-ва часов
int& ClockTime::SetHour()
{
    return hour;
}

    //установка/получение кол-ва общих секунд
long& ClockTime::SetFullSecond()
{
    TimeToFullSecond();
    return full_second;
}

    //вывод времени в формате (hh:mm:ss)
char* ClockTime::DisplayTime()
{
    TimeToString();
    return time_str;
}

/////////////////////ФУНКЦИИ ПРИВЕДЕНИЯ/////////////////////////

    //перевод строки в часы, минуты и секунды
void ClockTime::StringToTime()
{
    hour = (time_str[0]-'0')*10 + (time_str[1]-'0');
    minute = (time_str[3]-'0')*10 + (time_str[4]-'0');
    second = (time_str[6]-'0')*10 + (time_str[7]-'0');
}

    //перевод времени в строку
void ClockTime::TimeToString()
{
    TIME_CLEAN();
    time_str[2]=time_str[5]=':';
    time_str[0] = hour/10 + '0';
    time_str[1] = (hour%10) + '0';
    time_str[3] = minute/10 + '0';
    time_str[4] = (minute%10) + '0';
    time_str[6] = second/10 + '0';
    time_str[7] = (second%10) + '0';
}

    //перевод времени в общие секунды
void ClockTime::TimeToFullSecond()
{
    full_second = second + minute*60 + hour*3600;
}

    //перевод общих секунд в часы, минуты и секунды
void ClockTime::FullSecondToTime()
{
    long time_x = full_second;      //сохраняем данные об общих секундах
    int hour_x = 0, minute_x = 0;   //переменные для хранения часов и минут
    //определяем кол-во часов по общим секундам
    for(hour_x = 0; time_x >= 3600; hour_x++)
    { time_x -= 3600; if(hour_x>=24) hour_x = 0; }
    //определяем кол-во минут по оставшимся общим секундам
    for(minute_x = 0; time_x >=60; minute_x++)
    { time_x -=60; }

    second = time_x;
    minute = minute_x;
    hour = hour_x;
}

////////////////////////////////////////////////////////////////

    //установка времени через строку
void ClockTime::WriteTime()
{
    TIME_INLINE();
    StringToTime();
    TimeToFullSecond();
}

    //сохранение времени после ручного ввода через методы (Set)
void ClockTime::SaveTime()
{
    if(full_second <= 0)    //если меняли время,
        TimeToFullSecond(); //то сохраняем кол-во общих
    else                    //если меняли кол-во общих секунд
        FullSecondToTime(); //то сохраняем время
    TimeToString();         //и строку
}


///////////////////////ОПЕРАТОРЫ/////////////////////////////////
//////////////Перегрузка унарных операторов//////////////////////

    //префиксный инкремент
const ClockTime& ClockTime::operator ++()
{
    this->SetFullSecond()++;
    this->FullSecondToTime();
    return *this;
}

    //постфиксный инкремент
const ClockTime& ClockTime::operator ++(int)
{
    ClockTime* tmp = this;
    this->SetFullSecond()++;
    this->FullSecondToTime();
    return *tmp;
}

    //префиксный денкремент
const ClockTime& ClockTime::operator --()
{
    this->SetFullSecond()--;
    this->FullSecondToTime();
    return *this;
}

    //постфиксный денкремент
const ClockTime& ClockTime::operator --(int)
{
    ClockTime* tmp = this;
    this->SetFullSecond()--;
    this->FullSecondToTime();
    return *tmp;
}

/////////Перегрузка операторов "прибавления/вычитания"////////////

    //прибавляем секунды
const ClockTime& ClockTime::operator +=(const long t)
{
    this->SetFullSecond() += t;
    this->FullSecondToTime();
    return *this;
}

    //вычитаем секунды
const ClockTime& ClockTime::operator -=(const long t)
{
    this->SetFullSecond() -= t;
    this->FullSecondToTime();
    return *this;
}

    //складываем время
const ClockTime& ClockTime::operator +=(ClockTime& t)
{
    this->SetFullSecond() += t.SetFullSecond();
    this->FullSecondToTime();
    return *this;
}

    //вычитаем время
const ClockTime& ClockTime::operator -=(ClockTime& t)
{
    this->SetFullSecond() -= t.SetFullSecond();
    this->FullSecondToTime();
    return *this;
}

///////////////Перегрузка операторов сравнения/////////////////////

bool ClockTime::operator ==(ClockTime& t)
{
    return (this->SetFullSecond() == t.SetFullSecond()) ? true : false;
}

bool ClockTime::operator !=(ClockTime& t)
{
    return (*this == t) ? false : true;
}

bool ClockTime::operator <(ClockTime& t)
{
    return (this->SetFullSecond() < t.SetFullSecond()) ? true : false;
}

bool ClockTime::operator <=(ClockTime& t)
{
    return ((*this < t) || (*this == t)) ? true : false;
}

bool ClockTime::operator >(ClockTime& t)
{
    return ((*this == t) || (*this < t)) ? false : true;
}

bool ClockTime::operator >=(ClockTime& t)
{
    return ((*this > t) || (*this == t)) ? true : false;
}

/////////////Перегрузка операторов сложения/вычитания///////////////

    //перегрузка оператора сложения времени и секунд
const ClockTime ClockTime::operator +(const long t)
{
    return ClockTime(this->SetFullSecond() + t);
}

    //перегрузка оператора вычитания времени и секунд
const ClockTime ClockTime::operator -(const long t)
{
    return ClockTime(this->SetFullSecond() - t);
}

    //перегрузка оператора сложения двух времен
const ClockTime ClockTime::operator +(ClockTime& t)
{
    return ClockTime(this->SetFullSecond() + t.SetFullSecond());
}

    //перегрузка оператора вычитания двух времен
const ClockTime ClockTime::operator -(ClockTime& t)
{
    return ClockTime(this->SetFullSecond() - t.SetFullSecond());
}


////////////////////////////////////////////////////////////////////


//////////////////////////AllDataTime///////////////////////////////
////////////////////////////МЕТОДЫ/////////////////////////////////

    //функия очистки символьного массива
inline void AllDataTime::ALLDATA_CLEAN()
{
    DATA_CLEAN();            //очистка массива даты
    TIME_CLEAN();            //очистка массива времени
    for(int i=0;i<ALLDATA_LEN; alldata_str[i++]=0); //очистка массива полного времени
}

    //функция обработки принятой полной даты (строки)
inline void AllDataTime::STR_INLINE()
{
    for(;;) //пока не будет соблюден формат введенного полного времени
    {
        ALLDATA_CLEAN();
        scanf("%s",alldata_str);
        if(alldata_str[2]!=':' || alldata_str[5]!=':' || alldata_str[8]==0 ||
                alldata_str[11]!='.' || alldata_str[14]!='.' || alldata_str[19]!=0)
        { std::cout << "ERROR: Print Full Time(hh:mm:ss/dd.mm.yyyy)!" <<std::endl; }
        else    //если все принято, то выходим из цикла
        { break; }
    }
}


    //пустой конструктор на полную дату (00:00:00/01.01.0000)
AllDataTime::AllDataTime() : DataTime(), ClockTime()
{ AllDataToString(); }

    //конструктор через время и дату
AllDataTime::AllDataTime(int h, int mi, int s, int d, int mo, int y) :
    DataTime(d, mo, y), ClockTime(h, mi, s)
{ AllDataToString(); }

    //конструктор через дату (00:00:00/dd.mm.yyyy)
AllDataTime::AllDataTime(int d, int mo, int y) :
    DataTime(d, mo, y), ClockTime()
{ AllDataToString(); }

    //конструктор через общие параметры (t - секунды, d - дни)
AllDataTime::AllDataTime(long t, long d) :
    ClockTime(t), DataTime(d)
{ FullParamToAllData(); AllDataToString();}

    //вывод полной даты в формате (hh:mm:ss/dd.mm.yyyy)
char* AllDataTime::DisplayAllData()
{
    AllDataToString();
    return alldata_str;
}

/////////////////////ФУНКЦИИ ПРИВЕДЕНИЯ/////////////////////////

    //перевод строки в дату и время (полную дату)
void AllDataTime::StringToAllData()
{
    strncpy(time_str, alldata_str, 9);
    time_str[8] = 0;
    strcpy(data_str, &alldata_str[9]);
    data_str[10] = 0;

    StringToTime();
    StringToData();
}

    //перевод даты и времени в строку
void AllDataTime::AllDataToString()
{
    ALLDATA_CLEAN();
    TimeToString();
    DataToString();
    strcat(alldata_str, time_str);
    strcat(alldata_str,"/");
    strcat(alldata_str, data_str);
}

    //перевод полной даты в обшие секунды и дни с 0 года
void AllDataTime::AllDataToFullParam()
{
    DataToFullDays();
    TimeToFullSecond();
}

    //перевод общих параметров в полную дату
void AllDataTime::FullParamToAllData()
{
    FullSecondToTime();
    FullDaysToData();
}

    //переопределение метода перевода общих секунд во время
void AllDataTime::FullSecondToTime()
{
    long time_x = full_second;
    int day_x = 0, hour_x = 0, minute_x = 0;
    //основное изменение метода для согласования времени и даты при вычитании
    while(time_x < 0)
    {
        time_x += 86400; day_x--;
    }
    //и сложении полных дат
    for(hour_x = 0; time_x >= 3600; hour_x++)
    { time_x -= 3600; if(hour_x>23){hour_x = 0; day_x++;} }

    for(minute_x = 0; time_x >=60; minute_x++)
    { time_x -=60; }

    second = time_x;
    minute = minute_x;
    hour = hour_x;
    full_day +=day_x;
}


///////////////////////////////////////////////////////////////

    //установка полной даты через строку
void AllDataTime::WriteAllData()
{
    STR_INLINE();
    StringToAllData();
    DataToFullDays();
    TimeToFullSecond();
}

    //сохранение полной даты после ручного ввода через методы (Set)
void AllDataTime::SaveAllData()
{
    SaveData();
    SaveTime();
    AllDataToString();
}


///////////////////////ОПЕРАТОРЫ/////////////////////////////////
//////////////Перегрузка унарных операторов//////////////////////

    //префиксный инкремент
const AllDataTime& AllDataTime::operator ++()
{
    this->SetFullSecond()++;
    this->FullParamToAllData();
    return *this;
}

    //постфиксный инкремент
const AllDataTime& AllDataTime::operator ++(int)
{
    AllDataTime* tmp = this;
    this->SetFullSecond()++;
    this->FullParamToAllData();
    return *tmp;
}

    //префиксный денкремент
const AllDataTime& AllDataTime::operator --()
{
    this->SetFullSecond()--;
    this->FullParamToAllData();
    return *this;
}

    //постфиксный денкремент
const AllDataTime& AllDataTime::operator --(int)
{
    AllDataTime* tmp = this;
    this->SetFullSecond()--;
    this->FullParamToAllData();
    return *tmp;
}


/////////Перегрузка операторов "прибавления/вычитания"////////////
    //прибавляем секунды
const AllDataTime& AllDataTime::operator +=(const long dt)
{
    this->SetFullSecond() += dt;
    this->FullParamToAllData();
    return *this;
}

    //вычитаем секунды
const AllDataTime& AllDataTime::operator -=(const long dt)
{
    this->SetFullSecond() -= dt;
    this->FullParamToAllData();
    return *this;
}

    //складываем время
const AllDataTime& AllDataTime::operator +=(DataTime& dt)
{
    this->SetFullDays() += dt.SetFullDays();
    this->FullParamToAllData();
    return *this;
}

    //вычитаем время
const AllDataTime& AllDataTime::operator -=(DataTime& dt)
{
    this->SetFullDays() -= dt.SetFullDays();
    this->FullParamToAllData();
    return *this;
}

    //складываем дату
const AllDataTime& AllDataTime::operator +=(ClockTime& dt)
{
    this->SetFullSecond() += dt.SetFullSecond();
    this->FullParamToAllData();
    return *this;
}

    //вычитаем дату
const AllDataTime& AllDataTime::operator -=(ClockTime& dt)
{
    this->SetFullSecond() -= dt.SetFullSecond();
    this->FullParamToAllData();
    return *this;
}

    //складываем полную дату
const AllDataTime& AllDataTime::operator +=(AllDataTime& dt)
{
    this->SetFullDays() += dt.SetFullDays();
    this->SetFullSecond() += dt.SetFullSecond();
    this->FullParamToAllData();
    return *this;
}

    //вычитаем полную дату
const AllDataTime& AllDataTime::operator -=(AllDataTime& dt)
{
    this->SetFullDays() -= dt.SetFullDays();
    this->SetFullSecond() -= dt.SetFullSecond();
    this->FullParamToAllData();
    return *this;
}


///////////////Перегрузка операторов сравнения/////////////////////

bool AllDataTime::operator ==(AllDataTime& dt)
{
    return ((this->SetFullSecond() == dt.SetFullSecond()) &&
            (this->SetFullDays() == dt.SetFullDays())) ? true : false;
}

bool AllDataTime::operator !=(AllDataTime& dt)
{
    return (*this == dt) ? false : true;
}

bool AllDataTime::operator <(AllDataTime& dt)
{
    if(this->SetFullDays() < dt.SetFullDays())
        return true;
    else if((this->SetFullDays() == dt.SetFullDays()) &&
            (this->SetFullSecond() < dt.SetFullSecond()))
    { return true; }
    else
    { return false; }
}

bool AllDataTime::operator <=(AllDataTime& dt)
{
    return ((*this < dt) || (*this == dt)) ? true : false;
}

bool AllDataTime::operator >(AllDataTime& dt)
{
    return ((*this == dt) || (*this < dt)) ? false : true;
}

bool AllDataTime::operator >=(AllDataTime& dt)
{
    return ((*this > dt) || (*this == dt)) ? true : false;
}


/////////////Перегрузка операторов сложения/вычитания///////////////

    //перегрузка оператора сложения полной даты и секунд
const AllDataTime AllDataTime::operator +(const long dt)
{
    return AllDataTime(this->SetFullSecond() + dt, this->SetFullDays());
}

    //перегрузка оператора вычитания полной даты и секунд
const AllDataTime AllDataTime::operator -(const long dt)
{
    return AllDataTime(this->SetFullSecond() - dt, this->SetFullDays());
}

    //перегрузка оператора сложения полной даты и даты
const AllDataTime AllDataTime::operator +(DataTime& dt)
{
    return AllDataTime(this->SetFullSecond(), this->SetFullDays() + dt.SetFullDays());
}

    //перегрузка оператора вычитания полной даты и даты
const AllDataTime AllDataTime::operator -(DataTime& dt)
{
    return AllDataTime(this->SetFullSecond(), this->SetFullDays() - dt.SetFullDays());
}

    //перегрузка оператора сложения полной даты и времени
const AllDataTime AllDataTime::operator +(ClockTime& dt)
{
    return AllDataTime(this->SetFullSecond() + dt.SetFullSecond(), this->SetFullDays());
}

    //перегрузка оператора вычитания полной даты и времени
const AllDataTime AllDataTime::operator -(ClockTime& dt)
{
    return AllDataTime(this->SetFullSecond() - dt.SetFullSecond(), this->SetFullDays());
}

    //перегрузка оператора сложения двух полных дат
const AllDataTime AllDataTime::operator +(AllDataTime& dt)
{
    return AllDataTime(this->SetFullSecond() + dt.SetFullSecond(),
                       this->SetFullDays() + dt.SetFullDays());
}

    //перегрузка оператора вычитания двух полных дат
const AllDataTime AllDataTime::operator -(AllDataTime& dt)
{
    return AllDataTime(this->SetFullSecond() - dt.SetFullSecond(),
                       this->SetFullDays() - dt.SetFullDays());
}


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
