#ifndef T2_OBJECTSIO_H
#define T2_OBJECTSIO_H
#include <iostream>

struct OctIO{
    unsigned long long& ref; //для key1
};

struct DelimiterIO{
    char exp; //для разделителей
};

struct LabelIO{
    std::string exp; //для ключевого слова key
};

struct CharIO{
    char& ref; //для key2
};

struct StringIO{
    std::string& ref; //для key3
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest); //перегрузка оператора ввода для разделителей
std::istream& operator>>(std::istream& in, OctIO&& dest); //перегрузка оператора ввода для данных 1-го ключа
std::istream& operator>>(std::istream& in, StringIO&& dest); //перегрузка оператора ввода для данных 3-го ключа
std::istream& operator>>(std::istream& in, LabelIO&& dest); //перегрузка оператора ввода для ключа
std::istream& operator>>(std::istream& in, CharIO&& dest); //перегрузка оператора ввода данных для 2-го ключа

#endif //T2_OBJECTSIO_H
