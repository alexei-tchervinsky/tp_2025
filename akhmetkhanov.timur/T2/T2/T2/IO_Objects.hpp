#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <iostream>
#include <string>

namespace nspace {
    struct DelimiterIO { char exp; };
    struct LabelIO { std::string label; };
    struct ULLHexIO { unsigned long long& ref; };
    struct DoubleSciIO { double& ref; };
    struct StringIO { std::string& ref; };

    std::istream& operator>>(std::istream&, DelimiterIO&&);
    std::istream& operator>>(std::istream&, LabelIO&&);
    std::istream& operator>>(std::istream&, ULLHexIO&&);
    std::istream& operator>>(std::istream&, DoubleSciIO&&);
    std::istream& operator>>(std::istream&, StringIO&&);
}

#endif
