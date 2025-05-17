#include "IO_Objects.hpp"

#include <iterator>
#include <algorithm>

namespace narumov {
    std::istream& operator>>(std::istream& is, LimitingSymbolIO&& ls) {
        std::istream::sentry sentry(is);
        if(!sentry) {
            return is;
        }
        char c;
        is >> c;
        if(is && (c != ls.symbol)) {
            is.setstate(std::ios::failbit);
        }
        return is;
    }
}
