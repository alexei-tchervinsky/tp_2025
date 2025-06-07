#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

struct DataStruct {
    char key1;
    unsigned long long key2;
    std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& data) {
    char openBrace = '\0';
    char colon1 = '\0', colon2 = '\0', colon3 = '\0';
    std::string keyName;
    char quote1 = '\0', quote2 = '\0';
    char ch;
    unsigned long long ullValue = 0;

    if (!(in >> openBrace) || openBrace != '(') {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    for (int i = 0; i < 3; ++i) {
        if (!(in >> colon1)) {
            in.setstate(std::ios_base::failbit);
            return in;
        }
        if (colon1 != ':') {
            in.setstate(std::ios_base::failbit);
            return in;
        }

        in >> keyName;

        if (keyName == "key1") {
            if (!(in >> ch >> colon2)) {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            if (ch != '\'' || colon2 != ':') {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            data.key1 = ch;
        } else if (keyName == "key2") {
            if (!(in >> ullValue >> ch >> colon2)) {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            if (ch != 'u' && ch != 'U' || colon2 != ':') {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            data.key2 = ullValue;
        } else if (keyName == "key3") {
            if (!(in >> quote1)) {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            if (quote1 != '"') {
                in.setstate(std::ios_base::failbit);
                return in;
            }

            std::getline(in, data.key3, '"');
            if (!(in >> quote2 >> colon3) || quote2 != '"' || colon3 != ':') {
                in.setstate(std::ios_base::failbit);
                return in;
            }
        } else {
            in.setstate(std::ios_base::failbit);
            return in;
        }
    }

    if (!(in >> ch) || ch != ')') {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 \'" << data.key1 << "\':"
        << ":key2 " << data.key2 << "ull:"
        << ":key3 \"" << data.key3 << "\":)";
    return out;
}

int main() {
    std::vector<DataStruct> dataVector;

    // Считываем данные
    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(dataVector)
    );

    // Сортируем
    auto compare = [](const DataStruct& a, const DataStruct& b) {
        if (a.key1 != b.key1) return a.key1 < b.key1;
        if (a.key2 != b.key2) return a.key2 < b.key2;
        return a.key3.length() < b.key3.length();
    };
    std::sort(dataVector.begin(), dataVector.end(), compare);

    // Выводим
    std::copy(
        dataVector.begin(),
        dataVector.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}

