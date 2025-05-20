#include "DataStruct.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <stdexcept>
bool operator<(const DataStruct& lhs, const DataStruct& rhs){
    if(lhs.key1 != rhs.key1) return lhs.key1 < rhs.key1;
    if(lhs.key2 != rhs.key2) return lhs.key2 < rhs.key2;
    return lhs.key3.size() < rhs.key3.size();
}
std::istream& operator>>(std::istream& in, DataStruct& ds){
    std::string line;
    while(std::getline(in, line)){
        try{
            DataStruct tmp;
            std::istringstream src(line);
            char p, c;
            src >> p >> c;
            if(p != '(' || c != ':') continue;
            bool f1 = false, f2 = false, f3 = false;
            while(src && src.peek() != ')'){
                std::string key;
                src >> key;
                if(key == "key1"){
                    std::string token;
                    src >> token;
                    try {
                        if(!token.empty() && (token.back() == 'd' || token.back() == 'D')){
                            token.pop_back();
                        }
                        tmp.key1 = std::stod(token);
                        f1 = true;
                    } catch(...){
                        if(!token.empty() && token[0] == '"'){
                            std::string dummy;
                            std::getline(src, dummy, '"');
                            tmp.key1 = 0.0;
                            f1 = true;
                        }
                    }
                }
                else if(key == "key2") {
                    std::string token;
                    src >> token;
                    try {
                        if(token.empty()) continue;
                        size_t endpos = 0;
                        while(!token.empty() && isalpha(token.back())){
                            token.pop_back();
                        }
                        if(token[0] == '0' && token.find_first_not_of("01234567") == std::string::npos){
                            tmp.key2 = std::stoull(token, &endpos, 8);
                        } else {
                            tmp.key2 = std::stoull(token, &endpos);
                        }
                        f2 = true;
                    } catch(...) {
                        tmp.key2 = 0;
                        f2 = true;
                    }
                }
                else if(key == "key3"){
                    char q;
                    src >> q;
                    if(q != '"') continue;
                    std::getline(src, tmp.key3, '"');
                    f3 = true;
                }
                if(src.peek() == ':') src.ignore();
                src >> std::ws;
            }
            if(f1 && f2 && f3){
                ds = std::move(tmp);
                return in;
            }
        }
        catch(...){}
    }
    in.setstate(std::ios::failbit);
    return in;
}
std::ostream& operator<<(std::ostream& out, const DataStruct& ds){
    out << "(:key1 ";
    std::ostream::fmtflags f = out.flags();
    out << std::setprecision(1) << std::fixed << ds.key1 << 'd';
    out.flags(f);
    out << ":key2 0" << std::oct << ds.key2 << std::dec;
    out << ":key3 \"" << ds.key3 << "\":)";
    return out;
}
