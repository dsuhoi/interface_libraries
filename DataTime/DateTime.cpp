//Created by DSuhoi (2020).//
#include <iostream>
#include <cstring>
#include "DateTime.h"


//////////////////////DateTime//////////////////////////////
///////////////////////МЕТОДЫ//////////////////////////////

    //пустой конструктор на дату (00.00.0000)
DateTime::DateTime()
{
    day = 0; month = 0; year = 0; full_day = 0; //установка по умолчанию всех данных
}

    //конструктор через кол-во дней от 0 года
DateTime::DateTime(long l) : full_day(l)
{
    if(full_day < 0) full_day += 365;
    FullDaysToDate();
}

    //конструктор через ручную утсановку даты (день, месяц, год)
DateTime::DateTime(int d, int m, int y) : day(d), month(m), year(y)
{
    if(!DateToFullDays()) *this = DateTime();
}

    //конструктор через строку
DateTime::DateTime(char *buff)
{
    if(!StringToDate(buff)) *this = DateTime();
    DateToFullDays();
}

    //установка/получение кол-ва дней в данном месяце
int& DateTime::SetDay()
{
    return day;
}

    //установка/получение кол-ва месяцев в данном году
int& DateTime::SetMonth()
{
    return month;
}

    //установка/получение кол-ва лет
int& DateTime::SetYear()
{
    return year;
}

    //установка/получение кол-ва дней от 0 года
long& DateTime::SetFullDays()
{
    return full_day;
}

    //вывод даты в формате dd.mm.yyyy
char* DateTime::DisplayDate()
{
    static char date_str[11];
    for(int i = 0; i < 11; i++) date_str[i] = 0;
    date_str[2]=date_str[5]='.';
    date_str[0] = day/10 + '0';
    date_str[1] = (day%10) + '0';
    date_str[3] = month/10 + '0';
    date_str[4] = (month%10) + '0';
    date_str[6] = year/1000 + '0';
    date_str[7] = (year/100 - (year/1000)*10) + '0';
    if(year>99)
    {
    date_str[8] = (year/10 - (year/100)*10) + '0';
    date_str[9] = (year - (year/10)*10) + '0';
    }
    else
    {
    date_str[8] = year/10 + '0';
    date_str[9] = (year - (year/10)*10) + '0';
    }
    date_str[10] = 0;

    return date_str;
}

/////////////////////ФУНКЦИИ ПРИВЕДЕНИЯ///////////////////////////
    //проверка полученной даты
bool DateTime::CheckDate()
{
    if(day < 1) return 0;
    if(year < 0 || year > 9999) return 0;

        if (month == 4 || month == 6 || month == 9 || month == 11)
        { if (day > 30) return 0; }
        else if (month == 2)
        {
            if(((!(year%4)&&year%100) || !(year%400))&&year)
            { if(day > 29) return 0; }
            else
            { if(day > 28) return 0; }
        }
        else if ((month > 0)&&(month < 13))
        { if(day > 31) return 0; }
        else
        { return 0; }

        return 1;
}

    //перевод строки в дни, месяцы и годы
bool DateTime::StringToDate(char* date_str)
{
    day = (date_str[0]-'0')*10 + (date_str[1]-'0');
    month = (date_str[3]-'0')*10 + (date_str[4]-'0');
    year = (date_str[6]-'0')*1000 + (date_str[7]-'0')*100 + (date_str[8]-'0')*10 + (date_str[9]-'0');

    return CheckDate();
}

    //перевод даты в кол-во дней от 0 года
bool DateTime::DateToFullDays()
{
    full_day = 0;   //сбрасываем кол-во дней
    bool visokos_count = ((!(year%4)&&year%100) || !(year%400))&&year; //определение високосного года
    int visokos_num = year/4 - (year/100 - year/400); //кол-во високосных лет

    switch (month)
    {               //определение кол-ва дней через месяц
    case 0:
        full_day = 0; day = 0;
        break;
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
    default: std::cout << "ERROR: DATE!" << std::endl; //если как-то ввели неправильный месяц...
        break;
    }

    if(visokos_count) visokos_num--;  //погрешность на 0 високосный год

    full_day +=365*(year - visokos_num) + 366*visokos_num;  //прибавление дней по годам

    return CheckDate();
}

    //перевод кол-ва дней от 0 года в дни, месяцы и годы
