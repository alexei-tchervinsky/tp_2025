#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <iostream>
#include <iomanip>

namespace tarasov {
    struct DelimiterIO {
        char exp;
    };

    struct DoubleSciIO {
        double& ref;
    };

    struct CharLitIO {
        char& ref;
    };

    struct StringLitIO {
        std::string& ref;
    };

    char readChar(std::istream& in);

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);

    std::istream& operator>>(std::istream& in, DoubleSciIO&& dest);

    std::istream& operator>>(std::istream& in, CharLitIO&& dest);

    std::istream& operator>>(std::istream& in, StringLitIO&& dest);
}

#endif

