#include "IO_Objects.hpp"

namespace tarasenko {
    std::istream &operator>>(std::istream &in, LabelIO &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        std::string label = "";
        for (std::size_t i = 0; i < dest.label.length(); ++i) {
            label += in.get();
        }
        if (in && (label != dest.label)) {
            in.setstate(std::ios_base::failbit);
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, DelimiterIO &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        char c;
        in >> c;
        if (in && (c != dest.delimiter)) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, Oct_IO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c;
        if (!(in >> c) || c != '0')
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (isdigit(in.peek())) {
            in >> dest.ref;
        }
        else
        {
            dest.ref = 0;
        }

        return in;
    }

    std::istream& operator>>(std::istream& in, Char_IO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> DelimiterIO{ '\'' } >> dest.ref >> DelimiterIO{ '\'' };
    }

    std::istream& operator>>(std::istream& in, String_IO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    std::istream& operator>>(std::istream& in, Char_IO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> DelimiterIO{ '\'' } >> dest.ref >> DelimiterIO{ '\'' };
    }
}
