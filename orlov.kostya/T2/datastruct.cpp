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

        os << "(:key1" << src.key1 << "ull";
        os << ":key2" << std::scientific << std::setprecision(6) << src.key2;
        os << ":key3 \"" << src.key3 << "\":)";

        return os;
    }

    std::istream& operator>>(std::istream& is, DataStruct& src)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        DataStruct tmp;

        is >> checkSymbol{ '(' };

        for (std::size_t i = 0; i < 3; ++i)
        {
            std::size_t num;

            is >> checkSymbol{ ':' } >> checkLabel{ "key" } >> num;

            if (num == 1)
            {
                is >> checkSymbol{ ' ' } >> checkUnsLongLong{ tmp.key1 };
            }
            else if (num == 2)
            {
                is >> checkSymbol{ ' ' } >> checkDoubleScientific{ tmp.key2 };
            }
            else if (num == 3)
            {
                is >> checkSymbol{ ' ' } >> checkString{ tmp.key3 };
            }
        }

        is >> checkSymbol{ ':' } >> checkSymbol{ ')' };

        if (is)
            src = tmp;

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

