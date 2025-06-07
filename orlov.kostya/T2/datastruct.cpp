#include <algorithm>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <map> // Добавлено для использования std::map

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
        if (e_pos != std::string::npos)
        {
            if (str[e_pos + 2] == '0' && str.length() > e_pos + 3)
            {
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
        std::map<std::string, bool> keys_read;
        keys_read["key1"] = false;
        keys_read["key2"] = false;
        keys_read["key3"] = false;

        is >> checkSymbol{ '(' };
        if (!is) return is;

        for (std::size_t i = 0; i < 3; ++i)
        {
            is >> checkSymbol{ ':' };
            if (!is) return is;

            std::string label_str;
            is >> checkLabelAnyOrder{ label_str };
            if (!is) return is;

            if (label_str == "key1")
            {
                if (keys_read["key1"]) {
                    is.setstate(std::ios::failbit);
                    return is;
                }
                is >> checkUnsLongLong{ tmp.key1 };
                if (!is) return is;
                keys_read["key1"] = true;
            }
            else if (label_str == "key2")
            {
                if (keys_read["key2"]) {
                    is.setstate(std::ios::failbit);
                    return is;
                }
                is >> checkDoubleScientific{ tmp.key2 };
                if (!is) return is;
                keys_read["key2"] = true;
            }
            else if (label_str == "key3")
            {
                if (keys_read["key3"]) {
                    is.setstate(std::ios::failbit);
                    return is;
                }
                is >> checkString{ tmp.key3 };
                if (!is) return is;
                keys_read["key3"] = true;
            }
            else
            {
                is.setstate(std::ios::failbit);
                return is;
            }
        }

        if (is && (!keys_read["key1"] || !keys_read["key2"] || !keys_read["key3"]))
        {
            is.setstate(std::ios::failbit);
            return is;
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