void DateTime::FullDaysToDate()
{
    long data_x = full_day;         //создаем переменную для временного хранения данных
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

    ( ((!(year_x%4)&&year_x%100)||!(year_x%400))&&year_x )
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
    else if(data_x == 0)
    {
        month_x = 0; year_x = 0;
    }
    else
    { std::cout << "ERROR: DATA!"<<std::endl; }

    day = data_x;   //сохраняем результаты вычислений
    month = month_x;
    year = year_x;
}

//////////////////////////////////////////////////////////////////  

    //установка даты через ввод
void DateTime::WriteDate()
{
    char* date_str = new char[11];
    for(;;) //пока не будет соблюден формат введенной даты
    {
        scanf("%s",date_str);
        if(!(StringToDate(date_str) && date_str[2]=='.' && date_str[5]=='.' && date_str[10]==0))
        { std::cout << "ERROR: Print Date(dd.mm.yyyy)!" <<std::endl; }
        else    //если все принято, то выходим из цикла
        { break; }
    }
    DateToFullDays();   //определяем кол-во дней с 0 года
    delete [] date_str;
}

    //сохранение даты после ручного ввода через методы (Set)
void DateTime::SaveDate()
{        //если меняли дату,
    if(full_day <= 1)
    {   //то сохраняем кол-во дней с 0 года
        if(!DateToFullDays()) *this = DateTime();
    }
    else FullDaysToDate();   //сохраняем дату
}

///////////////////////ОПЕРАТОРЫ/////////////////////////////////
/////////////Перегрузка операторов присваивания//////////////////
    //присвоение даты через строку
const DateTime& DateTime::operator =(char* buff)
{
    *this = DateTime(buff);
    return *this;
}

//////////////Перегрузка унарных операторов//////////////////////
    //префиксный инкремент
const DateTime& DateTime::operator ++()
{
    this->SetFullDays()++;
    this->FullDaysToDate();
    return *this;
}

    //постфиксный инкремент
const DateTime& DateTime::operator ++(int)
{
    DateTime* tmp = this;
    this->SetFullDays()++;
    this->FullDaysToDate();
    return *tmp;
}

    //префиксный денкремент
const DateTime& DateTime::operator --()
{
    this->SetFullDays()--;
    this->FullDaysToDate();
    return *this;
}

    //постфиксный денкремент
const DateTime& DateTime::operator --(int)
{
    DateTime* tmp = this;
    this->SetFullDays()--;
    this->FullDaysToDate();
    return *tmp;
}

/////////Перегрузка операторов "прибавления/вычитания"////////////
    //прибавляем дни
const DateTime& DateTime::operator +=(const long d)
{
    this->SetFullDays() += d;
    this->FullDaysToDate();
    return *this;
}

    //вычитаем дни
const DateTime& DateTime::operator -=(const long d)
{
    this->SetFullDays() -= d;
    this->FullDaysToDate();
    return *this;
}

    //складываем дату
const DateTime& DateTime::operator +=(DateTime& d)
{
    this->SetFullDays() += d.SetFullDays();
    this->FullDaysToDate();
    return *this;
}

    //вычитаем дату
const DateTime& DateTime::operator -=(DateTime& d)
{
    this->SetFullDays() -= d.SetFullDays();
    this->FullDaysToDate();
    return *this;
}

///////////////Перегрузка операторов сравнения/////////////////////

bool DateTime::operator ==(DateTime& d)
{
    return (this->SetFullDays() == d.SetFullDays()) ? true : false;
}

bool DateTime::operator !=(DateTime& d)
{
    return (*this == d) ? false : true;
}

bool DateTime::operator <(DateTime& d)
{
    return (this->SetFullDays() < d.SetFullDays()) ? true : false;
}

bool DateTime::operator <=(DateTime& d)
{
    return ((*this < d) || (*this == d)) ? true : false;
}

bool DateTime::operator >(DateTime& d)
{
    return ((*this == d) || (*this < d)) ? false : true;
}

bool DateTime::operator >=(DateTime& d)
{
    return ((*this > d) || (*this == d)) ? true : false;
}

/////////////Перегрузка операторов сложения/вычитания///////////////
    //перегрузка оператора сложения даты и дней
const DateTime DateTime::operator +(const long d)
{
    return DateTime(this->SetFullDays() + d);
}

    //перегрузка оператора вычитания даты и дня
const DateTime DateTime::operator -(const long d)
{
    return DateTime(this->SetFullDays() - d);
}

    //перегрузка оператора сложения дат
