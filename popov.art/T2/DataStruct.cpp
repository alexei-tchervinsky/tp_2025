#include "DataStruct.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <stdexcept>
bool operator<(const DataStruct& lhs, const DataStruct& rhs)
{
    if (lhs.key1 != rhs.key1) return lhs.key1 < rhs.key1;
    if (lhs.key2 != rhs.key2) return lhs.key2 < rhs.key2;
    return lhs.key3.size() < rhs.key3.size();
}
std::istream& operator>>(std::istream& in, DataStruct& ds)
{
    std::string line;
    while (std::getline(in, line))
    {
        try
        {
            DataStruct tmp;
            std::istringstream src(line);
            char p, c;
            src >> p >> c;
            if (p != '(' || c != ':') throw std::runtime_error("");
            bool f1 = false, f2 = false, f3 = false;
            while (src && src.peek() != ')')
            {
                std::string key;
                src >> key;
                if (key == "key1")
                {
                    std::string token; 
                    src >> token;
                    try {
                        if (!token.empty() && (token.back() == 'd' || token.back() == 'D')) {
                            tmp.key1 = std::stod(token.substr(0, token.size() - 1));
                        } else {
                            tmp.key1 = std::stod(token);
                        }
                        f1 = true;
                    } catch (...) {
                        throw std::runtime_error("");
                    }
                }
                else if (key == "key2")
                {
                    std::string token; 
                    src >> token;
                    try {
                        if (token.empty()) throw std::runtime_error("");
                        bool isOctal = true;
                        for (char ch : token) {
                            if (ch < '0' || ch > '7') {
                                isOctal = false;
                                break;
                            }
                        }
                        if (isOctal) {
                            tmp.key2 = std::stoull(token, nullptr, 8);
                        } else {
                            tmp.key2 = std::stoull(token);
                        }
                        f2 = true;
                    } catch (...) {
                        throw std::runtime_error("");
                    }
                }
                else if (key == "key3")
                {
                    char q; src >> q; if (q != '"') throw std::runtime_error("");
                    std::getline(src, tmp.key3, '"'); f3 = true;
                }
                else throw std::runtime_error("");
                char d; src >> d; if (d != ':') throw std::runtime_error("");
                src >> std::ws;
            }
            char cl; src >> cl;
            if (cl != ')' || !(f1 && f2 && f3)) throw std::runtime_error("");
            ds = std::move(tmp);
            return in;
        }
        catch (...) {}
    }
    in.setstate(std::ios::failbit);
    return in;
}
std::ostream& operator<<(std::ostream& out, const DataStruct& ds)
{
    out << "(:key1 ";
    std::ostream::fmtflags f = out.flags();
    out << std::setprecision(1) << std::defaultfloat << ds.key1 << 'd';
    out.flags(f);
    out << ":key2 0" << std::oct << ds.key2 << std::dec;
    out << ":key3 \"" << ds.key3 << "\":)";
    return out;
}
