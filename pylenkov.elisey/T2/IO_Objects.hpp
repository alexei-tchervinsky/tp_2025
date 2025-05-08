#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <complex>
#include <utility>
#include <iostream>

namespace nspace
{

    struct DelimiterIO
    {
        char exp;
    };

    struct LabelIO
    {
        std::string label;
    };

    struct CharIO
    {
        char& ref;
    };

    struct ULLHexIO
    {
        unsigned long long& ref;
    };

    struct StringIO
    {
        std::string& ref;
    };

    std::istream& operator>>(std::istream&, DelimiterIO&&);
    std::istream& operator>>(std::istream&, LabelIO&&);
    std::istream& operator>>(std::istream&, CharIO&&);
    std::istream& operator>>(std::istream&, ULLHexIO&&);
    std::istream& operator>>(std::istream&, StringIO&&);
}

#endif
