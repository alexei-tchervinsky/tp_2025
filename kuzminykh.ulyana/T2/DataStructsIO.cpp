#include "DataStructsIO.h"

iofmtguard::iofmtguard(std::basic_ios<char>& s) :
    s_(s),
    width_(s.width()),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
{}

iofmtguard::~iofmtguard()
{
    s_.width(width_);
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}

std::istream& operator>>(std::istream& in, DelimiterIO&& d)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char c = 0;
    in >> c;
    if (in >> c && c != d.exp)
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, LongLongIO&& d)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    in >> d.ref;

    if (in.peek() == 'l' || in.peek() == 'L')
    {
        std::string suffix;
        in >> suffix;
        if (suffix != "ll" && suffix != "LL")
        {
            in.setstate(std::ios::failbit);
        }
    }
    return in;
}

std::istream& operator>>(std::istream& in, ULongLongOctIO&& d)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    if (in.peek() == '0')
    {
        in >> std::oct >> d.ref;
    }
    else
    {
        in >> d.ref;
    }

    if (in.peek() == 'u' || in.peek() == 'U')
    {
        std::string suffix;
        in >> suffix;
        if (suffix != "ull" && suffix != "ULL")
        {
            in.setstate(std::ios::failbit);
        }
    }
    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& d)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, d.ref, '"');
}

std::istream& operator>>(std::istream& in, DataStruct& d)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    DataStruct tmp;
    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };

    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
    while (in && in.peek() != ')')
    {
        std::string key;
        if (!(in >> key))
        {
            in.setstate(std::ios::failbit);
            break;
        }

        if (key == "key1" && !hasKey1)
        {
            if (!(in >> LongLongIO{ tmp.key1 } >> DelimiterIO{ ':' }))
            {
                break;
            }
            hasKey1 = true;
        }
        else if (key == "key2" && !hasKey2)
        {
            if (!(in >> ULongLongOctIO{ tmp.key2 } >> DelimiterIO{ ':' }))
            {
                break;
            }
            hasKey2 = true;
        }
        else if (key == "key3" && !hasKey3)
        {
            if (!(in >> StringIO{ tmp.key3 } >> DelimiterIO{ ':' }))
            {
                break;
            }
            hasKey3 = true;
        }
        else
        {
            std::string dummy;
            while (in && in.peek() != ':' && in.peek() != ')')
            {
                in >> dummy;
            }
            if (in.peek() == ':') in.get();
        }
    }

    if (hasKey1 && hasKey2 && hasKey3)
    {
        in >> DelimiterIO{ ')' };
        d = tmp;
    }
    else
    {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& d)
{
    std::ostream::sentry sentry(out);
    if (!sentry) return out;

    iofmtguard fmt(out);
    out << "(:key1 " << d.key1 << "ll";
    out << ":key2 0" << std::oct << d.key2;
    out << ":key3 \"" << d.key3 << "\":)";
    return out;
}