const DateTime DateTime::operator +(DateTime& d)
{
    return DateTime(this->SetFullDays() + d.SetFullDays());
}

    //перегрузка оператора вычитания двух дат
const DateTime DateTime::operator -(DateTime& d)
{
    return DateTime(this->SetFullDays() - d.SetFullDays());
}

//////////////////Перегрузка операторов ввода/вывода///////////////////////
    //перегрузка оператора вывода
std::ostream& operator <<(std::ostream& out, DateTime& d)
{
    out << d.DisplayDate();
    return out;
}

    //перегрузка оператора ввода
std::istream& operator >>(std::istream& in, DateTime& d)
{
    char* buff = new char[11];
    in >> buff;
    d = DateTime(buff);
    if(!in)
    { d = DateTime(); }
    delete [] buff;
    return in;
}

//////////////////////////////////////////////////////////////////////



////////////////////////ClockTime///////////////////////////////////
/////////////////////////МЕТОДЫ////////////////////////////////////

    //пустой конструктор на время (00:00:00)
ClockTime::ClockTime()
{
    second = 0; minute = 0; hour = 0, full_second = 0;  //установка по умолчанию всех данных
}

    //конструктор через строку
ClockTime::ClockTime(char* buff)
{
    if(!StringToTime(buff)) *this = ClockTime();
    TimeToFullSecond();
}

    //конструктор через общие секунды
ClockTime::ClockTime(long t) : full_second(t)
{
    FullSecondToTime();
}

    //конструктор через часы и минуты (секунды обнулены)
ClockTime::ClockTime(int h, int m) : hour(h), minute(m)
{
    second = 0;
    if(!TimeToFullSecond()) *this = ClockTime();
}

    //конструктор через часы, минуты и секунды
ClockTime::ClockTime(int h, int m, int s) : hour(h), minute(m), second(s)
{
    if(!TimeToFullSecond()) *this = ClockTime();
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
    return full_second;
}

    //вывод времени в формате (hh:mm:ss)
char* ClockTime::DisplayTime()
{
    static char time_str[9];
    for(int i = 0; i < 9; i++) time_str[i] = 0;
    time_str[2]=time_str[5]=':';
    time_str[0] = hour/10 + '0';
    time_str[1] = (hour%10) + '0';
    time_str[3] = minute/10 + '0';
    time_str[4] = (minute%10) + '0';
    time_str[6] = second/10 + '0';
    time_str[7] = (second%10) + '0';
    time_str[8] = 0;

    return time_str;
}

/////////////////////ФУНКЦИИ ПРИВЕДЕНИЯ/////////////////////////
    //проверка полученного времени
bool ClockTime::CheckTime()
{
    if(second < 0 || second > 59) return 0;
    if(minute < 0 || minute > 59) return 0;
    if(hour < 0 || hour > 23) return 0;

    return 1;
}

    //перевод строки в часы, минуты и секунды
bool ClockTime::StringToTime(char* time_str)
{
    hour = (time_str[0]-'0')*10 + (time_str[1]-'0');
    minute = (time_str[3]-'0')*10 + (time_str[4]-'0');
    second = (time_str[6]-'0')*10 + (time_str[7]-'0');

    return CheckTime();
}

    //перевод времени в общие секунды
bool ClockTime::TimeToFullSecond()
{
    full_second = second + minute*60 + hour*3600;
    return CheckTime();
}

    //перевод общих секунд в часы, минуты и секунды
int ClockTime::FullSecondToTime()
{
    long time_x = 0;    //переменная для хранения данных об общих секундах
    int hour_x = 0, minute_x = 0, day_x = 0;   //переменные для хранения часов, минут и дней
    //определяем кол-во дней при вычитании дат
    while(full_second < 0)
    {
        full_second += 86400; day_x--;
    }
    time_x = full_second;
    //определяем кол-во часов по общим секундам
    for(hour_x = 0; time_x >= 3600; hour_x++)
    { time_x -= 3600; if(hour_x>23){hour_x = 0; day_x++;} }
    //определяем кол-во минут по оставшимся общим секундам
    for(minute_x = 0; time_x >=60; minute_x++)
    { time_x -=60; }

    second = time_x;
    minute = minute_x;
    hour = hour_x;

    return day_x;
}

////////////////////////////////////////////////////////////////

    //установка времени через строку
