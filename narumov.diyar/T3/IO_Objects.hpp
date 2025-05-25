#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <complex>
#include <utility>
#include <iostream>

namespace narumov {
    struct LimitingSymbolIO {
        char symbol;
    };

    std::istream& operator>>(std::istream&, LimitingSymbolIO&&);
}

#endif
