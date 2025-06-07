#include "IO_Objects.h"
#include "DataStruct.h"
#include <sstream>
#include <iomanip>
#include <string>

std::istream& operator>>(std::istream& in, DataStruct& data) {
    DataStruct temp;
    std::string line;

    if (!std::getline(in, line)) {
        return in;
    }

    if (line.empty() || line.front() != '(' || line.back() != ')') {
        in.setstate(std::ios::failbit);
        return in;
    }

    line = line.substr(1, line.size() - 2);
    std::istringstream iss(line);
    std::string token;
    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

    while (iss >> token) {
        if (token == ":key1") {
            std::string value;
            iss >> value;
            if (!parseScientificDouble(value, temp.key1)) {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey1 = true;
        } else if (token == ":key2") {
            std::string value;
            iss >> value;
            if (!parseHexULL(value, temp.key2)) {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey2 = true;
        } else if (token == ":key3") {
            iss >> std::quoted(temp.key3);
            hasKey3 = true;
        }
    }

    if (!hasKey1 || !hasKey2 || !hasKey3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    data = temp;
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 " << std::scientific << std::setprecision(6) << data.key1
        << ":key2 " << std::hex << std::uppercase << data.key2
        << ":key3 " << std::quoted(data.key3) << ":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}
