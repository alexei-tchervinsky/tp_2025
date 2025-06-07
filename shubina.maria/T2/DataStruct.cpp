// DataStruct.cpp
#include "DataStruct.h"
#include <string>

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


