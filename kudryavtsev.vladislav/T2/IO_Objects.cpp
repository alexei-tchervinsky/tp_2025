#include "IO_Objects.hpp"

namespace tarasov {
    char readChar(std::istream& in) {
        char c = 0;
        in >> c;
        return c;
    }

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
        const std::istream::sentry sentry(in);
        if (!sentry) return in;

        char c = 0;
        in >> std::ws;
        if (!in) return in;

        in >> c;

        if (in && c != dest.exp) {
            in.setstate(std::ios::failbit);
        }

        return in;
    }

    std::istream& operator>>(std::istream& in, DoubleSciIO&& dest) {
        const std::istream::sentry sentry(in);
        if (!sentry) return in;

        return in >> std::scientific >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, CharLitIO&& dest) {
        const std::istream::sentry sentry(in);
        if (!sentry) return in;

        char c;
        if (in >> DelimiterIO{'\''} >> c >> DelimiterIO{'\''}) {
            dest.ref = c;
        } else {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, StringLitIO&& dest) {
        const std::istream::sentry sentry(in);
        if (!sentry) return in;

        return in >> std::quoted(dest.ref);
    }
}

