#include "IO_Objects.hpp"
#include <iterator>
#include <algorithm>

namespace nspace
{
    std::istream& operator>>(std::istream& is, DelimiterIO&& dlim)
    {
        std::istream::sentry sentry(is);
        if(!sentry)
        {
            return is;
        }

        char c = '0';
        is >> c;

        if (is && (c != dlim.exp))
        {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, LabelIO&& l)
    {
        std::istream::sentry sentry(is);
        if(!sentry)
        {
            return is;
        }
        std::string temp;
        std::copy_n(
            std::istream_iterator<char>(is),
            l.label.length(),
            std::back_inserter(temp)
        );
        if(is && (temp != l.label))
        {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, CharIO&& chr)
    {
        std::istream::sentry sentry(is);
        if (!sentry)
        {
            return is;
        }

        char quote;
        is >> quote;
        if (quote != '\'')
        {
            is.setstate(std::ios::failbit);
            return is;
        }

        char c;
        is >> c;
        chr.ref = c;

        is >> quote;
        if (quote != '\'')
        {
            is.setstate(std::ios::failbit);
            return is;
        }

        return is;
    }

    std::istream& operator>>(std::istream& is, ULLHexIO&& ullhex)
    {
        std::istream::sentry sentry(is);
        if (!sentry)
        {
            return is;
        }

        char c1, c2;
        is >> c1 >> c2;
        if(c1 != '0' || (c2 != 'x' && c2 != 'X'))
        {
            is.setstate(std::ios::failbit);
            return is;
        }

        std::string hex_num;
        while(isalnum(is.peek())) {
            char c;
            is >> c;
            hex_num += c;
        }
        try
        {
            ullhex.ref = std::stoull(hex_num, nullptr, 16);
        }
        catch(...)
        {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, StringIO&& s)
    {
        std::istream::sentry sentry(is);
        if(!sentry)
        {
            return is;
        }
        return std::getline(is >> DelimiterIO { '\"' }, s.ref, '\"');
    }
}
