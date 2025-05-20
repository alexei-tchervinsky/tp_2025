#include "DataStruct.hpp"
#include <sstream>
#include <iomanip>
#include <cctype>
#include <stdexcept>
namespace {
    bool parseDouble(const std::string& str, double& value) {
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
    bool parseOctalULL(const std::string& str, unsigned long long& value) {
        try {
            std::string num = str;
            while (!num.empty() && isalpha(num.back()))
                num.pop_back();
            if (num.empty()) return false;
            if (num.size() > 1 && num[0] == '0') {
                value = std::stoull(num, nullptr, 8);
            } else {
                value = std::stoull(num);
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
            if (!(iss >> value) || !parseDouble(value, tmp.key1)) break;
            hasKey1 = true;
        }
        else if (key == "key2") {
            std::string value;
            if (!(iss >> value) || !parseOctalULL(value, tmp.key2)) break;
            hasKey2 = true;
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
