#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <complex>
#include <string>
#include <iostream>

namespace prokopenko {
  // Структура для хранения данных с тремя ключами:
  // key1 - комплексное число, key2 - символ, key3 - строка
  struct DataStruct {
    std::complex<double> key1;  // Комплексное число
    char key2;                  // Символ
    std::string key3;           // Строка

    // Оператор сравнения для сортировки объектов DataStruct
    // Сначала сравниваем по модулю key1, затем по key2, затем по длине key3
    bool operator<(const DataStruct& other) const;
  };

  // Операторы ввода и вывода для работы с потоком в пользовательском формате
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}

#endif
