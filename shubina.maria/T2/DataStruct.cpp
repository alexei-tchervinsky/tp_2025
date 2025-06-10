#include "DataStruct.h"
#include <sstream>
#include <cctype>

std::istream& operator>>(std::istream& in, DataStruct& data) {
    char openBrace = '\0';
    if (!(in >> openBrace) || openBrace != '(') {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    bool hasKey1 = false, hasKey2 = false;

    while (true) {
        char colon;
        if (!(in >> colon) || colon != ':') break;

        std::string keyName;
        in >> keyName;

        char colonAfterKey;
        if (!(in >> colonAfterKey) || colonAfterKey != ':') {
            in.setstate(std::ios_base::failbit);
            return in;
        }

        if (keyName == "key1") {
            char ch, quote;
            if (!(in >> ch) || ch != '\'') {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            if (!(in >> ch)) {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            if (!(in >> quote) || quote != '\'') {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            data.key1 = ch;
            hasKey1 = true;
        } else if (keyName == "key2") {
            unsigned long long value = 0;
            char suffix;
            if (!(in >> value >> suffix)) {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            if (suffix != 'u' && suffix != 'U') {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            if ((in.peek() != ':') && !isspace(in.peek())) {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            data.key2 = value;
            hasKey2 = true;
        } else if (keyName == "key3") {
            char quote;
            if (!(in >> quote) || quote != '"') {
                in.setstate(std::ios_base::failbit);
                return in;
            }

            std::getline(in, data.key3, '"');
        } else {
            in.setstate(std::ios_base::failbit);
            return in;
        }
    }

    if (!hasKey1 || !hasKey2) {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    char closeBrace;
    if (!(in >> closeBrace) || closeBrace != ')') {
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

