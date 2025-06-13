#include "IO_Objects.hpp"
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cmath>

namespace koshelev {
    std::istream& operator>>(std::istream& in, DelimiterIO&& d) {
        char ch;
        in >> std::ws >> ch;
        if (!in || ch != d.expected) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, LabelIO&& label) {
        std::string result;
        char ch;
        while (in.get(ch)) {
            if (ch == ' ') break;
            result += ch;
        }
        if (in) {
            label.ref = result;
        } else {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, StringIO&& s) {
        char quote;
        in >> std::ws >> quote;
        if (quote != '"') {
            in.setstate(std::ios::failbit);
            return in;
        }
        std::getline(in, s.ref, '"');
        if (!in) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, ScientificIO&& sci) {
        double value;
        in >> value;
        if (!in || !(std::isfinite(value))) {
            in.setstate(std::ios::failbit);
            return in;
        }
        double absValue = std::abs(value);
        if (absValue == 0.0 || absValue >= 10.0 || absValue < 1.0) {
            in.setstate(std::ios::failbit);
            return in;
        }
        sci.ref = value;
        return in;
    }

    std::istream& operator>>(std::istream& in, HexIO&& hex) {
        std::string str;
        in >> str;
        if (str.size() < 3 || (str.substr(0, 2) != "0x" && str.substr(0, 2) != "0X")) {
            in.setstate(std::ios::failbit);
            return in;
        }
        try {
            hex.ref = std::stoull(str, nullptr, 16);
        } catch (...) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
}
