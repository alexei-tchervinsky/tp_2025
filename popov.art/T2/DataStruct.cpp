#include "DataStruct.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <stdexcept>
bool operator<(const DataStruct& lhs, const DataStruct& rhs) {
    if (lhs.key1 != rhs.key1) return lhs.key1 < rhs.key1;
    if (lhs.key2 != rhs.key2) return lhs.key2 < rhs.key2;
    return lhs.key3.size() < rhs.key3.size();
}
std::istream& operator>>(std::istream& in, DataStruct& ds) {
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        try {
            DataStruct tmp;
            std::istringstream src(line);
            char p, c;
            if (!(src >> p >> c) || p != '(' || c != ':') continue;
            bool f1 = false, f2 = false, f3 = false;
            while (src && src.peek() != ')') {
                std::string key;
                if (!(src >> key)) break;
                if (key == "key1") {
                    std::string token;
                    if (!(src >> token)) break;
                    try {
                        if (!token.empty() && (token.back() == 'd' || token.back() == 'D')) {
                            token.pop_back();
                        }
                        tmp.key1 = std::stod(token);
                        f1 = true;
                    } catch (...) {
                        tmp.key1 = 0.0;
                        f1 = true;
                    }
                }
                else if (key == "key2") {
                    std::string token;
                    if (!(src >> token)) break;
                    try {
                        if (token.empty()) {
                            tmp.key2 = 0;
                            f2 = true;
                            continue;
                        }
                        while (!token.empty() && isalpha(token.back())) {
                            token.pop_back();
                        }
                        if (token.empty()) {
                            tmp.key2 = 0;
                            f2 = true;
                            continue;
                        }
                        tmp.key2 = std::stoull(token);
                        f2 = true;
                    } catch (...) {
                        tmp.key2 = 0;
                        f2 = true;
                    }
                }
                else if (key == "key3") {
                    char q;
                    if (!(src >> q) || q != '"') continue;
                    std::getline(src, tmp.key3, '"');
                    f3 = true;
                }
                if (src.peek() == ':') src.ignore();
            }
            if (f1 && f2 && f3) {
                ds = std::move(tmp);
                return in;
            }
        } catch (...) {}
    }
    in.setstate(std::ios::failbit);
    return in;
}
std::ostream& operator<<(std::ostream& out, const DataStruct& ds) {
    out << "(:key1 ";
    std::ostream::fmtflags f = out.flags();
    out << std::setprecision(1) << std::fixed << ds.key1 << 'd';
    out.flags(f);
    out << ":key2 0" << std::oct << ds.key2 << std::dec;
    out << ":key3 \"" << ds.key3 << "\":)";
    return out;
}
