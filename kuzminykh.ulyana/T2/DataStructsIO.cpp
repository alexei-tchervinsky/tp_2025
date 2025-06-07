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
            std::cout << lab;
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

    DataStruct tmp;

    if (!(in >> DelimiterIO{ '(' })) {
        std::cerr << "Error: Missing opening '('\n";
        return in;
    }

    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
    while (in && in.peek() != ')')
    {

        if (!(in >> DelimiterIO{ ':' })) {

            break;
        }

        std::string key;
        if (!(in >> key)) {

            in.setstate(std::ios::failbit);
            break;
        }


        if (key == "key1" && !hasKey1)
        {
            if (!(in >> LongLongIO{ tmp.key1 })) {

                break;
            }
            hasKey1 = true;

        }
        else if (key == "key2" && !hasKey2)
        {
            if (!(in >> ULongLongOctIO{ tmp.key2 })) {

                break;
            }
            hasKey2 = true;

        }
        else if (key == "key3" && !hasKey3)
        {
            if (!(in >> StringIO{ tmp.key3 })) {

                break;
            }
            hasKey3 = true;


        }
        else if (key==")")
        {
            break;
        }
        else
        {

            std::string dummy;
            while (in && in.peek() != ':' && in.peek() != ')') {
                in >> dummy;
            }
        }
    }

    if (!(hasKey1 && hasKey2 && hasKey3)) {

        in.setstate(std::ios::failbit);
    }
    else {
        d = tmp;
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& d)
{
    std::ostream::sentry sentry(out);
    if (!sentry) return out;

    iofmtguard fmt(out);
    out << "(:key1 " << d.key1 << "ll";
    out << ":key2 " << std::showbase << std::oct << d.key2;
    out << ":key3 \"" << d.key3 << "\":)";
    return out;
}

bool compareDataStructs(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}
