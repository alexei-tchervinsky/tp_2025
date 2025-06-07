#include <algorithm>
#include <iomanip>
#include <cmath>
#include "datastruct.hpp"
#include "iofmtguard.hpp"
#include "ioObjects.hpp"

namespace orlov
{
    std::ostream& operator<<(std::ostream& os, const DataStruct& src)
    {
        std::ostream::sentry sentry(os);
        if (!sentry) return os;

        iofmtguard guard(os);
        os << "(:key1 " << src.key1 << "ull";
        os << ":key2 " << std::scientific << std::setprecision(6) << src.key2;
        os << ":key3 \"" << src.key3 << "\":)";
        return os;
    }

    std::istream& operator>>(std::istream& is, DataStruct& dest)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        DataStruct tmp;
        char c = 0;

        if (!(is >> checkSymbol{'('} >> checkSymbol{':'})) {
            is.setstate(std::ios::failbit);
            return is;
        }

        for (int i = 0; i < 3; ++i) {
            std::size_t num = 0;
            if (!(is >> checkLabel{"key"} >> num >> checkSymbol{' '})) {
                is.setstate(std::ios::failbit);
                return is;
            }

            if (num == 1) {
                if (!(is >> checkUnsLongLong{tmp.key1})) return is;
            }
            else if (num == 2) {
                if (!(is >> checkDoubleScientific{tmp.key2})) return is;
            }
            else if (num == 3) {
                if (!(is >> checkString{tmp.key3})) return is;
            }

            if (i < 2 && !(is >> checkSymbol{':'})) {
                is.setstate(std::ios::failbit);
                return is;
            }
        }

        if (!(is >> checkSymbol{':'} >> checkSymbol{')'})) {
            is.setstate(std::ios::failbit);
            return is;
        }

        if (is) dest = tmp;
        return is;
    }

    bool compareDataStruct(const DataStruct& first, const DataStruct& second)
    {
        if (first.key1 != second.key1)
            return first.key1 < second.key1;
        if (std::abs(first.key2 - second.key2) > 1e-9)
            return first.key2 < second.key2;
        return first.key3.length() < second.key3.length();
    }
}

