#include "DataStruct.h"
#include <sstream>
#include <cctype>
#include <cstdlib>

std::istream& operator>>(std::istream& in, DataStruct& data) {
    char openBrace = '\0';
    if (!(in >> openBrace) || openBrace != '(') {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

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
            // ����� ������ ������� ��� key1
            char ch;
            if (in >> ch && ch == '\'') {
                // ������ 'a'
                if (!(in >> data.key1) || !(in >> ch) || ch != '\'') {
                    in.setstate(std::ios_base::failbit);
                    return in;
                }
            } else {
                // ������ ������� - ����������� � char
                in.unget();
                int val;
                if (!(in >> val)) {
                    in.setstate(std::ios_base::failbit);
                    return in;
                }
                data.key1 = static_cast<char>(val);
            }
            hasKey1 = true;
        } else if (keyName == "key2") {
            // ����� ������ ������� ��� key2
            std::string numStr;
            char ch;
            while (in >> ch && ch != ':' && !isspace(ch)) {
                numStr += ch;
            }
            in.unget();

            try {
                if (numStr.find('.') != std::string::npos ||
                    numStr.find('e') != std::string::npos) {
                    // ��� ����� � ��������� ������
                    double dval = std::stod(numStr);
                    data.key2 = static_cast<unsigned long long>(dval);
                } else if (numStr.find("0x") == 0 || numStr.find("0X") == 0) {
                    // ��� hex �����
                    data.key2 = std::stoull(numStr, nullptr, 16);
                } else if (numStr.find("0b") == 0 || numStr.find("0B") == 0) {
                    // ��� binary �����
                    data.key2 = std::stoull(numStr.substr(2), nullptr, 2);
                } else {
                    // ��� ������� �����
                    data.key2 = std::stoull(numStr);
                }
                hasKey2 = true;
            } catch (...) {
                in.setstate(std::ios_base::failbit);
                return in;
            }
        } else if (keyName == "key3") {
            char quote;
            if (!(in >> quote) || quote != '"') {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            std::getline(in, data.key3, '"');
            hasKey3 = true;
        } else {
            in.setstate(std::ios_base::failbit);
            return in;
        }
    }

    if (!hasKey1 || !hasKey2 || !hasKey3) {
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
    out << "(:key1 '" << data.key1 << "':"
        << ":key2 " << data.key2 << "ull:"
        << ":key3 \"" << data.key3 << "\":)";
    return out;
}

