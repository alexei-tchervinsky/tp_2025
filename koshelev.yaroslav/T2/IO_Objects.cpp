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
                if (!parseComplex(value, temp.key1)) {
                    in.setstate(std::ios::failbit);
                    return in;
                }
                hasKey1 = true;
            }
        }
        else if (token == ":key2") {
            std::string value;
            if (iss >> value) {
                if (!parseRational(value, temp.key2)) {
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
    out << "(:key1 #c(" << std::fixed << std::setprecision(1)
        << data.key1.real() << " " << data.key1.imag() << ")"
        << " :key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)"
        << " :key3 " << std::quoted(data.key3) << ":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    // Compare by complex number magnitude
    double magA = std::abs(a.key1);
    double magB = std::abs(b.key1);
    if (magA != magB) return magA < magB;

    // Compare rational numbers as fractions
    double ratA = static_cast<double>(a.key2.first) / a.key2.second;
    double ratB = static_cast<double>(b.key2.first) / b.key2.second;
    if (ratA != ratB) return ratA < ratB;

    // Compare string lengths
    return a.key3.length() < b.key3.length();
}
