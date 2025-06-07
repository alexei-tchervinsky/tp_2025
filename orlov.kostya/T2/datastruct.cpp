#include <algorithm>
#include <iomanip>
#include <cmath>
#include <sstream>

#include "datastruct.hpp"
#include "iofmtguard.hpp"
#include "ioObjects.hpp"

namespace orlov
{
    std::string formatScientific(const double data)
    {
        std::ostringstream oss;
        oss << std::scientific << std::setprecision(1) << data;
        std::string str = oss.str();

        size_t e_pos = str.find('e');
        if (e_pos != std::string::npos) {
            if (str[e_pos + 2] == '0') {
                str.erase(e_pos + 2, 1);
            }
        }
        return str;
    }

    std::ostream& operator<<(std::ostream& os, const DataStruct& src)
    {
        std::ostream::sentry sentry(os);
        if (!sentry) return os;

        iofmtguard guard(os);

        os << "(:key1 " << src.key1 << "ull";
        os << ":key2 " << formatScientific(src.key2);
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
            if (i == 0)
            {
                is >> checkSymbol{ ':' };
                is >> checkLabel{ "key1" }  >> checkUnsLongLong{ tmp.key1 };
            }
            else if (i == 1)
            {
                is >> checkLabel{ "key2" } >> checkDoubleScientific{ tmp.key2 };
            }
            else if (i == 2)
            {
                is >> checkLabel{ ":key3" } >> checkString{ tmp.key3 };
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

