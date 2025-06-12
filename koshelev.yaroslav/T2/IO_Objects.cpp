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
            if (isdigit(c)) {
                numStr += c;
                hasDigit = true;
            }
            else if (c == '.' || c == 'e' || c == 'E') {
                numStr += c;
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

    std::istream& operator>>(std::istream& in, HexUllIO&& h) {
        std::string numStr;
        char c;
        in >> std::ws >> c;

        if (c == '0') {
            numStr += c;
            char next = in.peek();
            if (next == 'x' || next == 'X' || next == 'b' || next == 'B') {
                in.get(c);
                numStr += c;
            }
        } else if (isdigit(c)) {
            numStr += c;
        } else {
            in.setstate(std::ios::failbit);
            return in;
        }

        while (in.get(c)) {
            if (isxdigit(c)) {
                numStr += c;
            } else {
                in.unget();
                break;
            }
        }

        try {
            size_t pos = 0;
            h.ref = std::stoull(numStr, &pos, 0);
            if (pos != numStr.length()) {
                in.setstate(std::ios::failbit);
            }
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
        if (in.peek() == '"' || in.peek() == '\'' || in.peek() == '#') {
            in.setstate(std::ios::failbit);
            return in;
        }
        return in >> DoubleIO{k.ref};
    }
}
