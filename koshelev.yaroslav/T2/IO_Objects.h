#ifndef IO_OBJECTS_H
#define IO_OBJECTS_H

#include <string>
#include <iostream>

namespace solution {

    struct DelimiterIO {
        char expected;
    };

    struct LabelIO {
        std::string& ref;
    };

    struct DoubleSciIO {
        double& ref;
    };

    struct ULLHexIO {
        unsigned long long& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&&);
    std::istream& operator>>(std::istream& in, LabelIO&&);
    std::istream& operator>>(std::istream& in, DoubleSciIO&&);
    std::istream& operator>>(std::istream& in, ULLHexIO&&);
    std::istream& operator>>(std::istream& in, StringIO&&);

}

#endif
