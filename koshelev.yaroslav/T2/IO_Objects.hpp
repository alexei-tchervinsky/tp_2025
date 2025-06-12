#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <string>
#include <iostream>

namespace koshelev {
    struct DelimiterIO {
        char expected;
    };

    struct LabelIO {
        std::string& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    struct ScientificIO {
        double& ref;
    };

    struct HexIO {
        unsigned long long& ref;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&&);
    std::istream& operator>>(std::istream& in, LabelIO&&);
    std::istream& operator>>(std::istream& in, StringIO&&);
    std::istream& operator>>(std::istream& in, ScientificIO&&);
    std::istream& operator>>(std::istream& in, HexIO&&);
}

#endif
