#include "IO_Objects.hpp"

#include <sstream>
#include <iomanip>

namespace ponomarenko {

    std::istream& operator>>(std::istream& in, DelimiterIO&& d) {
        char ch;
        in >> std::ws >> ch;
        if (!in || ch != d.expected) in.setstate(std::ios::failbit);
        return in;
    }

    std::istream& operator>>(std::istream& in, LabelIO&& label) {
        std::string result;
        char ch;
        while (in.get(ch)) {
            if (ch == ' ') break;
            result += ch;
        }
        if (in) label.ref = result;
        else in.setstate(std::ios::failbit);
        return in;
    }

    std::istream& operator>>(std::istream& in, ULLLitIO&& u) {
        std::string str;
        in >> str;
        if (str.size() > 3 && (str.substr(str.size()-3) == "ull" || str.substr(str.size()-3) == "ULL")) {
            str = str.substr(0, str.size()-3);
            std::istringstream ss(str);
            ss >> u.ref;
            if (!ss) in.setstate(std::ios::failbit);
        } else {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, CharIO&& c) {
        char quote1, value, quote2;
        in >> quote1 >> value >> quote2;
        if (in && quote1 == ''' && quote2 == ''') c.ref = value;
        else in.setstate(std::ios::failbit);
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
        if (!in) in.setstate(std::ios::failbit);
        return in;
    }
}
