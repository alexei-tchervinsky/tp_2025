#include "DataStruct.hpp"
#include <sstream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <stdexcept>
namespace
{
    unsigned long long parseOct(const std::string& s)
    {
        if (s.empty() || !std::all_of(s.begin(), s.end(), [](char c){ return c>='0' && c<='7'; }))
            throw std::runtime_error("bad octal literal");
        return std::stoull(s, nullptr, 8);
    }
    double parseDbl(const std::string& s)
    {
        if (s.size()<2 || (s.back()!='d' && s.back()!='D'))
            throw std::runtime_error("bad double literal");
        return std::stod(s.substr(0, s.size()-1));
    }
}
bool operator<(const DataStruct& lhs, const DataStruct& rhs)
{
    if (lhs.key1!=rhs.key1) return lhs.key1<rhs.key1;
    if (lhs.key2!=rhs.key2) return lhs.key2<rhs.key2;
    return lhs.key3.size()<rhs.key3.size();
}
std::istream& operator>>(std::istream& in, DataStruct& ds)
{
    std::string line;
    while (std::getline(in,line))
    {
        try
        {
            std::istringstream src(line);
            char p,c; src>>p>>c; if(p!='('||c!=':') throw std::runtime_error("fmt");
            bool f1=false,f2=false,f3=false;
            while(src&&src.peek()!=')')
            {
                std::string key; src>>key;
                if(key=="key1")
                {
                    std::string tok; src>>tok; ds.key1=parseDbl(tok); f1=true;
                }
                else if(key=="key2")
                {
                    std::string tok; src>>tok; ds.key2=parseOct(tok); f2=true;
                }
                else if(key=="key3")
                {
                    char q; src>>q; if(q!='"') throw std::runtime_error("str");
                    std::getline(src,ds.key3,'"'); f3=true;
                }
                else throw std::runtime_error("key");

                char d; src>>d; if(d!=':') throw std::runtime_error("delim");
                src>>std::ws;
            }
            char cls; src>>cls; if(cls!=')'||!(f1&&f2&&f3)) throw std::runtime_error("close");
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
    out<<"(:key1 ";
    std::ostream::fmtflags f=out.flags();
    out<<std::setprecision(1)<<std::defaultfloat<<ds.key1<<'d';
    out.flags(f);
    out<<":key2 0"<<std::oct<<ds.key2<<std::dec;
    out<<":key3 \""<<ds.key3<<"\":)";
    return out;
}
