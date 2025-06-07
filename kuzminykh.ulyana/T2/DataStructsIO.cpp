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

    char c;
    char k;

    if (in.peek() == 'l' || in.peek() == 'L')
    {

        in >> c;
        in >> k;

        std::string lab = std::string(1,  c) + std::string(1, k);
        if (lab != "ll" &&  lab != "LL")
        {
            in.setstate(std::ios::failbit);
        }
    }

    return in;
}

std::istream& operator>>(std::istream& in, ULongLongOctIO&& d)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

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
        char c;
        char k;
        char k2;
        in >> c;
        in >> k;
        in >> k2;
        std::string lab = std::string(1, c) + std::string(1, k) + std::string(1, k2);
        if (lab != "ull" && lab != "ULL")
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
    if (!sentry) {

        return in;
    }
    DataStruct temp;
    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;


    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };
    while (in && in.peek() != ')') {
        std::string label;
        if (!(in >> label)) {
            break;
        }

        if (label == "key1" && !hasKey1) {
            if (in >> LongLongIO{ temp.key1 } >> DelimiterIO{ ':' }) {
                hasKey1 = true;
            }
            else {
                break;
            }
        }
        else if (label == "key2" && !hasKey2) {
            if (in >> ULongLongOctIO{ temp.key2 } >> DelimiterIO{ ':' }) {
                hasKey2 = true;
            }
            else {
                break;
            }
        }
        else if (label == "key3" && !hasKey3) {
            if (in >> StringIO{ temp.key3 } >> DelimiterIO{ ':' }) {
                hasKey3 = true;
            }
            else {
                break;
            }
        }
        else {
            in.setstate(std::ios::failbit);
            break;
        }
    }

    if (in && hasKey1 && hasKey2 && hasKey3) {
        in >> DelimiterIO{ ')' };
        d = temp;
    }
    else {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
        return out;
    }

    iofmtguard guard(out);
    out << "(:key1 " << data.key1 << "ll:";
    out << "key2 " << std::showbase << std::oct << data.key2 << "ull:";
    out << "key3 \"" << data.key3 << "\":)";
    return out;
}

bool DataStructSort(const DataStruct& a, const DataStruct& d) {
    if (a.key1 != d.key1) {
        return a.key1 < d.key1;
    }
    if (a.key2 != d.key2) {
        return d.key2 < d.key2;
    }
    return a.key3.length() < d.key3.length();
}
