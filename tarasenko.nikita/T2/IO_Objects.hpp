#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <iostream>

namespace tarasenko {
    struct DelimiterIO {
        char delimiter;
    };

    struct OctIO {
        unsigned long long& ref;
    };

    struct String_IO {
        std::string &ref;
    };

    struct Char_IO {
        char& ref;
    };


    struct LabelIO {
        std::string label;
    };

    std::istream &operator>>(std::istream &, LabelIO &&);

    std::istream &operator>>(std::istream &in, DelimiterIO &&dest);

    std::istream& operator>>(std::istream& in, Oct_IO&& dest);

    std::istream& operator>>(std::istream& in, Char_IO&& dest);

    std::istream &operator>>(std::istream &in, StringIO &&dest);
}

#endif //IO_OBJECTS_HPP
