#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <cctype>
#include <iomanip>

struct DataStruct {
    unsigned long long key1;  // ULL OCT
    char key2;                // CHR LIT
    std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& ds) {
    std::string line;
    if (!std::getline(in, line)) {
        return in;
    }

    size_t start = line.find('(');
    size_t end = line.rfind(')');
    if (start == std::string::npos || end == std::string::npos) {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::string content = line.substr(start + 1, end - start - 1);
    std::istringstream iss(content);
    std::string token;

    bool has_key1 = false, has_key2 = false, has_key3 = false;
    unsigned long long key1_val = 0;
    char key2_val = '\0';
    std::string key3_val;

    while (iss >> token) {
        if (token == ":key1") {
            std::string oct_val;
            iss >> oct_val;
            try {
                key1_val = std::stoull(oct_val, nullptr, 8);
                has_key1 = true;
            }
            catch (...) {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        else if (token == ":key2") {
            std::string char_lit;
            iss >> char_lit;
            if (char_lit.size() == 3 && char_lit[0] == '\'' && char_lit[2] == '\'') {
                key2_val = char_lit[1];
                has_key2 = true;
            }
            else {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        else if (token == ":key3") {
            std::string str_lit;
            iss >> std::ws;
            if (iss.peek() == '"') {
                iss.get();
                std::getline(iss, str_lit, '"');
                key3_val = str_lit;
                has_key3 = true;
            }
            else {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
    }

    if (!has_key1 || !has_key2 || !has_key3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    ds.key1 = key1_val;
    ds.key2 = key2_val;
    ds.key3 = key3_val;
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& ds) {
    out << "(:key1 " << std::oct << ds.key1 << ":key2 '" << ds.key2 << "':key3 \"" << ds.key3 << "\":)";
    return out;
}

bool compareDataStructs(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> data;

    // Чтение данных
    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data)
    );

    // Сортировка данных
    std::sort(data.begin(), data.end(), compareDataStructs);

    // Вывод данных
    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
