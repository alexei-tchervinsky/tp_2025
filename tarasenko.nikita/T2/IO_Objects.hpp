#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <iostream>
#include <string>

namespace tarasenko {
    struct DelimiterIO {
        char delimiter;
    };

    struct OctIO {
        unsigned long long& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    struct CharIO {
        char& ref;
    };

    struct LabelIO {
        std::string label;
    };

    std::istream& operator>>(std::istream&, LabelIO&&);
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, OctIO&& dest);
    std::istream& operator>>(std::istream& in, CharIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif //IO_OBJECTS_HPP