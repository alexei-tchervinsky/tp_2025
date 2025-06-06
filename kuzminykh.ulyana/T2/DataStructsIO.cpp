#include "DataStructsIO.hpp"

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
    if (c != d.exp)
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, LongLongIO&& d)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    long long value = 0;
    in >> value;

    std::string suffix;
    in >> suffix;
    if (suffix != "ll" && suffix != "LL")
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    d.ref = value;
    return in;
}

std::istream& operator>>(std::istream& in, ULongLongOctIO&& d)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    std::string token;
    in >> token;
    if (token.empty() || token[0] != '0')
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::istringstream iss(token);
    iss >> std::oct >> d.ref;

    if (!iss)
    {
        in.setstate(std::ios::failbit);
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

std::istream& operator>>(std::istream& in, LabelIO&& d)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    std::string value;
    if ((in >> StringIO{ value }) && value != d.exp)
    {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& d)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    DataStruct temp;
    std::string input;
    if (!std::getline(in, input, ')'))
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    input.push_back(')');

    std::istringstream record(input);
    record >> DelimiterIO{ '(' };

    bool read1 = false, read2 = false, read3 = false;
    while (record)
    {
        std::string label;
        if (!(record >> DelimiterIO{ ':' } >> LabelIO{ "key1" }))
        {
            record.clear();
        }
        else
        {
            record >> DelimiterIO{ ' ' } >> LongLongIO{ temp.key1 };
            read1 = true;
            continue;
        }

        if (!(record >> DelimiterIO{ ':' } >> LabelIO{ "key2" }))
        {
            record.clear();
        }
        else
        {
            record >> DelimiterIO{ ' ' } >> ULongLongOctIO{ temp.key2 };
            read2 = true;
            continue;
        }

        if (!(record >> DelimiterIO{ ':' } >> LabelIO{ "key3" })) {
            record.clear();
        }
        else
        {
            record >> DelimiterIO{ ' ' } >> StringIO{ temp.key3 };
            read3 = true;
            continue;
        }

        break;
    }

    if (!read1 || !read2 || !read3)
    {
        in.setstate(std::ios::failbit);
    }
    else
    {
        d = temp;
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& d)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }

    iofmtguard fmt(out);
    out << "(:key1 " << d.key1 << "ll"
        << ":key2 0" << std::oct << d.key2
        << ":key3 \"" << d.key3 << "\":)";
    return out;
}
