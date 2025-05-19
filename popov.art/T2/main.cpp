#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <stdexcept>
struct DataStruct
{
    double              key1;   // DBL LIT
    unsigned long long  key2;   // ULL OCT
    std::string         key3;
};
static bool cmpData(const DataStruct& lhs, const DataStruct& rhs)
{
    if (lhs.key1 != rhs.key1)                     return lhs.key1 < rhs.key1;
    if (lhs.key2 != rhs.key2)                     return lhs.key2 < rhs.key2;
                                                   return lhs.key3.size() < rhs.key3.size();
}
namespace detail
{
    unsigned long long parseOct(const std::string& s)
    {
        if (s.empty() || !std::all_of(s.begin(), s.end(),
                                      [](char c){ return c >= '0' && c <= '7'; }))
            throw std::runtime_error("bad octal literal");
        return std::stoull(s, nullptr, 8);
    }
    double parseDbl(const std::string& s)
    {
        if (s.size() < 2 || (s.back()!='d' && s.back()!='D'))
            throw std::runtime_error("bad double literal");
        return std::stod(s.substr(0, s.size()-1));
    }
}
std::istream& operator>>(std::istream& in, DataStruct& ds)
{
    std::string line;
    while (std::getline(in, line))
    {
        try
        {
            std::istringstream src(line);
            char paren{}, colon{};
            src >> paren >> colon;
            if (paren!='(' || colon!=':')                     throw std::runtime_error("no opening");
            bool have1=false, have2=false, have3=false;
            while (src && src.peek()!=')')
            {
                std::string keyName;          src >> keyName;
                if      (keyName=="key1")
                {
                    std::string token;        src >> token;
                    ds.key1 = detail::parseDbl(token);
                    have1 = true;
                }
                else if (keyName=="key2")
                {
                    std::string token;        src >> token;
                    ds.key2 = detail::parseOct(token);
                    have2 = true;
                }
                else if (keyName=="key3")
                {
                    char quote;              src >> quote;
                    if (quote!='"')                           throw std::runtime_error("no quote");
                    std::getline(src, ds.key3, '"');
                    have3 = true;
                }
                else                                            throw std::runtime_error("unknown key");
                char delim;                    src >> delim;
                if (delim!=':')                                throw std::runtime_error("no colon");
                src >> std::ws;
            }
            char closer{};                      src >> closer;
            if (closer!=')' || !(have1&&have2&&have3))
                throw std::runtime_error("bad closing");
            return in;
        }
        catch(...)
        {
        }
    }
    in.setstate(std::ios::failbit);
    return in;
}
std::ostream& operator<<(std::ostream& out, const DataStruct& ds)
{
    out << "(:key1 ";
    {
        std::ostream::fmtflags old = out.flags();       // сохраняем флаги
        out << std::setprecision(1) << std::defaultfloat << ds.key1 << 'd';
        out.flags(old);                                 // вернули флаги
    }

    out << ":key2 0" << std::oct << ds.key2 << std::dec;
    out << ":key3 \"" << ds.key3 << "\":)";

    return out;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::vector<DataStruct> vec;
    std::copy(std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(vec));
    std::sort(vec.begin(), vec.end(), cmpData);
    std::copy(vec.begin(), vec.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));
    return 0;
}
