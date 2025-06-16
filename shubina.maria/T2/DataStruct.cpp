#include "data_struct.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <iterator>

namespace shubina
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        char c;
        in >> c;
        if (in && c != dest.exp)
            in.setstate(std::ios::failbit);
        return in;
    }

    std::istream& operator>>(std::istream& in, CharIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        in >> DelimiterIO{'\''} >> dest.ref >> DelimiterIO{'\''};
        return in;
    }

    std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry) return in;

        std::string token;
        char c;
        while (in.get(c) && (std::isdigit(c) || c == 'u' || c == 'U' || c == 'l' || c == 'L'))
            token += c;
        in.putback(c);

        try
        {
            size_t pos = 0;
            dest.ref = std::stoull(token, &pos);
            if (pos < token.size())
            {
                while (pos < token.size() &&
                       (token[pos] == 'u' || token[pos] == 'U' ||
                        token[pos] == 'l' || token[pos] == 'L'))
                    ++pos;
                if (pos != token.size())
                    in.setstate(std::ios::failbit);
            }
        }
        catch (...) { in.setstate(std::ios::failbit); }

        return in;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry) return in;

        in >> DelimiterIO{'\"'};
        std::getline(in, dest.ref, '\"');
        return in;
    }

    std::istream& operator>>(std::istream& in, LabelIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry) return in;

        std::string actual;
        actual.resize(dest.exp.length());
        in.read(&actual[0], dest.exp.length());

        if (!in || actual != dest.exp)
            in.setstate(std::ios::failbit);

        return in;
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry) return in;

        DataStruct input;
        bool has_key1 = false, has_key2 = false, has_key3 = false;

        in >> DelimiterIO{'('} >> DelimiterIO{':'};

        while (in.peek() != ')' && in.peek() != EOF)
        {
            std::string field;
            if (!(in >> field)) break;

            if (field == "key1")
            {
                if (in >> CharIO{input.key1}) has_key1 = true;
                in >> DelimiterIO{':'};
            }
            else if (field == "key2")
            {
                if (in >> UnsignedLongLongIO{input.key2}) has_key2 = true;
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

        if (in.peek() == ')') in.ignore();

        if (has_key1 && has_key2 && has_key3)
            dest = input;
        else
            in.setstate(std::ios::failbit);

        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
    {
        std::ostream::sentry sentry(out);
        if (!sentry) return out;
        iofmtguard fmtguard(out);
        out << "(:key1 '" << dest.key1 << "'"
            << ":key2 " << dest.key2 << "ull"
            << ":key3 \"" << dest.key3 << "\":)";
        return out;
    }

    iofmtguard::iofmtguard(std::basic_ios<char>& s) :
        s_(s), width_(s.width()), fill_(s.fill()),
        precision_(s.precision()), fmt_(s.flags()) {}

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

    std::vector<DataStruct> readDataStructs(std::istream& in)
    {
        std::vector<DataStruct> result;
        std::copy(
            std::istream_iterator<DataStruct>(in),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(result)
        );
        return result;
    }

    void writeDataStructs(const std::vector<DataStruct>& data, std::ostream& out)
    {
        std::copy(
            data.begin(),
            data.end(),
            std::ostream_iterator<DataStruct>(out, "\n")
        );
    }
}

