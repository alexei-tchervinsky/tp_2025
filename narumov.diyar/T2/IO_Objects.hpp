#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <complex>
#include <utility>
#include <iostream>

namespace narumov {
    struct LimitingSymbolIO {
        char symbol;
    };

    struct LabelIO {
        std::string label;
    };

    struct ComplexIO {
        std::complex<double>& ref;
    };

    struct RationalIO {
        std::pair<long long, unsigned long long>& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    std::istream& operator>>(std::istream&, LimitingSymbolIO&&);
    std::istream& operator>>(std::istream&, LabelIO&&);
    std::istream& operator>>(std::istream&, ComplexIO&&);
    std::istream& operator>>(std::istream&, RationalIO&&);
    std::istream& operator>>(std::istream&, StringIO&&);
}

#endif
