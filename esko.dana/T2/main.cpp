#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>

struct DataStruct {
    double key1;
    long long key2;
    std::string key3;
};

void skipSpaces(const std::string& str, size_t& i) {
    while (i < str.size() && std::isspace(str[i])) ++i;
}

bool parseNumber(const std::string& str, double& result) {
    try {
        size_t pos = 0;
        result = std::stod(str, &pos);
        return pos == str.length();
    } catch (...) {
        return false;
    }
}

bool parseNumber(const std::string& str, long long& result) {
    try {
        size_t pos = 0;

        if (str.size() > 2 && str[0] == '0') {
            if (str[1] == 'x' || str[1] == 'X') {
                result = std::stoll(str, &pos, 16);
            } else if (str[1] == 'b' || str[1] == 'B') {
                result = std::stoll(str.substr(2), &pos, 2);
            } else {
                result = std::stoll(str, &pos, 8);
            }
        } else {
            result = std::stoll(str, &pos);
        }

        return pos == str.length();
    } catch (...) {
        return false;
    }
}


std::ostream& operator<<(std::ostream& out, const DataStruct& o) {
    out << "(:key1 " << std::fixed << std::setprecision(1) << o.key1 << "D"
        << ":key2 " << o.key2 << "LL"
        << ":key3 \"" << o.key3 << "\":)";
    return out;
}

int main() {
    std::vector<DataStruct> items;

    try {
        std::istream_iterator<DataStruct> input_start(std::cin);
        std::istream_iterator<DataStruct> input_end;
        std::copy(input_start, input_end, std::back_inserter(items));
    } catch (const std::exception& e) {
        std::cerr << "Ошибка чтения: " << e.what() << std::endl;
        return 1;
    }

    std::sort(items.begin(), items.end(), [](const DataStruct& a, const DataStruct& b) {
        if (a.key1 == b.key1) {
            if (a.key2 == b.key2) {
                return a.key3.length() < b.key3.length();
            }
            return a.key2 < b.key2;
        }
        return a.key1 < b.key1;
    });

    std::cout << "\nОтсортированные элементы:\n";
    std::copy(items.begin(), items.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
    std::cout << std::endl;

    return 0;
}

bool parse(const std::string& str, DataStruct& o) {
    if (str.empty() || str.front() != '(' || str.back() != ')')
        return false;

    size_t i = 1;
    int flags = 0;

    while (i < str.size()) {
        skipSpaces(str, i);
        if (i >= str.size() || str[i] != ':') break;
        ++i;

        std::string key;
        while (i < str.size() && std::isalpha(str[i]))
            key += str[i++];

        if (key.empty()) return false;

        skipSpaces(str, i);
        if (i >= str.size()) return false;

        if (key == "key1") {
            if (flags & 1) return false;
            flags |= 1;

            std::string val;
            while (i < str.size() && str[i] != ':' && str[i] != ')') {
                val += str[i++];
            }

            if (!val.empty() && (val.back() == 'd' || val.back() == 'D')) {
                val.pop_back();
            }

            if (!parseNumber(val, o.key1)) {
                return false;
            }
        }
        else if (key == "key2") {
            if (flags & 2) return false;
            flags |= 2;

            std::string val;
            while (i < str.size() && str[i] != ':' && str[i] != ')') {
                val += str[i++];
            }

            if (val.size() >= 2) {
                std::string suffix = val.substr(val.size() - 2);
                for (auto& c : suffix) c = std::tolower(c);

                if (suffix == "ll" || suffix == "ul") {
                    val.erase(val.size() - 2);
                }
            }

            if (!parseNumber(val, o.key2)) {
                return false;
            }
        }
        else if (key == "key3") {
            if (flags & 4) return false;
            flags |= 4;

            if (i >= str.size() || str[i] != '"') return false;
            ++i;

            std::string val;
            while (i < str.size()) {
                if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
                    break;
                val += str[i++];
            }

            if (i >= str.size() || str[i] != '"') return false;
            ++i;

            o.key3 = val;
        }
        else {
            return false;
        }
    }

    return (flags == 7);
}
