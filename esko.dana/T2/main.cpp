#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <windows.h>

struct DataStruct {
    double      key1;   // число с плавающей точкой (double), формат —         :key1 30.0d:
    long long   key2;   // целое знаковое число (long long), формат —          :key2 -89LL:
    std::string key3;   // строка в кавычках, может содержать спец. символы —  :key3 "Data":
};

bool parse(std::string const & str, DataStruct & o) {   // парсинг и заполнение структуры о
    if (str[0] != '(')        // проверка скобки
        return false;

    size_t m = 0;             // флаг чтобы не допустить повторного появления одного и того же поля
    for (size_t i = 1; i < str.size(); ++i) {
        if (str[i] == ':') {
            std::string key = "";
            for (i = i + 1; i < str.size() && (str[i] != ' ' && str[i] != ')'); ++i)
                key += str[i];

            if (str[i] == ')' && key.empty()) {
                if (i == str.size() - 1 && m == 7)
                    return true;

                return false;
            }

            if (key == "key1") {
                if (m & 1)
                    return false;
                m |= 1;

                std::string value = "";
                for (i = i + 1; i < str.size() && (str[i] != 'D' && str[i] != 'd'); ++i)
                    value += str[i];

                if (value.empty())
                    return false;

                if (value.front() == ' ')
                    return false;

                if (value.back()  == ' ')
                    return false;

                o.key1 = std::stod(value);

                continue;
            }

            if (key == "key2") {
                if (m & 2)
                    return false;
                m |= 2;

                std::string value = "";
                for (i = i + 1; i < str.size() && (str[i] != 'L' && str[i] != 'l'); ++i)
                    value += str[i];

                if (value.empty())
                    return false;

                if (value.front() == ' ')
                    return false;

                if (value.back()  == ' ')
                    return false;

                o.key2 = std::stoll(value);

                if (++i == str.size())
                    return false;

                if (str[i] != 'L' && str[i] != 'l')
                    return false;

                continue;
            }

            if (key == "key3") {
                if (m & 4)
                    return false;
                m |= 4;

                if (++i == str.size())
                    return false;

                if (str[i] != '"')
                    return false;

                std::string value = "";
                for (i = i + 1; i < str.size(); ++i) {
                    if (str[i] == '"' && str[i - 1] != '\\')
                        break;
                    value += str[i];
                }

                o.key3 = value;

                continue;
            }

            return false;
        }
    }
    return false;
}

std::istream& operator>>(std::istream& in, DataStruct& o) {
    std::string line;
    while (std::getline(in, line)) {
            if (parse(line, o)) {
                return in;
            }
            else {
                in.setstate(std::ios::failbit);

            }
    }
    return in;
}

std::ostream& operator<<(std::ostream & out, DataStruct const & o) {        // перегрузка оператора вывода
    out << "(:key1" << " " << std::fixed << std::setprecision(1) << o.key1 << "D"
        <<  ":key2" << " " << o.key2 << "LL"
        <<  ":key3" << " " << "\"" << o.key3 << "\":)";

    return out;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::vector<DataStruct> items;

    while (std::cin) {
        try {
            std::istream_iterator<DataStruct> input_start(std::cin);
            std::istream_iterator<DataStruct> input_end;
            std::copy(input_start, input_end, std::back_inserter(items));
        }
    catch (...) {
    }
    }

    std::ranges::sort(items.begin(), items.end(), [](auto const & a, auto const & b) {
        if (a.key1 == b.key1) {
            if (a.key2 == b.key2) {
                return a.key3.length() < b.key3.length();
            }
            return a.key2 < b.key2;
        }
        return a.key1 < b.key1;
    });

    std::cout << std::endl;

    std::copy(items.begin(), items.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n"));

    std::cout << std::endl;

    return 0;
}
