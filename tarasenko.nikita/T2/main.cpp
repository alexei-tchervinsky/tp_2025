#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <cctype>
#include <climits>

struct DataStruct {
    unsigned long long key1;  // ULL OCT
    char key2;                // CHR LIT
    std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& ds) {
    DataStruct temp;
    bool key1_set = false, key2_set = false, key3_set = false;
    std::string line;

    if (!std::getline(in, line, ')')) {
        in.setstate(std::ios::failbit);
        return in;
    }

    line += ')';
    std::istringstream iss(line);
    char ch;

    if (!(iss >> ch) || ch != '(') {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::string key;
    while (iss >> ch && ch == ':') {
        if (!(iss >> key)) {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (key == "key1") {
            std::string value;
            if (!(iss >> value)) {
                in.setstate(std::ios::failbit);
                return in;
            }
            try {
                size_t pos = 0;
                temp.key1 = std::stoull(value, &pos, 8);
                if (pos != value.size()) {
                    in.setstate(std::ios::failbit);
                    return in;
                }
                key1_set = true;
            }
            catch (...) {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        else if (key == "key2") {
            std::string value;
            if (!(iss >> value) || value.size() != 3 || value[0] != '\'' || value[2] != '\'') {
                in.setstate(std::ios::failbit);
                return in;
            }
            temp.key2 = value[1];
            key2_set = true;
        }
        else if (key == "key3") {
            std::string value;
            iss >> std::ws;
            if (iss.peek() != '"') {
                in.setstate(std::ios::failbit);
                return in;
            }
            iss.get();
            std::getline(iss, temp.key3, '"');
            key3_set = true;
        }
        else {
            in.setstate(std::ios::failbit);
            return in;
        }

        while (iss.get(ch) && ch != ':') {
            if (!std::isspace(ch)) {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        if (ch == ':') {
            iss.putback(ch);
        }
    }

    if (!key1_set || !key2_set || !key3_set) {
        in.setstate(std::ios::failbit);
        return in;
    }

    ds = temp;
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& ds) {
    out << "(:key1 " << std::oct << ds.key1 << std::dec << "ull"
        << ":key2 '" << ds.key2 << "'"
        << ":key3 \"" << ds.key3 << "\":)";
    return out;
}

bool compareDataStructs(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> data;

    // Чтение данных с обработкой ошибок
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        DataStruct ds;
        if (iss >> ds) {
            data.push_back(ds);
        }
        // Игнорируем некорректные строки
    }

    std::sort(data.begin(), data.end(), compareDataStructs);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