void ClockTime::WriteTime()
{
    char* time_str = new char[9];
    for(;;) //пока не будет соблюден формат введенного времени
    {
        scanf("%s",time_str);
        if(!(StringToTime(time_str) && time_str[2]==':' &&
             time_str[5]==':' && time_str[8]==0))
        { std::cout << "ERROR: Print Time(hh.mm.ss)!" <<std::endl; }
        else    //если все принято, то выходим из цикла
        { break; }
    }

    TimeToFullSecond();
    delete [] time_str;
}

    //сохранение времени после ручного ввода через методы (Set)
void ClockTime::SaveTime()
{       //если меняли время,
    if(full_second <= 0)
    {       //то сохраняем кол-во общих
        if(!(TimeToFullSecond()))
        { second = 0; minute = 0; hour = 0; full_second = 0; }
    }
    else FullSecondToTime(); //сохраняем время
}


///////////////////////ОПЕРАТОРЫ/////////////////////////////////
/////////////Перегрузка операторов присваивания//////////////////
    //присвоение времени через строку
const ClockTime& ClockTime::operator =(char* buff)
{
    *this = ClockTime(buff);
    return *this;
}

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

//////////////////Перегрузка операторов ввода/вывода///////////////////////
    //перегрузка оператора вывода
std::ostream& operator<<(std::ostream& out, ClockTime& t)
{
    out << t.DisplayTime();
    return out;
}

    //перегрузка оператора ввода
std::istream& operator >>(std::istream& in, ClockTime& t)
{
    char* buff = new char[9];
    in >> buff;
    t = ClockTime(buff);
    if(!in)
    { t = ClockTime(); }
    delete [] buff;
    return in;
}

////////////////////////////////////////////////////////////////////



//////////////////////////AllDateTime///////////////////////////////
////////////////////////////МЕТОДЫ/////////////////////////////////

    //пустой конструктор на полную дату (00:00:00/01.01.0000)
AllDateTime::AllDateTime() : DateTime(), ClockTime()
{}

    //конструктор через строку
AllDateTime::AllDateTime(char* buff)
{
    if(!StringToAllDate(buff)) *this = AllDateTime();
    AllDateToFullParam();
}

    //конструктор через время и дату
AllDateTime::AllDateTime(int h, int mi, int s, int d, int mo, int y) :
    DateTime(d, mo, y), ClockTime(h, mi, s)
{}

    //конструктор через дату (00:00:00/dd.mm.yyyy)
AllDateTime::AllDateTime(int d, int mo, int y) :
    DateTime(d, mo, y), ClockTime()
{}

    //конструктор через общие параметры (t - секунды, d - дни)
AllDateTime::AllDateTime(long t, long d) : DateTime(d)
{ full_second = t; FullParamToAllDate(); }

    //вывод полной даты в формате (hh:mm:ss/dd.mm.yyyy)
char* AllDateTime::DisplayAllDate()
{
    static char alldate_str[20];
    for(int i = 0; i < 20; i++) alldate_str[i] = 0;
    strcat(alldate_str, DisplayTime());
    strcat(alldate_str,"/");
    strcat(alldate_str, DisplayDate());
    alldate_str[19] = 0;

    return alldate_str;
}

/////////////////////ФУНКЦИИ ПРИВЕДЕНИЯ/////////////////////////
    //проверка полученной полной даты
bool AllDateTime::CheckAllDate()
{
    if(!CheckDate()) return 0;
    if(!CheckTime()) return 0;

    return 1;
}

    //перевод строки в дату и время (полную дату)
bool AllDateTime::StringToAllDate(char* alldate_str)
{
    char* time_str = new char[9];
    char* date_str = new char[11];

    if(alldate_str[2] == ':' && alldate_str[5] == ':' && alldate_str[8] == 0)
    {
        strncpy(time_str, alldate_str, 9);
        time_str[8] = 0;
        StringToTime(time_str);
        return CheckTime();
    }
    else if(alldate_str[2] == '.' && alldate_str[5] == '.' && alldate_str[10] == 0)
    {
        strncpy(date_str, alldate_str, 11);
        date_str[10] = 0;
        StringToDate(date_str);
    }
    else
    {
        strncpy(time_str, alldate_str, 9);
        time_str[8] = 0;
        strcpy(date_str, &alldate_str[9]);
        date_str[10] = 0;
        StringToTime(time_str);
        StringToDate(date_str);
    }

    delete [] time_str;
    delete [] date_str;

    return CheckAllDate();
}

    //перевод полной даты в обшие секунды и дни с 0 года
