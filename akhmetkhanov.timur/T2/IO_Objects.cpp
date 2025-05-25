#include "IO_Objects.hpp"
#include <iterator>
#include <algorithm>
#include <cctype>

namespace nspace {
    std::istream& operator>>(std::istream& is, DelimiterIO&& dlim) {
        char c;
        if (is >> c && c != dlim.exp) is.setstate(std::ios::failbit);
        return is;
    }

    std::istream& operator>>(std::istream& is, LabelIO&& l) {
        std::string temp(l.label.size(), '\0');
        std::copy_n(std::istream_iterator<char>(is), l.label.size(), temp.begin());
        if (temp != l.label) is.setstate(std::ios::failbit);
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
        return std::getline(is >> DelimiterIO{ '\"' }, s.ref, '\"');
    }
}
