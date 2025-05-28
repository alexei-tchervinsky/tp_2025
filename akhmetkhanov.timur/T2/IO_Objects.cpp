#include "IO_Objects.hpp"
#include <iterator>
#include <algorithm>
#include <cctype>
#include <sstream>

namespace nspace {
    std::istream& operator>>(std::istream& is, DelimiterIO&& dlim) {
        char c;
        is >> std::ws;
        if (is >> c && c != dlim.exp) {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, LabelIO&& l) {
        std::string temp;

        for (size_t i = 0; i < l.label.size(); ++i) {
            char c;
            if (!(is >> c)) {
                is.setstate(std::ios::failbit);
                return is;
            }
            temp += c;
        }

        if (temp != l.label) {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, ULLHexIO&& ullhex) {
        char c1, c2;
        is >> c1 >> c2;
        if (c1 != '0' || (c2 != 'x' && c2 != 'X')) {
            is.setstate(std::ios::failbit);
        } else {
            is >> std::hex >> ullhex.ref >> std::dec;
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, DoubleSciIO&& dsci) {
        is >> dsci.ref;
        return is;
    }

    std::istream& operator>>(std::istream& is, StringIO&& s) {
        char quote;
        is >> quote;
        if (quote != '\"') {
            is.setstate(std::ios::failbit);
            return is;
        }

        std::getline(is, s.ref, '\"');
        return is;
    }
}
