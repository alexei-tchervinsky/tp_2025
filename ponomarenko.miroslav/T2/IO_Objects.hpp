#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <string>
#include <complex>
#include <iostream>

namespace ponomarenko {

    struct DelimiterIO {
        char expected;
    };

    struct LabelIO {
        std::string& ref;
    };

    struct ComplexIO {
        std::complex<double>& ref;
    };

    struct CharIO {
        char& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&&);
    std::istream& operator>>(std::istream& in, LabelIO&&);
    std::istream& operator>>(std::istream& in, ComplexIO&&);
    std::istream& operator>>(std::istream& in, CharIO&&);
    std::istream& operator>>(std::istream& in, StringIO&&);
}

#endif
