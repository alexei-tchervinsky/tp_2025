#include "IO_Objects.hpp"
#include <cctype>

namespace nspace {

std::istream& operator>>(std::istream& is, DelimiterIO&& d) {
    char c;
    if (is >> c && c != d.exp) is.setstate(std::ios::failbit);
    return is;
}

std::istream& operator>>(std::istream& is, LabelIO&& l) {
    for (char e : l.label) {
        char c;
        if (!is.get(c) || c != e) { is.setstate(std::ios::failbit); break; }
    }
    return is;
}

std::istream& operator>>(std::istream& is, ULLHexIO&& u) {
    char c1, c2;
    is >> c1 >> c2;
    if (!is || c1 != '0' || (c2 != 'x' && c2 != 'X')) {
        is.setstate(std::ios::failbit);
    } else {
        is >> std::hex >> u.ref >> std::dec;
    }
    return is;
}

std::istream& operator>>(std::istream& is, DoubleSciIO&& d) {
    is >> d.ref;
    return is;
}

std::istream& operator>>(std::istream& is, StringIO&& s) {
    return std::getline(is >> DelimiterIO{'"'}, s.ref, '"');
}

}
