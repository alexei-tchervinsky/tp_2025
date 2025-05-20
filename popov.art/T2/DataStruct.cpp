#include "DataStruct.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <stdexcept>
namespace
{
    double parseDbl(const std::string& s)
    {
        if (s.size() < 2 || (s.back() != 'd' && s.back() != 'D'))
            throw std::runtime_error("bad double literal");
        return std::stod(s.substr(0, s.size() - 1));
    }
    unsigned long long parseOct(const std::string& s)
    {
        if (s.empty() || !std::all_of(s.begin(), s.end(), [](char c){ return c >= '0' && c <= '7'; }))
            throw std::runtime_error("bad octal literal");
        return std::stoull(s, nullptr, 8);
    }
}
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
            if (p != '(' || c != ':') throw std::runtime_error("no opening");
            bool f1 = false, f2 = false, f3 = false;
            while (src && src.peek() != ')')
            {
                std::string key;
                src >> key;
                if (key == "key1")
                {
                    std::string token; src >> token;
                    tmp.key1 = parseDbl(token); f1 = true;
                }
                else if (key == "key2")
                {
                    std::string token;
                    src >> token;
                    tmp.key2 = parseOct(token);
                    f2 = true;
                }
                else if (key == "key3")
                {
                    char q; src >> q; if (q != '"') throw std::runtime_error("no quote");
                    std::getline(src, tmp.key3, '"'); f3 = true;
                }
                else throw std::runtime_error("bad key");
                char d; src >> d; if (d != ':') throw std::runtime_error("no colon");
                src >> std::ws;
            }
            char cl; src >> cl;
            if (cl != ')' || !(f1 && f2 && f3)) throw std::runtime_error("bad closing");
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
