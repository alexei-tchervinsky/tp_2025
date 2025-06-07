#include "DataStruct.h"
#include <sstream>

bool parseScientificDouble(const std::string& str, double& value) {
    std::istringstream iss(str);
    iss >> value;
    return !iss.fail();
}

bool parseHexULL(const std::string& str, unsigned long long& value) {
    std::istringstream iss(str);
    iss >> std::hex >> value;
    return !iss.fail();
}
