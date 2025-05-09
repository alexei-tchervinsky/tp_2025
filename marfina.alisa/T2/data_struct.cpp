#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <iomanip>
#include "data_struct.hpp"

namespace marfina
{

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c;
    in >> c;
    if (in && (c != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, CharIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }


    if (! (in >> DelimiterIO {'\''}))
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    char c;

    if (!(in >> c))
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    dest.ref = c;

    if (!(in >> DelimiterIO{'\''}))
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    return in;

}

std::istream& operator>>(std::istream& in, RationalIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    if (!(in >> DelimiterIO{'('} >> DelimiterIO{':'} >> LabelIO{"N"}))
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    if (!(in >> dest.ref.first)) return in;
    if (!(in >> DelimiterIO{':'} >> LabelIO{"D"}))
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    if (!(in >> dest.ref.second)) return in;
    if (!(in >> DelimiterIO{':'} >> DelimiterIO{')'}))
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    if (dest.ref.second == 0)
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return std::getline(in >> DelimiterIO{'\"'}, dest.ref, '\"');
}

std::istream& operator>>(std::istream& in, LabelIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    std::string data;
    std::copy_n
    (
        std::istream_iterator<char>(in),
        dest.exp.length(),
        std::back_inserter(data)
    );

    if (in && (data != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    DataStruct input;
    bool has_key1 = false, has_key2 = false, has_key3 = false;

    in >> DelimiterIO{'('} >> DelimiterIO{':'};

    while (true)
    {
        if (in.peek() == ')')
        {
            in.ignore();
            break;
        }

        std::string field;
        if (!(in >> field)) break;
        if (field == "key1")
        {
            if (in >> CharIO{input.key1}) has_key1 = true;
            in >> DelimiterIO{':'};
        }
        else if (field == "key2")
        {
            if (in >> RationalIO{input.key2}) has_key2 = true;
            in >> DelimiterIO{':'};
        }
        else if (field == "key3")
        {
            if (in >> StringIO{input.key3}) has_key3 = true;
            in >> DelimiterIO{':'};
        }
        else
        {
            std::string stranger;
            std::getline(in, stranger, ':');
        }
    }

    if (has_key1 && has_key2 && has_key3)
    {
        dest = input;
    }
    else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
{
    std::ostream::sentry sentry(out);
    if (!sentry) return out;
    iofmtguard fmtguard(out);
    out << "(:key1 '" << dest.key1 << "'"
    << ":key2 (:N " << dest.key2.first << ":D " << dest.key2.second << ":)"
    << ":key3 \"" << dest.key3 << "\":)";
    return out;
}

iofmtguard::iofmtguard(std::basic_ios<char>& s) :
    s_(s), width_(s.width()), fill_(s.fill()),
    precision_(s.precision()), fmt_(s.flags()){}

iofmtguard::~iofmtguard()
{
    s_.width(width_);
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}

bool compare_structures(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}
}
