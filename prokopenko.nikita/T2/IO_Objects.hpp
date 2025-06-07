#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <string>
#include <complex>
#include <iostream>

namespace prokopenko {

    // Структура для чтения ожидаемого символа-разделителя
    struct DelimiterIO {
        char expected;
    };

    // Структура для чтения метки ключа
    struct LabelIO {
        std::string& ref;
    };

    // Структура для чтения комплексного числа
    struct ComplexIO {
        std::complex<double>& ref;
    };

    // Структура для чтения одиночного символа
    struct CharIO {
        char& ref;
    };

    // Структура для чтения строки
    struct StringIO {
        std::string& ref;
    };

    // Объявления операторов для всех типов ввода
    std::istream& operator>>(std::istream& in, DelimiterIO&&);
    std::istream& operator>>(std::istream& in, LabelIO&&);
    std::istream& operator>>(std::istream& in, ComplexIO&&);
    std::istream& operator>>(std::istream& in, CharIO&&);
    std::istream& operator>>(std::istream& in, StringIO&&);
}

#endif
