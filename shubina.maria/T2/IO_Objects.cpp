#include "IO_Objects.h"
#include <sstream>
#include <cctype>
#include <unordered_map>
#include <stdexcept>
#include <istream>

std::string extractRecord(std::istream& is) {
    std::string line;
    if (!std::getline(is, line) || line.empty()) {
        return "";
    }
    size_t start = line.find("(:");
    size_t end = line.rfind(":)");
    if (start == std::string::npos || end == std::string::npos || end <= start) {
        return "";
    }
    return line.substr(start + 2, end - start - 2);
}

std::string trim(const std::string& s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) ++start;
    auto end = s.end();
    do {
        --end;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
    return std::string(start, end + 1);
}

void parseField(const std::string& token, std::unordered_map<std::string, std::string>& fields) {
    size_t colon1 = token.find(':');
    if (colon1 == std::string::npos)
        return;
    std::string fieldKey = token.substr(0, colon1);
    std::string fieldValue = token.substr(colon1 + 1);
    fields[fieldKey] = trim(fieldValue);
}

std::istream& operator>>(std::istream& is, DataStruct& ds) {
    std::string record = extractRecord(is);
    if (record.empty()) {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    std::unordered_map<std::string, std::string> fields;
    std::istringstream ss(record);
    std::string token;
    while (std::getline(ss, token, ':')) {
        if (!token.empty()) {
            parseField(token, fields);
        }
    }

    if (fields.size() != 3 || !fields.count("key1") || !fields.count("key2") || !fields.count("key3")) {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    // Parse key1 (char)
    std::string key1Str = fields["key1"];
    if (key1Str.size() != 3 || key1Str[0] != '\'' || key1Str[2] != '\'') {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    ds.key1 = key1Str[1];

    // Parse key2 (unsigned long long)
    std::string key2Str = fields["key2"];
    try {
        size_t pos = 0;
        if (key2Str.find("0x") == 0 || key2Str.find("0X") == 0) {
            ds.key2 = std::stoull(key2Str.substr(2), &pos, 16);
        } else if (key2Str.find("0b") == 0 || key2Str.find("0B") == 0) {
            ds.key2 = std::stoull(key2Str.substr(2), &pos, 2);
        } else if (key2Str[0] == '0' && key2Str.size() > 1) {
            ds.key2 = std::stoull(key2Str.substr(1), &pos, 8);
        } else {
            ds.key2 = std::stoull(key2Str, &pos, 10);
        }
        if (pos != key2Str.size()) {
            is.setstate(std::ios_base::failbit);
            return is;
        }
    } catch (...) {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    // Parse key3 (string)
    std::string key3Str = fields["key3"];
    if (key3Str.size() < 2 || key3Str.front() != '"' || key3Str.back() != '"') {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    ds.key3 = key3Str.substr(1, key3Str.size() - 2);

    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
    os << "(:key1 '" << ds.key1 << "':key2 " << ds.key2 << ":key3 \"" << ds.key3 << "\":)";
    return os;
}

std::vector<DataStruct> readDataStructs(std::istream& is) {
    std::vector<DataStruct> result;
    DataStruct ds;
    while (is >> ds) {
        result.push_back(ds);
        is.clear();
    }
    is.clear();
    return result;
}

void writeDataStructs(const std::vector<DataStruct>& data, std::ostream& os) {
    for (const auto& ds : data) {
        os << ds << '\n';
    }
}

