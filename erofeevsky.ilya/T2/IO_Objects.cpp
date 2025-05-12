#include "IO_Objects.hpp"
#include <iterator>
#include <algorithm>

namespace erofick {
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

    std::istream& operator>>(std::istream& is, LongLongIO&& ll) {
        std::istream::sentry sentry(is);
        if (!sentry) {
            return is;
        }
        is >> ll.ref;
        std::string suffix;
        std::copy_n(
            std::istream_iterator<char>(is),
            2,
            std::back_inserter(suffix)
        );
        if (is && (suffix != "ll" && suffix != "LL")) {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, CharIO&& c) {
        std::istream::sentry sentry(is);
        if (!sentry) {
            return is;
        }
        is >> LimitingSymbolIO{ '\'' } >> c.ref >> LimitingSymbolIO{ '\'' };
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