bool AllDateTime::AllDateToFullParam()
{
    TimeToFullSecond();
    DateToFullDays();

    return CheckAllDate();
}

    //перевод общих параметров в полную дату
void AllDateTime::FullParamToAllDate()
{
    full_day += FullSecondToTime();
    FullDaysToDate();
}

///////////////////////////////////////////////////////////////

    //установка полной даты через строку
void AllDateTime::WriteAllDate()
{
    char* alldate_str = new char[20];
    for(;;) //пока не будет соблюден формат введенного полного времени
    {
        scanf("%s",alldate_str);
     if(!(StringToAllDate(alldate_str) && alldate_str[2]==':' && alldate_str[5]==':' &&
          alldate_str[11]=='.' && alldate_str[14]=='.' && alldate_str[19]==0))
        { std::cout << "ERROR: Print Full Date(hh:mm:ss/dd.mm.yyyy)!" <<std::endl; }
        else    //если все принято, то выходим из цикла
        { break; }
    }

    AllDateToFullParam();
    delete [] alldate_str;
}

    //сохранение полной даты после ручного ввода через методы (Set)
void AllDateTime::SaveAllDate()
{
    SaveDate();
    SaveTime();
}


///////////////////////ОПЕРАТОРЫ/////////////////////////////////
/////////////Перегрузка операторов присваивания//////////////////
    //возвращение даты в формате объекта DateTime
const DateTime AllDateTime::GetDateTime()
{
    return DateTime(full_day);
}

    //возвращение времени в формате объекта ClockTime
const ClockTime AllDateTime::GetClockTime()
{
    return ClockTime(full_second);
}

    //присвоение времени
const AllDateTime& AllDateTime::operator =(ClockTime& t)
{
    this->SetFullSecond() = t.SetFullSecond();
    this->FullSecondToTime();
    return *this;
}

    //присвоение даты
const AllDateTime& AllDateTime::operator =(DateTime& d)
{
    this->SetFullDays() = d.SetFullDays();
    this->FullDaysToDate();
    return *this;
}

    //присвоение полной даты через строку
const AllDateTime& AllDateTime::operator =(char* buff)
{
    *this = AllDateTime(buff);
    return *this;
}

//////////////Перегрузка унарных операторов//////////////////////
    //префиксный инкремент
const AllDateTime& AllDateTime::operator ++()
{
    this->SetFullSecond()++;
    this->FullParamToAllDate();
    return *this;
}

    //постфиксный инкремент
const AllDateTime& AllDateTime::operator ++(int)
{
    AllDateTime* tmp = this;
    this->SetFullSecond()++;
    this->FullParamToAllDate();
    return *tmp;
}

    //префиксный денкремент
const AllDateTime& AllDateTime::operator --()
{
    this->SetFullSecond()--;
    this->FullParamToAllDate();
    return *this;
}

    //постфиксный денкремент
const AllDateTime& AllDateTime::operator --(int)
{
    AllDateTime* tmp = this;
    this->SetFullSecond()--;
    this->FullParamToAllDate();
    return *tmp;
}


/////////Перегрузка операторов "прибавления/вычитания"////////////
    //прибавляем секунды
const AllDateTime& AllDateTime::operator +=(const long dt)
{
    this->SetFullSecond() += dt;
    this->FullParamToAllDate();
    return *this;
}

    //вычитаем секунды
const AllDateTime& AllDateTime::operator -=(const long dt)
{
    this->SetFullSecond() -= dt;
    this->FullParamToAllDate();
    return *this;
}

    //складываем время
const AllDateTime& AllDateTime::operator +=(DateTime& dt)
{
    this->SetFullDays() += dt.SetFullDays();
    this->FullParamToAllDate();
    return *this;
}

    //вычитаем время
const AllDateTime& AllDateTime::operator -=(DateTime& dt)
{
    this->SetFullDays() -= dt.SetFullDays();
    this->FullParamToAllDate();
    return *this;
}

    //складываем дату
const AllDateTime& AllDateTime::operator +=(ClockTime& dt)
{
    this->SetFullSecond() += dt.SetFullSecond();
    this->FullParamToAllDate();
    return *this;
}

    //вычитаем дату
