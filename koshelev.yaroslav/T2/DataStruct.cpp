#include "DataStruct.h"
#include <sstream>
#include <cctype>

bool parseScientificDouble(const std::string& str, double& value) {
    std::istringstream iss(str);
    iss >> value;
    return !iss.fail() && iss.eof();
}

bool parseHexULL(const std::string& str, unsigned long long& value) {
    std::string s = str;
    if (s.size() > 1 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        s = s.substr(2);
    }
    
    std::istringstream iss(s);
    iss >> std::hex >> value;
    return !iss.fail() && iss.eof();
}
