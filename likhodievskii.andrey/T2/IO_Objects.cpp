//
// Created by jdh99 on 17.04.2025.
//

#include "IO_Objects.hpp"

namespace likhodievskii {
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

    std::istream &operator>>(std::istream &in, HexUnsignedLongLongIO &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        in >> DelimiterIO{'0'};
        if (in.peek() == 'X') {
            in >> DelimiterIO{'X'};
        } else {
            in >> DelimiterIO{'x'};
        }
        in >> std::hex >> dest.ref;
        return in;
    }


    std::istream &operator>>(std::istream &in, StringIO &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
    }


    std::istream &operator>>(std::istream &in, ComplexDoubleIO &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        double real, imag;
        in >> DelimiterIO{'#'} >> DelimiterIO{'c'} >> DelimiterIO{'('};
        in >> real >> imag;
        in >> DelimiterIO{')'};
        dest.ref = std::complex<double>(real, imag);
        return in;
    }
}
