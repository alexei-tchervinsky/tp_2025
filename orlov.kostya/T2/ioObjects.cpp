#include <string>
#include <sstream>
#include <cctype>
#include "ioObjects.hpp"

namespace orlov
{
    std::istream& operator>>(std::istream& is, checkSymbol&& cSymb)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        char c;
        is >> c;

        if (is && (c != cSymb.symbol))
            is.setstate(std::ios::failbit);

        return is;
    }

    std::istream& operator>>(std::istream& is, checkLabel&& cL)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        std::string tmp;
        is >> tmp;

        if (is && (tmp != cL.label))
            is.setstate(std::ios::failbit);

        return is;
    }

    std::istream& operator>>(std::istream& is, checkUnsLongLong&& cULL)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        std::string numbStr;
        is >> numbStr;

        if
        (
            numbStr.size() > 2 &&
            (
                numbStr.substr(numbStr.size() - 3) == "ull" ||
                numbStr.substr(numbStr.size() - 3) == "uLL"
            )
        )
        {
            numbStr = numbStr.substr(0, numbStr.size() - 3);
        }
        else if
        (
            numbStr.size() > 1 &&
            (
                numbStr.back() == 'u' ||
                numbStr.back() == 'U'
            )
        )
        {
            numbStr = numbStr.substr(0, numbStr.size() - 1);
        }

        std::istringstream iss(numbStr);
        iss >> cULL.src;

        if (iss.fail() || !iss.eof())
            is.setstate(std::ios::failbit);

        return is;
    }

    std::istream& operator>>(std::istream& is, checkDoubleScientific&& cD)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        std::string numbStr;
        is >> numbStr;

        if
        (
            !numbStr.empty() &&
            (
                numbStr.back() == 'd' ||
                numbStr.back() == 'D'
            )
        )
        {
            numbStr = numbStr.substr(0, numbStr.size() - 1);
        }

        std::istringstream iss(numbStr);
        iss >> cD.src;

        if (iss.fail() || !iss.eof())
            is.setstate(std::ios::failbit);

        return is;
    }

    std::istream& operator>>(std::istream& is, checkString&& cStr)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        return std::getline(is >> checkSymbol{ '\"' }, cStr.src, '\"');
    }
}