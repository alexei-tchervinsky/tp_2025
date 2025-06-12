#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <string>
#include <iostream>

namespace solution {
    struct DelimiterIO { char expected; };
    struct DoubleIO { double& ref; };
    struct HexUllIO { unsigned long long& ref; };
    struct StringIO { std::string& ref; };
    struct LabelIO { std::string& ref; };
    struct Key1IO { double& ref; };

    std::istream& operator>>(std::istream& in, DelimiterIO&& d);
    std::istream& operator>>(std::istream& in, DoubleIO&& d);
    std::istream& operator>>(std::istream& in, HexUllIO&& h);
    std::istream& operator>>(std::istream& in, StringIO&& s);
    std::istream& operator>>(std::istream& in, LabelIO&& l);
    std::istream& operator>>(std::istream& in, Key1IO&& k);
}

#endif
