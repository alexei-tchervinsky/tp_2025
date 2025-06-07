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
    char c;
    in >> c;
    if (in && (c != d.exp))
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



    if (in.peek() == 'l' || in.peek() == 'L') {
        char first = in.get();
        if (in.peek() == first) {
            in.get();
        }
        else {
            in.unget();
            in.setstate(std::ios::failbit);
        }
    }
    else {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::istream& operator>>(std::istream& in, ULongLongOctIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    char c;
    if (!(in >> c) || c != '0') {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (isdigit(in.peek())) {
        in >> dest.ref;
    }
    else {
        dest.ref = 0;
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

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    DataStruct input;
    using sep = DelimiterIO;
    using oct = ULongLongOctIO;
    using ll = LongLongIO;
    using str = StringIO;
    in >> sep{ '(' } >> sep{ ':' };
    bool isKey1 = false, isKey2 = false, isKey3 = false;
    while (in.peek() != ')') {
        std::string keyLabel;
        if (!(in >> keyLabel)) {
            break;
        }
        if (keyLabel == "key1" && !isKey1) {
            in >> ll{ input.key1 } >> sep{ ':' };
            if (!in) return in;
            isKey1 = true;
        }
        else if (keyLabel == "key2" && !isKey2) {
            in >> oct{ input.key2 } >> sep{ ':' };
            if (!in) return in;
            isKey2 = true;
        }
        else if (keyLabel == "key3" && !isKey3) {
            in >> str{ input.key3 } >> sep{ ':' };
            if (!in) return in;
            isKey3 = true;
        }
        else {
            in.setstate(std::ios::failbit);
            break;
        }
    }
    if (in && isKey1 && isKey2 && isKey3) {
        in >> sep{ ')' };
        if (!in) return in;
        dest = input;
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
    out << "key2 " << '0' << data.key2 << "ull:";
    out << "key3 \"" << data.key3 << "\":)";
    return out;
}

bool DataStructSort(const DataStruct& a, const DataStruct& d) {
    if (a.key1 != d.key1) {
        return a.key1 < d.key1;
    }
    if (a.key2 != d.key2) {
        return a.key2 < d.key2;
    }
    return a.key3.length() < d.key3.length();
}
