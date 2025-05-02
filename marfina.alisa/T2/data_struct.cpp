#include <iostream>
#include <string>
#include <iomanip>
#include "data_struct.hpp"

namespace marfina {

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    char c;
    if (in >> c && c != dest.exp)
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, CharIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    char quote;
    if (in >> quote && quote != '\'')
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    if (in >> dest.ref >> quote && quote != '\'')
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, RationalIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    long long numerator = 0;
    unsigned long long denominator = 0;

    if (in >> DelimiterIO{'('} >> DelimiterIO{':'} >> LabelIO{"N"}
            >> numerator
            >> DelimiterIO{':'} >> LabelIO{"D"}
            >> denominator
            >> DelimiterIO{':'} >> DelimiterIO{')'}
        && denominator != 0)
    {
        dest.ref.first = numerator;
        dest.ref.second = denominator;
    } else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, LabelIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    std::string data;
    if (in >> data && data != dest.exp) {
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

    if (!(in >> DelimiterIO{'('} >> DelimiterIO{':'})) {
        return in;
    }

    while (true) {
        if (in.peek() == ')')
        {
            in.ignore();
            break;
        }

        std::string field;
        if (!(in >> field)) break;

        if (field == "key1")
        {
            if (in >> RationalIO{input.key1} >> DelimiterIO{':'}) {
                has_key1 = true;
            } else break;
        }
        else if (field == "key2")
        {
            if (in >> CharIO{input.key2} >> DelimiterIO{':'}) {
                has_key2 = true;
            } else break;
        }
        else if (field == "key3")
        {
            if (in >> StringIO{input.key3} >> DelimiterIO{':'}) {
                has_key3 = true;
            } else break;
        }
        else {
            in.setstate(std::ios::failbit);
            break;
        }
    }

    if (has_key1 && has_key2 && has_key3)
    {
        dest = input;
    } else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
    std::ostream::sentry sentry(out);
    if (!sentry) return out;

    iofmtguard fmtguard(out);
    out << "(:key1 (:N " << src.key1.first << ":D " << src.key1.second << ":)"
        << ":key2 '" << src.key2 << "'"
        << ":key3 \"" << src.key3 << "\":)";
    return out;
}

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

bool compare_structures(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}

} // namespace marfina
