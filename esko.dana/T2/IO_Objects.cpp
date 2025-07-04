// IO_Objects.cpp
#include "IO_Objects.h"
#include <iterator>
#include <algorithm>

namespace Data {
    std::istream& operator>>(std::istream& is, LimitingSymbolIO&& ls) {
        std::istream::sentry sentry(is);
        if (!sentry) {
            return is;
        }
        char c;
        is >> c;
        if (is && (c != ls.symbol)) {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, LabelIO&& l) {
        std::istream::sentry sentry(is);
        if (!sentry) {
            return is;
        }
        std::string temp;
        std::copy_n(
            std::istream_iterator<char>(is),
            l.label.length(),
            std::back_inserter(temp)
        );
        if (is && (temp != l.label)) {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, SignedLongLongIO&& sll) {
        std::istream::sentry sentry(is);
        if (!sentry) {
            return is;
        }
        is >> sll.ref;
        std::string suffix;
        std::copy_n(
            std::istream_iterator<char>(is),
            3,
            std::back_inserter(suffix)
        );
        if (is && (suffix != "sll" && suffix != "SLL")) {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, DoubleIO&& d) {
        std::istream::sentry sentry(is);
        if (!sentry) {
            return is;
        }
        is >> d.ref;
        char suffix;
        is >> suffix;
        if (is && (suffix != 'd' && suffix != 'D')) {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, StringIO&& s) {
        std::istream::sentry sentry(is);
        if (!sentry) {
            return is;
        }
        return std::getline(is >> LimitingSymbolIO{ '\"' }, s.ref, '\"');
    }
}
