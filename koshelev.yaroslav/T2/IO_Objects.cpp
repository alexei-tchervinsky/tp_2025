#include "IO_Objects.hpp"
#include <iomanip>
#include <sstream>
#include <cctype>

namespace solution {

    std::istream& operator>>(std::istream& in, DelimiterIO&& d) {
        char c;
        in >> c;
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
        in >> c;

        if (c == '0') {
            numStr += c;
            char next = in.peek();
            if (next == 'x' || next == 'X') {
                in.get(c);
                numStr += c;
            } else {
                h.ref = 0;
                return in;
            }
        } else {
            in.setstate(std::ios::failbit);
            return in;
        }

        bool hasDigit = false;
        while (in.get(c)) {
            if (isxdigit(c)) {
                numStr += c;
                hasDigit = true;
            } else {
                in.unget();
                break;
            }
        }

        if (!hasDigit) {
            in.setstate(std::ios::failbit);
            return in;
        }

        try {
            h.ref = std::stoull(numStr, nullptr, 16);
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
}
