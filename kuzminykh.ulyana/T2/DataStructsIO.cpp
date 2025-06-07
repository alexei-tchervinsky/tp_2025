#include "DataStructsIO.h"
#include <iomanip>

namespace kuzminykh
{
    std::ostream& operator<<(std::ostream& os, const DataStruct& ds)
    {
        std::ostream::sentry sentry(os);
        if (!sentry)
        {
            return os;
        }
        os << "(:key1 ";
        os << ds.key1_ << "ll";
        os << ":key2 " << ds.key2_;
        os << ":key3 \"";
        os << ds.key3_;
        os << "\":)";
        return os;
    }


    std::istream& operator>>(std::istream& in, DataStruct& ds)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct tmp;
        in >> DelimiterIO{ '(' };
        for (std::size_t i = 0; i < 3; i++)
        {
            short number = 0;

            in >> DelimiterIO{ ':' } >> LabelIO{ "key" } >> number;

            switch (number)
            {
            case LongLong:
            {
                in >> LongLongIO{ tmp.key1_ };
                break;
            }
            case OCT:
            {
                in >> OctUnsignedLongLongIO{ tmp.key2_ };
                break;
            }
            case STRING:
            {
                in >> StringIO{ tmp.key3_ };
                break;
            }
            }
        }
        in >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
        if (in) {
            ds = tmp;
        }
        return in;
    }

    bool compare(const DataStruct& a, const DataStruct& b)
    {
        if (a.key1_ != b.key1_)
        {
            return a.key1_ < b.key1_;
        }
        if (a.key2_ != b.key2_)
        {
            return a.key2_ < b.key2_;
        }
        return a.key3_.length() < b.key3_.length();
    }

    std::istream& operator>>(std::istream& in, LabelIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string label = "";
        for (std::size_t i = 0; i < dest.label.length(); ++i)
        {
            label += tolower(in.get());
        }
        if (in && (label != dest.label))
        {
            in.setstate(std::ios_base::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        char c;
        in >> c;
        if (in && (c != dest.delimiter))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, OctUnsignedLongLongIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        unsigned long long tmp;
        in >> tmp;
        for (char c : std::to_string(tmp))
        {
            if (c > '7')
            {
                in.setstate(std::ios_base::failbit);
                return in;
            }
        }
        dest.ref = tmp;
        in >> LabelIO{ "ull" };
        return in;
    }
    iofmtguard::iofmtguard(std::basic_ios<char>& s) :
        s_(s),
        width_(s.width()),
        fill_(s.fill()),
        precision_(s.precision()),
        fmt_(s.flags())
    {}

    iofmtguard::~iofmtguard() {
        s_.width(width_);
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }
}
