#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

struct DataStruct {
    std::string key1;
    std::string key2;
    std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& data) {
    char ch;
    std::string token;

    if (!(in >> ch) || ch != '(') {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    for (int i = 0; i < 3; ++i) {
        if (!(in >> ch) || ch != ':') {
            in.setstate(std::ios_base::failbit);
            return in;
        }

        std::string key;
        in >> key;

        if (!(in >> ch) || ch != ':') {
            in.setstate(std::ios_base::failbit);
            return in;
        }

        std::ostringstream valueStream;
        in >> std::noskipws;

        int depth = 0;
        while (in >> ch) {
            if (ch == '(') {
                depth++;
            } else if (ch == ')') {
                if (--depth == 0) break;
            } else if (ch == ':' && depth == 0) {
                in.putback(ch);
                break;
            }
            valueStream << ch;
        }

        if (key == "key1") {
            data.key1 = valueStream.str();
        } else if (key == "key2") {
            data.key2 = valueStream.str();
        } else if (key == "key3") {
            data.key3 = valueStream.str();
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
    out << "(:key1 " << data.key1 << ":"
        << ":key2 " << data.key2 << ":"
        << ":key3 " << data.key3 << ":)";
    return out;
}

int main() {
    std::vector<DataStruct> dataVector;

    // —читываем данные
    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(dataVector)
    );

    if (dataVector.empty()) {
        std::cout << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
        return 0;
    }

    std::cout << "Atleast one supported record type\n";

    return 0;
}

