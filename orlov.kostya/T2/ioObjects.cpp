#include <string>
#include <sstream>
#include <cctype>
#include <limits>
#include "ioObjects.hpp"

namespace orlov
{
    std::istream& operator>>(std::istream& is, checkSymbol&& cSymb)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        char c;

        if (is.peek() == cSymb.symbol) {
            is.get(c);
        } else {
            is.setstate(std::ios::failbit);
        }

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

    std::istream& operator>>(std::istream& is, checkLabelAnyOrder&& cLAO)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        std::string temp_label;
        char c;
        while (is.get(c))
        {
            if (c == ' ' || c == ':')
            {
                is.putback(c);
                break;
            }
            temp_label += c;
        }

        if (temp_label.empty())
        {
            is.setstate(std::ios::failbit);
        } else {
            cLAO.label = temp_label;
        }

        return is;
    }


    std::istream& operator>>(std::istream& is, checkUnsLongLong&& cULL)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        std::string numbStr;

        char c;
        while (is.get(c))
        {
            if (c == ':' || c == ' ')
            {
                is.putback(c);
                break;
            }
            numbStr += c;
        }

        if (numbStr.size() >= 3 && (numbStr.substr(numbStr.size() - 3) == "ull" || numbStr.substr(numbStr.size() - 3) == "uLL"))
        {
            numbStr = numbStr.substr(0, numbStr.size() - 3);
        }
        else if (numbStr.size() >= 1 && (numbStr.back() == 'u' || numbStr.back() == 'U'))
        {
            numbStr = numbStr.substr(0, numbStr.size() - 1);
        }

        std::istringstream iss(numbStr);
        iss >> cULL.src;

        if (iss.fail() || !iss.eof()) {
            is.setstate(std::ios::failbit);
        }

        return is;
    }

    std::istream& operator>>(std::istream& is, checkDoubleScientific&& cD)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        double value;

        is >> std::scientific >> value;

        if (is.fail())
        {
            is.setstate(std::ios::failbit);
            return is;
        }
        cD.src = value;
        return is;
    }

    std::istream& operator>>(std::istream& is, checkString&& cStr)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        is >> checkSymbol{ '\"' };
        if (!is) return is;

        std::string temp_str;
        std::getline(is, temp_str, '\"');

        if (is.fail() && !is.eof())
        {
            return is;
        }

        cStr.src = temp_str;
        return is;
    }
}

