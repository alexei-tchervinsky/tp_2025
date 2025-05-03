#include <iostream>
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
    if (in >> c && c != dest.exp) in.setstate(std::ios::failbit);
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
    in >> dest.ref >> quote;
    if (quote != '\'') in.setstate(std::ios::failbit);
    return in;
}

std::istream& operator>>(std::istream& in, RationalIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    in >> DelimiterIO{'('} >> DelimiterIO{':'} >> LabelIO{"N"};
    in >> dest.ref.first;
    in >> DelimiterIO{':'} >> LabelIO{"D"};
    in >> dest.ref.second;
    in >> DelimiterIO{':'} >> DelimiterIO{')'};
    if (dest.ref.second == 0) in.setstate(std::ios::failbit);
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
    if ((in >> data) && (data != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}
// data_struct.cpp
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
            if (in.peek() == '\'')  // Теперь key1 - только символ
            {
                in >> CharIO{input.key1};
                has_key1 = true;
            }
            in >> DelimiterIO{':'};
        }
        else if (field == "key2")
        {
            if (in.peek() == '(')  // Теперь key2 - рациональное число
            {
                if (in >> RationalIO{input.key2})
                {
                    has_key2 = true;
                }
            }
            else if (in.peek() == '"')  // Дополнительно: строка для key2
            {
                std::string str_val;
                if (in >> StringIO{str_val} && !str_val.empty())
                {
                    input.key2.first = static_cast<long long>(str_val[0]);
                    input.key2.second = 1;
                    has_key2 = true;
                }
            }
            in >> DelimiterIO{':'};
        }
        else if (field == "key3")
        {
            in >> StringIO{input.key3} >> DelimiterIO{':'};
            has_key3 = true;
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

std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
    std::ostream::sentry sentry(out);
    if (!sentry) return out;
    iofmtguard fmtguard(out);
    out << "(:key1 '" << src.key1 << "'"
        << ":key2 ";
    if (src.key2.second == 1 && isprint(static_cast<char>(src.key2.first))) {
        out << "\"" << static_cast<char>(src.key2.first) << "\"";
    } else {
        out << "(:N " << src.key2.first << ":D " << src.key2.second << ":)";
    }
    out << ":key3 \"" << src.key3 << "\":)";
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
