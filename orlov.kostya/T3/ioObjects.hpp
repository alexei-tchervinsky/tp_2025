#ifndef IOOBJECTS_HPP
#define IOOBJECTS_HPP

#include <complex>
#include <utility>
#include <iostream>

namespace orlov
{
    struct checkSymbol
    {
        char symbol;
    };

    std::istream& operator>>(std::istream& is, checkSymbol&& cS);
}

#endif // !__IOOBJECTS_HPP