const AllDateTime& AllDateTime::operator -=(ClockTime& dt)
{
    this->SetFullSecond() -= dt.SetFullSecond();
    this->FullParamToAllDate();
    return *this;
}

    //складываем полную дату
const AllDateTime& AllDateTime::operator +=(AllDateTime& dt)
{
    this->SetFullDays() += dt.SetFullDays();
    this->SetFullSecond() += dt.SetFullSecond();
    this->FullParamToAllDate();
    return *this;
}

    //вычитаем полную дату
const AllDateTime& AllDateTime::operator -=(AllDateTime& dt)
{
    this->SetFullDays() -= dt.SetFullDays();
    this->SetFullSecond() -= dt.SetFullSecond();
    this->FullParamToAllDate();
    return *this;
}


///////////////Перегрузка операторов сравнения/////////////////////

bool AllDateTime::operator ==(AllDateTime& dt)
{
    return ((this->SetFullSecond() == dt.SetFullSecond()) &&
            (this->SetFullDays() == dt.SetFullDays())) ? true : false;
}

bool AllDateTime::operator !=(AllDateTime& dt)
{
    return (*this == dt) ? false : true;
}

bool AllDateTime::operator <(AllDateTime& dt)
{
    if(this->SetFullDays() < dt.SetFullDays())
        return true;
    else if((this->SetFullDays() == dt.SetFullDays()) &&
            (this->SetFullSecond() < dt.SetFullSecond()))
    { return true; }
    else
    { return false; }
}

bool AllDateTime::operator <=(AllDateTime& dt)
{
    return ((*this < dt) || (*this == dt)) ? true : false;
}

bool AllDateTime::operator >(AllDateTime& dt)
{
    return ((*this == dt) || (*this < dt)) ? false : true;
}

bool AllDateTime::operator >=(AllDateTime& dt)
{
    return ((*this > dt) || (*this == dt)) ? true : false;
}


/////////////Перегрузка операторов сложения/вычитания///////////////
    //перегрузка оператора сложения полной даты и секунд
const AllDateTime AllDateTime::operator +(const long dt)
{
    return AllDateTime(this->SetFullSecond() + dt, this->SetFullDays());
}

    //перегрузка оператора вычитания полной даты и секунд
const AllDateTime AllDateTime::operator -(const long dt)
{
    return AllDateTime(this->SetFullSecond() - dt, this->SetFullDays());
}

    //перегрузка оператора сложения полной даты и даты
const AllDateTime AllDateTime::operator +(DateTime& dt)
{
    return AllDateTime(this->SetFullSecond(), this->SetFullDays() + dt.SetFullDays());
}

    //перегрузка оператора вычитания полной даты и даты
const AllDateTime AllDateTime::operator -(DateTime& dt)
{
    return AllDateTime(this->SetFullSecond(), this->SetFullDays() - dt.SetFullDays());
}

    //перегрузка оператора сложения полной даты и времени
const AllDateTime AllDateTime::operator +(ClockTime& dt)
{
    return AllDateTime(this->SetFullSecond() + dt.SetFullSecond(), this->SetFullDays());
}

    //перегрузка оператора вычитания полной даты и времени
const AllDateTime AllDateTime::operator -(ClockTime& dt)
{
    return AllDateTime(this->SetFullSecond() - dt.SetFullSecond(), this->SetFullDays());
}

    //перегрузка оператора сложения двух полных дат
const AllDateTime AllDateTime::operator +(AllDateTime& dt)
{
    return AllDateTime(this->SetFullSecond() + dt.SetFullSecond(),
                       this->SetFullDays() + dt.SetFullDays());
}

    //перегрузка оператора вычитания двух полных дат
const AllDateTime AllDateTime::operator -(AllDateTime& dt)
{
    return AllDateTime(this->SetFullSecond() - dt.SetFullSecond(),
                       this->SetFullDays() - dt.SetFullDays());
}

//////////////////Перегрузка операторов ввода/вывода///////////////////////
    //перегрузка оператора вывода
std::ostream& operator<<(std::ostream& out, AllDateTime& dt)
{
    out << dt.DisplayAllDate();
    return out;
}

    //перегрузка оператора ввода
std::istream& operator >>(std::istream& in, AllDateTime& dt)
{
    char* buff = new char[20];
    in >> buff;
    dt = AllDateTime(buff);
    if(!in)
    { dt = AllDateTime(); }
    delete [] buff;
    return in;
}


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

