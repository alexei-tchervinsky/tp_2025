#include "DataStruct.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <utility>
namespace {
    bool parseDoubleFast(const char* start, const char* end, double& value) {
        char* parse_end;
        value = std::strtod(start, &parse_end);
        if (parse_end == end || (*parse_end == 'd' || *parse_end == 'D')) {
            return true;
        }
        return false;
    }
    bool parseOctalULLFast(const char* start, const char* end, unsigned long long& value) {
        char* parse_end;
        if (*start == '0') {
            value = std::strtoull(start, &parse_end, 8);
        } else {
            value = std::strtoull(start, &parse_end, 10);
        }
        while (parse_end < end && std::isalpha(*parse_end)) {
            parse_end++;
        }
        return parse_end == end;
    }
}
bool operator<(const DataStruct& lhs, const DataStruct& rhs) {
    if (lhs.key1 != rhs.key1) return lhs.key1 < rhs.key1;
    if (lhs.key2 != rhs.key2) return lhs.key2 < rhs.key2;
    return lhs.key3.size() < rhs.key3.size();
}
std::istream& operator>>(std::istream& in, DataStruct& ds) {
    std::string line;
    if (!std::getline(in, line)) {
        return in;
    }
    const char* ptr = line.data();
    const char* end = ptr + line.size();
    if (ptr == end || *ptr++ != '(') {
        in.setstate(std::ios::failbit);
        return in;
    }
    DataStruct tmp;
    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
    while (ptr < end && *ptr == ':') {
        ptr++;
        const char* key_start = ptr;
        while (ptr < end && !std::isspace(*ptr) && *ptr != ':') {
            ptr++;
        }
        std::string_view key(key_start, ptr - key_start);
        if (ptr == end || *ptr != ' ') {
            in.setstate(std::ios::failbit);
            return in;
        }
        ptr++;
        if (key == "key1") {
            const char* num_start = ptr;
            while (ptr < end && !std::isspace(*ptr) && *ptr != ':') {
                ptr++;
            }
            if (!parseDoubleFast(num_start, ptr, tmp.key1)) {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey1 = true;
        }
        else if (key == "key2") {
            const char* num_start = ptr;
            while (ptr < end && !std::isspace(*ptr) && *ptr != ':') {
                ptr++;
            }
            if (!parseOctalULLFast(num_start, ptr, tmp.key2)) {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey2 = true;
        }
        else if (key == "key3") {
            if (ptr == end || *ptr != '"') {
                in.setstate(std::ios::failbit);
                return in;
            }
            ptr++;
            const char* str_start = ptr;
            while (ptr < end && *ptr != '"') {
                ptr++;
            }
            if (ptr == end) {
                in.setstate(std::ios::failbit);
                return in;
            }
            tmp.key3.assign(str_start, ptr - str_start);
            ptr++;
            hasKey3 = true;
        }
        while (ptr < end && *ptr != ':') {
            ptr++;
        }
    }
    if (ptr == end || *ptr != ')' || !hasKey1 || !hasKey2 || !hasKey3) {
        in.setstate(std::ios::failbit);
        return in;
    }
    ds = std::move(tmp);
    return in;
}
std::ostream& operator<<(std::ostream& out, const DataStruct& ds) {
    out << "(:key1 ";
    auto flags = out.flags();
    out << std::fixed << std::setprecision(1) << ds.key1 << 'd';
    out.flags(flags);
    out << ":key2 0" << std::oct << ds.key2 << std::dec;
    out << ":key3 \"" << ds.key3 << "\":)";
    return out;
}
