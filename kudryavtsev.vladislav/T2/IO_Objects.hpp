#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <complex>
#include <utility>
#include <iostream>

namespace myspace {
    struct LimitingSymbolIO {
        char symbol;
    };

    struct LabelIO {
        std::string label;
    };

    struct ComplexIO {
        std::complex<double>& ref;
    };

    struct BinaryIO {
        std::string& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    std::istream& operator>>(std::istream&, LimitingSymbolIO&&);
    std::istream& operator>>(std::istream&, LabelIO&&);
    std::istream& operator>>(std::istream&, ComplexIO&&);
    std::istream& operator>>(std::istream&, BinaryIO&&);
    std::istream& operator>>(std::istream&, StringIO&&);
}

#endif