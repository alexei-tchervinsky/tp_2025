#include "DataStruct.hpp"
#include <sstream>
#include <iomanip>
#include <cctype>
#include <stdexcept>
#include <cmath>
namespace {
    bool parseScientificDouble(const std::string& str, double& value) {
        try {
            size_t pos = 0;
            value = std::stod(str, &pos);
            return pos == str.length();
        } catch (...) {
            return false;
        }
    }
    bool parseLiteralDouble(const std::string& str, double& value) {
        try {
            size_t pos = 0;
            std::string num = str;
            if (!num.empty() && (num.back() == 'd' || num.back() == 'D'))
                num.pop_back();
            value = std::stod(num, &pos);
            return pos == num.length();
        } catch (...) {
            return false;
        }
    }
    bool parseULL(const std::string& str, unsigned long long& value) {
        try {
            if (str.empty()) return false;
            if (str.size() > 1 && str[0] == '0') {
                if (str.size() > 2 && (str[1] == 'b' || str[1] == 'B')) {
                    value = std::stoull(str.substr(2), nullptr, 2);
                } else if (str.size() > 2 && (str[1] == 'x' || str[1] == 'X')) {
                    value = std::stoull(str.substr(2), nullptr, 16);
                } else {
                    value = std::stoull(str, nullptr, 8);
                }
            } else {
                value = std::stoull(str);
            }
            return true;
        } catch (...) {
            return false;
        }
    }
}
bool operator<(const DataStruct& lhs, const DataStruct& rhs) {
    if (lhs.key1 != rhs.key1) return lhs.key1 < rhs.key1;
    if (lhs.key2 != rhs.key2) return lhs.key2 < rhs.key2;
    return lhs.key3.size() < rhs.key3.size();
}
std::istream& operator>>(std::istream& in, DataStruct& ds) {
    std::string line;
    if (!std::getline(in, line)) return in;
    std::istringstream iss(line);
    char ch;
    DataStruct tmp;
    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
    if (!(iss >> ch) || ch != '(') {
        in.setstate(std::ios::failbit);
        return in;
    }
    while (iss >> ch && ch == ':') {
        std::string key;
        if (!(iss >> key)) break;
        if (key == "key1") {
            std::string value;
            if (!(iss >> value)) break;
            if (!parseLiteralDouble(value, tmp.key1) &&
                !parseScientificDouble(value, tmp.key1)) {
                break;
            }
            hasKey1 = true;
        }
        else if (key == "key2") {
            std::string value;
            if (!(iss >> value)) break;
            if (value[0] == '\'') {
                if (value.size() == 3 && value.back() == '\'') {
                    tmp.key2 = static_cast<unsigned char>(value[1]);
                    hasKey2 = true;
                }
            }
            else if (!parseULL(value, tmp.key2)) {
                break;
            } else {
                hasKey2 = true;
            }
        }
        else if (key == "key3") {
            if (!(iss >> ch) || ch != '"') break;
            std::string value;
            while (iss.get(ch) && ch != '"') {
                value += ch;
            }
            if (ch != '"') break;
            tmp.key3 = value;
            hasKey3 = true;
        }
        while (iss.peek() == ' ') iss.get();
    }
    if (iss >> ch && ch == ')' && hasKey1 && hasKey2 && hasKey3) {
        ds = tmp;
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}
std::ostream& operator<<(std::ostream& out, const DataStruct& ds) {
    out << "(:key1 " << std::fixed << std::setprecision(1) << ds.key1 << 'd';
    out << ":key2 0" << std::oct << ds.key2 << std::dec;
    out << ":key3 \"" << ds.key3 << "\":)";
    return out;
}
