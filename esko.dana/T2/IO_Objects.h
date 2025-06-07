// IO_Objects.hpp
#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <iostream>
#include <string>

namespace Data {
    struct LimitingSymbolIO {
        char symbol;
    };

    struct LabelIO {
        std::string label;
    };

    struct SignedLongLongIO {
        long long& ref;
    };

    struct DoubleIO {
        double& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    std::istream& operator>>(std::istream&, LimitingSymbolIO&&);
    std::istream& operator>>(std::istream&, LabelIO&&);
    std::istream& operator>>(std::istream&, SignedLongLongIO&&);
    std::istream& operator>>(std::istream&, DoubleIO&&);
    std::istream& operator>>(std::istream&, StringIO&&);
}

#endif