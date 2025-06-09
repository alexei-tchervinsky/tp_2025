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

        bool key1 = false;
        bool key2 = false;
        bool key3 = false;

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
                key1 = true;
                break;
            }
            case Char:
            {
                in >> CharIO{ tmp.key2_ };
                key2 = true;
                break;
            }
            case STRING:
            {
                in >> StringIO{ tmp.key3_ };
                key3 = true;
                break;
            }
            default:
                break;
            }
        }
        in >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
        if (in && key1 && key2 && key3) {
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
        std::string label;
        std::copy_n(std::istream_iterator<char>(in), dest.label.length(), std::back_inserter(label));
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

    std::istream& operator>>(std::istream& in, CharIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> DelimiterIO{ '\'' } >> dest.ref >> DelimiterIO{ '\'' };
    }

    std::istream& operator>>(std::istream& in, LongLongIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        in >> dest.ref;

        std::string suffix;
        std::copy_n(std::istream_iterator<char>(in), 2, std::back_inserter(suffix));
        if (in && (suffix != "ll" && suffix != "LL"))
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
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
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
