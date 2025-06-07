#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>
#include <iterator>

struct DataStruct {
    unsigned long long key1;
    char key2;
    std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& ds) {
    std::string line;
    if (!std::getline(in, line)) {
        return in;
    }

    size_t start = line.find('(');
    size_t end = line.rfind(')');
    if (start == std::string::npos || end == std::string::npos || start >= end) {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::string content = line.substr(start + 1, end - start - 1);
    std::istringstream iss(content);
    std::string token;

    ds.key1 = 0;
    ds.key2 = '\0';
    ds.key3.clear();

    bool key1_found = false, key2_found = false, key3_found = false;

    while (iss >> token) {
        if (token == ":key1") {
            std::string value;
            iss >> value;
            try {
                size_t pos = 0;
                ds.key1 = std::stoull(value, &pos, 8);
                if (pos != value.size()) {
                    throw std::invalid_argument("Invalid octal number");
                }
                key1_found = true;
            }
            catch (...) {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        else if (token == ":key2") {
            std::string value;
            iss >> value;
            if (value.size() >= 3 && value.front() == '\'' && value.back() == '\'') {
                ds.key2 = value[1];
                key2_found = true;
            }
            else {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        else if (token == ":key3") {
            std::string value;
            iss >> value;
            if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
                ds.key3 = value.substr(1, value.size() - 2);
                key3_found = true;
            }
            else {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
    }

    if (!key1_found || !key2_found || !key3_found) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& ds) {
    out << "(:key1 " << std::oct << ds.key1 << std::dec << ":key2 '" << ds.key2 << "':key3 \"" << ds.key3 << "\":)";
    return out;
}

bool compareDataStructs(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> data;

    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data)
    );

    std::sort(data.begin(), data.end(), compareDataStructs);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
