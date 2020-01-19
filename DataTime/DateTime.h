/* Библиотека для работы с форматом даты  в виде строки (dd.mm.yyyy) (char*),
 * день/месяц/год (integer) и кол-ва дней от нулевого високосного года (long).
 * Исчисление ведется с 01.01.0000 по 31.12.9999 (больший диапазон дат не целесообразен).
 * (Библиотека также должна будет включать класс для работы с суточным временем (hh:mm:ss) и
 * класс, являющийся производных от класса даты и времени (hh:mm:ss/dd.mm.yyyy).)
 * Created by DSuhoi (2020).
*/

#ifndef _DATA_H_
#define _DATA_H_

const int BUF_COUNTER = 11; //размер символьного массива (НЕ МЕНЕЕ 11 символов включая '\0')

class DataTime
{                //класс для хранения даты (dd.mm.yyyy) и взаимодействия с ней
private:
    char data_str[BUF_COUNTER]; //символьный массив для строки
    long full_day;              //кол-во дней от 0 (високосного) года
    int day;                    //кол-во дней в данном месяце
    int month;                  //кол-во месяцев в данном году
    int year;                   //кол-во лет
protected:
    inline void BUF_CLEAN();    //функия очистки символьного массива
    inline void STR_INLINE();   //функция обработки принятой даты (строки)

    void StringToData();    //перевод строки в дни, месяцы и годы
    void DataToString();    //перевод в формат dd.mm.yyyy
    void DataToFullDays();  //перевод даты в кол-во дней от 0 (високосного) года
    void FullDaysToData();  //перевод кол-ва дней от 0 года в дни, месяцы и годы
public:
    DataTime();             //пустой конструктор на дату (01.01.0000)
    DataTime(char*);        //конструктор через строку
    DataTime(long);         //конструктор через кол-во дней от 0 (високосного) года
    DataTime(int,int,int);  //конструктор через ручную утсановку даты (день, месяц, год)
    ////////////////////////МЕТОДЫ////////////////////////////////
    int& SetDay();          //установка/получение кол-ва дней в данном месяце
    int& SetMonth();        //установка/получение кол-ва месяцев в данном году
    int& SetYear();         //установка/получение кол-ва лет
    long& SetFullDays();    //установка/получение кол-ва дней от 0 (високосного) года
    char* DisplayData();    //вывод даты в формате dd.mm.yyyy
    void WriteData();       //установка даты через строку
    void SaveData();        //сохранение даты после ручного ввода через методы (Set)
    ///////////////////////ОПЕРАТОРЫ/////////////////////////////////
    //перегрузка унарных операторов
    const DataTime& operator++();       //префиксный инкремент
    const DataTime& operator++(int);    //постфиксный инкремент
    const DataTime& operator--();       //префиксный денкремент
    const DataTime& operator--(int);    //постфиксный денкремент
    //перегрузка операторов "прибавления/вычитания"
    const DataTime& operator+=(const long);     //прибавляем дни
    const DataTime& operator-=(const long);     //вычитаем дни
    const DataTime& operator+=(DataTime&);      //складываем дату
    const DataTime& operator-=(DataTime&);      //вычитаем дату
    //перегрузка операторов сравнения
    bool operator==(DataTime&);
    bool operator!=(DataTime&);
    bool operator<(DataTime&);
    bool operator<=(DataTime&);
    bool operator>(DataTime&);
    bool operator>=(DataTime&);
    //перегрузка операторов сложения/вычитания
    const DataTime operator+(DataTime&);    //перегрузка оператора сложения дат
    const DataTime operator-(DataTime&);    //перегрузка оператора вычитания двух дат
};


#endif // _DATA_H_
