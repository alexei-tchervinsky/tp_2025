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
    /*
    std::istream& operator>>(std::istream& in, LabelIO&& dest) {
        const std::istream::sentry sentry(in);
        if (!sentry) return in;

        std::string read_str;
        char c;

        while (in.get(c) && !std::isspace(c) && c != ':' && c != ')') {
            read_str += c;
        }

        if (in && !std::isspace(c)) {
            in.putback(c);
        }

        if (read_str != dest.exp) {
            in.setstate(std::ios::failbit);
        }

        return in;
    }
    */
    std::istream& operator>>(std::istream& in, DoubleSciIO&& dest) {
        const std::istream::sentry sentry(in);
        if (!sentry) return in;

        return in >> std::scientific >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, CharLitIO&& dest) {
        const std::istream::sentry sentry(in);
        if (!sentry) return in;

        char c1, c2, c3;
        in >> c1 >> c2 >> c3;

        if (in && c1 == '\'' && c3 == '\'') {
            dest.ref = c2;
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
