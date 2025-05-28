#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <iostream>
#include <string>

namespace erofick {
    struct LimitingSymbolIO {
        char symbol;
    };

    struct LabelIO {
        std::string label;
    };

    struct LongLongIO {
        long long& ref;
    };

    struct CharIO {
        char& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    std::istream& operator>>(std::istream&, LimitingSymbolIO&&);
    std::istream& operator>>(std::istream&, LabelIO&&);
    std::istream& operator>>(std::istream&, LongLongIO&&);
    std::istream& operator>>(std::istream&, CharIO&&);
    std::istream& operator>>(std::istream&, StringIO&&);
}


#endif

