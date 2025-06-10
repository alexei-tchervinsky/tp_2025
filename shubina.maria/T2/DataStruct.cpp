#include "DataStruct.h"
#include <sstream>

std::istream& operator>>(std::istream& in, DataStruct& data) {
    char ch;

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
            if (ch == '(') depth++;
            else if (ch == ')') {
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
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 " << data.key1 << ":"
        << ":key2 " << data.key2 << ":"
        << ":key3 " << data.key3 << ":)";
    return out;
}

