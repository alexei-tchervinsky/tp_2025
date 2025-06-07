#ifndef IOOBJECTS_HPP
#define IOOBJECTS_HPP

#include <string>
#include <iostream>

namespace orlov
{
    struct checkSymbol
    {
        char symbol;
    };

    struct checkLabel
    {
        std::string label;
    };

    struct checkUnsLongLong
    {
        unsigned long long& src;
    };

    struct checkDoubleScientific
    {
        double& src;
    };

    struct checkString
    {
        std::string& src;
    };

    std::istream& operator>>(std::istream& is, checkSymbol&& cSymb);
    std::istream& operator>>(std::istream& is, checkLabel&& cL);
    std::istream& operator>>(std::istream& is, checkUnsLongLong&& cULL);
    std::istream& operator>>(std::istream& is, checkDoubleScientific&& cD);
    std::istream& operator>>(std::istream& is, checkString&& cStr);
}

#endif // !__IOOBJECTS_HPP

