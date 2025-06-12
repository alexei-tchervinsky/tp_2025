#include "ioObjects.hpp"

#include <iterator>
#include <algorithm>

namespace orlov
{
    std::istream& operator>>(std::istream& is, checkSymbol&& cK) {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        char c;
        is >> c;

        if(is && (c != cK.symbol))
            is.setstate(std::ios::failbit);

        return is;
    }
}

