#include "DataStruct.h"
#include <sstream>
#include <cmath>

bool parseComplex(const std::string& str, std::complex<double>& value) {
    if (str.size() < 5 || str.substr(0, 3) != "#c(" || str.back() != ')') {
        return false;
    }

    std::istringstream iss(str.substr(3, str.size() - 4));
    double real, imag;
    if (!(iss >> real >> imag)) {
        return false;
    }

    value = std::complex<double>(real, imag);
    return true;
}

bool parseRational(const std::string& str, std::pair<long long, unsigned long long>& value) {
    if (str.size() < 7 || str.substr(0, 2) != "(:") {
        return false;
    }

    size_t end = str.rfind(":)");
    if (end == std::string::npos) {
        return false;
    }

    std::istringstream iss(str.substr(2, end - 2));
    std::string token;
    bool hasN = false, hasD = false;

    while (iss >> token) {
        if (token == ":N") {
            if (!(iss >> value.first)) {
                return false;
            }
            hasN = true;
        } else if (token == ":D") {
            if (!(iss >> value.second)) {
                return false;
            }
            hasD = true;
        }
    }

    return hasN && hasD;
}
