#include "IO_Objects.hpp"

#include <iterator>
#include <algorithm>

namespace narumov {
    std::istream& operator>>(std::istream& is, LimitingSymbolIO&& ls) {
        std::istream::sentry sentry(is);
        if(!sentry) {
            return is;
        }
        char c;
        is >> c;
        if(is && (c != ls.symbol)) {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, LabelIO&& l) {
        std::istream::sentry sentry(is);
        if(!sentry) {
            return is;
        }
        std::string temp;
        std::copy_n(
            std::istream_iterator<char>(is),
            l.label.length(),
            std::back_inserter(temp)
        );
        if(is && (temp != l.label)) {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, ComplexIO&& c) {
        std::istream::sentry sentry(is);
        if(!sentry) {
            return is;
        }
        double real, imaginary;
        is >> LabelIO { "#c" } >> LimitingSymbolIO { '(' };
        is >> real >> imaginary;
        is >>  LimitingSymbolIO { ')' };
        c.ref = std::complex<double>(real, imaginary);
        return is;
    }

    std::istream& operator>>(std::istream& is, RationalIO&& r) {
        std::istream::sentry sentry(is);
        if(!sentry) {
            return is;
        }
        is >> LimitingSymbolIO { '(' };
        is >> LimitingSymbolIO { ':' } >> LimitingSymbolIO { 'N' } >> r.ref.first;
        is >> LimitingSymbolIO { ':' } >> LimitingSymbolIO { 'D' } >> r.ref.second;
        is >> LimitingSymbolIO { ':' } >> LimitingSymbolIO { ')' };
        return is;
    }

    std::istream& operator>>(std::istream& is, StringIO&& s) {
        std::istream::sentry sentry(is);
        if(!sentry) {
            return is;
        }
        return std::getline(is >> LimitingSymbolIO { '\"' }, s.ref, '\"');
    }
}
