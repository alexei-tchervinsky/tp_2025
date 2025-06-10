#include "DataStruct.h"
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <cmath>

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
            // Гибкий парсинг для key1 (char)
            char ch;
            if (in >> ch && ch == '\'') {
                // Формат 'a'
                if (!(in >> data.key1) || !(in >> ch) || ch != '\'') {
                    in.setstate(std::ios_base::failbit);
                    return in;
                }
            } else {
                // Другие форматы - преобразуем к char
                in.unget();
                std::string valStr;
                char next;
                while (in >> next && next != ':' && next != ')') {
                    valStr += next;
                }
                in.unget();

                try {
                    if (valStr.find("0x") == 0 || valStr.find("0X") == 0) {
                        data.key1 = static_cast<char>(std::stoul(valStr, nullptr, 16));
                    } else if (valStr.find("#c") == 0) {
                        // Для комплексных чисел берем первую часть
                        data.key1 = static_cast<char>(0);
                    } else if (valStr.find("(") == 0) {
                        // Для вложенных структур
                        data.key1 = static_cast<char>(0);
                    } else {
                        data.key1 = static_cast<char>(std::stoi(valStr));
                    }
                } catch (...) {
                    data.key1 = 0;
                }
            }
            hasKey1 = true;
        } else if (keyName == "key2") {
            // Гибкий парсинг для key2 (unsigned long long)
            std::string numStr;
            char ch;
            while (in >> ch && ch != ':' && ch != ')') {
                numStr += ch;
            }
            in.unget();

            try {
                if (numStr.find('.') != std::string::npos ||
                    numStr.find('e') != std::string::npos) {
                    // Для чисел с плавающей точкой
                    double dval = std::stod(numStr);
                    data.key2 = static_cast<unsigned long long>(std::round(dval));
                } else if (numStr.find("0x") == 0 || numStr.find("0X") == 0) {
                    // Для hex чисел
                    data.key2 = std::stoull(numStr, nullptr, 16);
                } else if (numStr.find("0b") == 0 || numStr.find("0B") == 0) {
                    // Для binary чисел
                    data.key2 = std::stoull(numStr.substr(2), nullptr, 2);
                } else if (numStr.find("ull") != std::string::npos ||
                          numStr.find("ll") != std::string::npos) {
                    // Для чисел с суффиксами
                    data.key2 = std::stoull(numStr.substr(0, numStr.size()-2));
                } else if (numStr.find('\'') != std::string::npos) {
                    // Для символов
                    data.key2 = static_cast<unsigned long long>(numStr[1]);
                } else if (numStr.find("#c") == 0) {
                    // Для комплексных чисел
                    data.key2 = 0;
                } else if (numStr.find("(") == 0) {
                    // Для вложенных структур
                    data.key2 = 0;
                } else {
                    // Для обычных чисел
                    data.key2 = std::stoull(numStr);
                }
                hasKey2 = true;
            } catch (...) {
                data.key2 = 0;
                hasKey2 = true;
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

