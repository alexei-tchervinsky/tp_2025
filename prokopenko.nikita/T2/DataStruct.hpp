#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <complex>
#include <string>
#include <iostream>

// Используем пространство имён prokopenko 
namespace prokopenko {

    // Структура, содержащая 3 поля с различными типами данных
    struct DataStruct {
        std::complex<double> key1;  // Комплексное число
        char key2;                  // Один символ
        std::string key3;           // Строка

        // Оператор сравнения для сортировки структур
        bool operator<(const DataStruct& other) const;
    };

    // Оператор ввода структуры из потока
    std::istream& operator>>(std::istream& in, DataStruct& data);

    // Оператор вывода структуры в поток
    std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}

#endif
