//Created by DSuhoi (2020).//
#include <iostream>
#include <cstring>
#include "DateTime.h"


///////////////////////ФУНКЦИИ//////////////////////////////

    //функия очистки символьного массива
inline void DataTime::BUF_CLEAN()
{
     for(int i=0;i<BUF_COUNTER; data_str[i++]=0);   //очистка массива
}

    //функция обработки принятой даты (строки)
inline void DataTime::STR_INLINE()
{
    for(;;) //пока не будет соблюден формат введенной даты
    {
        BUF_CLEAN();
        scanf("%s",data_str);
        if(data_str[2]!='.' || data_str[5]!='.' || data_str[10]!=0)
        { std::cout << "ERROR: Print date(dd.mm.yyyy)!" <<std::endl; }
        else    //если все принято, то выходим из цикла
        { break; }
    }
}


    //пустой конструктор на дату (01.01.0000)
DataTime::DataTime()
{
    day = 1; month = 1; year = 0; full_day = 1; //установка по умолчанию всех данных
    strcpy(data_str,"01.01.0000");
}

    //конструктор через кол-во дней от 0  года
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

    //установка/получение кол-ва дней от 0 (високосного) года
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
    BUF_CLEAN();
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

    //перевод даты в кол-во дней от 0 (високосного) года
void DataTime::DataToFullDays()
{
    full_day = 0;   //количество дней с 0 года до dd.mm.yyyy
    bool visokos_count = ((!(year%4))&&(year%100)) || (!(year%400)); //определение високосного года
    int visokos_num = year/4 - (year/100 - year/400); //кол-во високосных лет

    switch (month)
    {               //определение кол-ва дней через месяц
    case 1:
        full_day = day;
        break;
    case 2:
        full_day = day + 31;
        break;\
    case 3:
        if(visokos_count) full_day = day + 60;  //счет дней по високосным годам
                else full_day = day + 59;
        break;
    case 4:
        if (visokos_count) full_day=91+day;
                else full_day=90+day;
        break;
    case 5:
        if (visokos_count) full_day=121+day;
                else full_day=120+day;
        break;
    case 6:
        if (visokos_count) full_day=152+day;
                else full_day=151+day;
        break;
    case 7:
        if (visokos_count) full_day=182+day;
                else full_day=181+day;
        break;
    case 8:
        if (visokos_count) full_day=213+day;
                else full_day=212+day;
        break;
    case 9:
        if (visokos_count) full_day=244+day;
                else full_day=243+day;
        break;
    case 10:
        if (visokos_count) full_day=274+day;
                else full_day=273+day;
        break;
    case 11:
        if (visokos_count) full_day=305+day;
                else full_day=304+day;
        break;
    case 12:
        if (visokos_count) full_day=335+day;
                else full_day=334+day;
        break;
    default: std::cout << "ERROR: MONTH!" << std::endl; //если как-то ввели неправильный месяц...
        break;
    }

    if(!visokos_count) full_day++;  //погрешность на 0 високосный год

    full_day +=365*(year - visokos_num) + 366*visokos_num;  //прибавление дней по годам
}

    //перевод кол-ва дней от 0 года в дни, месяцы и годы
void DataTime::FullDaysToData()
{
    long data_x = full_day;     //создаем переменную для временного хранения данных
    int year_x = 0, month_x = 0;    //переменные для хранения года и месяца
    bool vesokos_count = 0;         //счетчик високосного года

    //определяем год
    for(year_x = 0; data_x > 366; year_x++)
    {
    if((((!(year_x%4))&&(year_x%100))||(!(year_x%400)))) //если идет високосный год...
        data_x -=366;
    else
        data_x -=365;   //если не високосный...
    }

    (((!(year_x%4))&&(year_x%100))||(!(year_x%400))) ? vesokos_count = 1 : vesokos_count = 0;

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
    STR_INLINE();       //принимаем строку
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
const DataTime& DataTime::operator++()
{
    this->SetFullDays()++;
    this->FullDaysToData();
    return *this;
}

    //постфиксный инкремент
const DataTime& DataTime::operator++(int)
{
    DataTime* tmp = this;
    this->SetFullDays()++;
    this->FullDaysToData();
    return *tmp;
}

    //префиксный денкремент
const DataTime& DataTime::operator--()
{
    this->SetFullDays()--;
    this->FullDaysToData();
    return *this;
}

    //постфиксный денкремент
const DataTime& DataTime::operator--(int)
{
    DataTime* tmp = this;
    this->SetFullDays()--;
    this->FullDaysToData();
    return *tmp;
}

/////////Перегрузка операторов "прибавления/вычитания"////////////

    //прибавляем дни
const DataTime& DataTime::operator+=(const long d)
{
    this->SetFullDays() += d;
    this->FullDaysToData();
    return *this;
}

    //вычитаем дни
const DataTime& DataTime::operator-=(const long d)
{
    this->SetFullDays() -= d;
    this->FullDaysToData();
    return *this;
}

    //складываем дату
const DataTime& DataTime::operator+=(DataTime& d)
{
    this->SetFullDays() += d.SetFullDays();
    this->FullDaysToData();
    return *this;
}

    //вычитаем дату
const DataTime& DataTime::operator-=(DataTime& d)
{
    this->SetFullDays() -= d.SetFullDays();
    this->FullDaysToData();
    return *this;
}

///////////////Перегрузка операторов сравнения/////////////////////

bool DataTime::operator==(DataTime& d)
{
    return (this->SetFullDays() == d.SetFullDays()) ? true : false;
}

bool DataTime::operator!=(DataTime& d)
{
    return (*this == d) ? false : true;
}

bool DataTime::operator<(DataTime& d)
{
    return (this->SetFullDays() < d.SetFullDays()) ? true : false;
}

bool DataTime::operator<=(DataTime& d)
{
    return ((*this < d) || (*this == d)) ? true : false;
}

bool DataTime::operator>(DataTime& d)
{
    return ((*this == d) || (*this < d)) ? false : true;
}

bool DataTime::operator>=(DataTime& d)
{
    return ((*this > d) || (*this == d)) ? true : false;
}

/////////////Перегрузка операторов сложения/вычитания///////////////

    //перегрузка оператора сложения дат
const DataTime DataTime::operator+(DataTime& d)
{
    return DataTime(this->SetFullDays() + d.SetFullDays());
}

    //перегрузка оператора вычитания двух дат
const DataTime DataTime::operator-(DataTime& d)
{
    return DataTime(this->SetFullDays() - d.SetFullDays());
}


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
