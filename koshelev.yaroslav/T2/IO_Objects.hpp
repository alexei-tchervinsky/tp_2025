#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <string>
#include <iostream>

namespace solution {
    struct DelimiterIO {
        char expected;
    };

    struct LabelIO {
        std::string& ref;
    };

    struct DoubleIO {
        double& ref;
    };

    struct HexUllIO {
        unsigned long long& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&&);
    std::istream& operator>>(std::istream& in, LabelIO&&);
    std::istream& operator>>(std::istream& in, DoubleIO&&);
    std::istream& operator>>(std::istream& in, HexUllIO&&);
    std::istream& operator>>(std::istream& in, StringIO&&);
}

#endif
