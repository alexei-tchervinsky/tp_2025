#include "IO_Objects.hpp"
#include <iomanip>
#include <sstream>
#include <cctype>

namespace solution {
    std::istream& operator>>(std::istream& in, DelimiterIO&& d) {
        char c;
        in >> std::ws >> c;
        if (!in || c != d.expected) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, LabelIO&& l) {
        l.ref.clear();
        char c;
        while (in.get(c)) {
            if (c == ' ' || c == ':') {
                in.unget();
                break;
            }
            l.ref += c;
        }
        if (l.ref.empty()) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

std::istream& operator>>(std::istream& in, DoubleIO&& d) {
    std::string numStr;
    char c;
    bool hasDigit = false;

    if (in.peek() == '+' || in.peek() == '-') {
        in.get(c);
        numStr += c;
    }

    while (in.get(c)) {
        if (std::isdigit(c)) {
            numStr += c;
            hasDigit = true;
        }
        else if (c == '.' || c == 'e' || c == 'E') {
            numStr += c;
        }
        else if (c == 'd' || c == 'D') {
            break;
        }
        else {
            in.unget();
            break;
        }
    }

    if (!hasDigit) {
        in.setstate(std::ios::failbit);
        return in;
    }

    try {
        d.ref = std::stod(numStr);
    } catch (...) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

    std::istream& operator>>(std::istream& in, StringIO&& s) {
        in >> std::ws;
        char quote;
        in.get(quote);
        if (quote != '"') {
            in.setstate(std::ios::failbit);
            return in;
        }
        std::getline(in, s.ref, '"');
        return in;
    }

    std::istream& operator>>(std::istream& in, Key1IO&& k) {
        in >> std::ws;
        char c = in.peek();
        if (c == '"' || c == '\'' || c == '#') {
            in.setstate(std::ios::failbit);
            return in;
        }
        return in >> DoubleIO{k.ref};
    }
}
