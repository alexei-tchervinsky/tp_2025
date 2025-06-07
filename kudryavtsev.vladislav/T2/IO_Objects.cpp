#include "IO_Objects.hpp"

#include <iterator>
#include <algorithm>

namespace myspace {
    std::istream& operator>>(std::istream& is, LimitingSymbolIO&& ls) {
        std::istream::sentry sentry(is);
        if(!sentry) return is;
        char c;
        is >> c;
        if(is and (c != ls.symbol)) is.setstate(std::ios::failbit);
        return is;
    }

    std::istream& operator>>(std::istream& is, LabelIO&& l) {
        std::istream::sentry sentry(is);
        if(!sentry) return is;
        std::string temp;
        std::copy_n(std::istream_iterator<char>(is), l.label.length(), std::back_inserter(temp));
        if(is and (temp != l.label)) is.setstate(std::ios::failbit);
        return is;
    }

    std::istream& operator>>(std::istream& is, ComplexIO&& c) {
        std::istream::sentry sentry(is);
        if(!sentry) return is;
        double real, imag;
        is >> LabelIO{"#c"} >> LimitingSymbolIO{'('};
        is >> real >> imag;
        is >> LimitingSymbolIO{')'};
        c.ref = std::complex<double>(real, imag);
        return is;
    }

    std::istream& operator>>(std::istream& is, BinaryIO&& r) {
        std::istream::sentry sentry(is);
        if(!sentry) return is;
        is >> r.ref >> LimitingSymbolIO{':'};
        return is;
    }

    std::istream& operator>>(std::istream& is, StringIO&& s) {
        std::istream::sentry sentry(is);
        if(!sentry) return is;
        return std::getline(is >> LimitingSymbolIO{'\"'}, s.ref, '\"');
    }
}