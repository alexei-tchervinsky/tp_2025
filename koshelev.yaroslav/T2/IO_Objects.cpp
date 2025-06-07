#include "IO_Objects.h"
#include "DataStruct.h"
#include "iofmtguard.h"
#include <sstream>
#include <iomanip>
#include <string>

std::istream& operator>>(std::istream& in, DataStruct& data) {
    DataStruct temp;
    std::string line;

    if (!std::getline(in, line)) {
        return in;
    }

    // Trim whitespace
    line.erase(0, line.find_first_not_of(" \t"));
    line.erase(line.find_last_not_of(" \t") + 1);

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
            if (iss >> value) {
                if (!parseScientificDouble(value, temp.key1)) {
                    in.setstate(std::ios::failbit);
                    return in;
                }
                hasKey1 = true;
            }
        } 
        else if (token == ":key2") {
            std::string value;
            if (iss >> value) {
                if (!parseHexULL(value, temp.key2)) {
                    in.setstate(std::ios::failbit);
                    return in;
                }
                hasKey2 = true;
            }
        } 
        else if (token == ":key3") {
            if (iss >> std::quoted(temp.key3)) {
                hasKey3 = true;
            }
        }
    }

    if (!(hasKey1 && hasKey2 && hasKey3)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    data = temp;
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    iofmtguard guard(out);
    out << "(:key1 " << std::scientific << std::uppercase << std::setprecision(1) << data.key1
        << " :key2 0x" << std::hex << data.key2
        << " :key3 " << std::quoted(data.key3) << ":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}
