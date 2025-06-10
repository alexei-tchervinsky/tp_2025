#include "DataStruct.h"
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <algorithm>

namespace {
    bool parseKey1(std::istream& in, char& key1) {
        char ch;
        if (in >> ch) {
            if (ch == '\'') {
                // Формат 'a'
                if (in >> key1 >> ch && ch == '\'') {
                    return true;
                }
            } else {
                // Попробуем разные форматы
                in.unget();
                std::string valStr;
                while (in >> ch && ch != ':' && ch != ')') {
                    valStr += ch;
                }
                in.unget();

                if (!valStr.empty()) {
                    try {
                        if (valStr.find("0x") == 0 || valStr.find("0X") == 0) {
                            key1 = static_cast<char>(std::stoul(valStr, nullptr, 16));
                        } else if (valStr.find("#c") == 0) {
                            key1 = 0;
                        } else if (valStr.find("(") == 0) {
                            key1 = 0;
                        } else {
                            key1 = static_cast<char>(std::stoi(valStr));
                        }
                        return true;
                    } catch (...) {
                        key1 = 0;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool parseKey2(std::istream& in, unsigned long long& key2) {
        std::string numStr;
        char ch;
        while (in >> ch && ch != ':' && ch != ')') {
            numStr += ch;
        }
        in.unget();

        if (!numStr.empty()) {
            try {
                // Удаляем суффиксы
                std::string cleanNum = numStr;
                size_t pos;
                if ((pos = cleanNum.find("ull")) != std::string::npos ||
                    (pos = cleanNum.find("ll")) != std::string::npos ||
                    (pos = cleanNum.find("d")) != std::string::npos) {
                    cleanNum = cleanNum.substr(0, pos);
                }

                if (cleanNum.find('.') != std::string::npos ||
                    cleanNum.find('e') != std::string::npos) {
                    // Для чисел с плавающей точкой
                    double dval = std::stod(cleanNum);
                    key2 = static_cast<unsigned long long>(std::round(dval));
                } else if (cleanNum.find("0x") == 0 || cleanNum.find("0X") == 0) {
                    // Для hex чисел
                    key2 = std::stoull(cleanNum, nullptr, 16);
                } else if (cleanNum.find("0b") == 0 || cleanNum.find("0B") == 0) {
                    // Для binary чисел
                    key2 = std::stoull(cleanNum.substr(2), nullptr, 2);
                } else if (cleanNum.find('\'') != std::string::npos) {
                    // Для символов
                    key2 = static_cast<unsigned long long>(cleanNum[1]);
                } else if (cleanNum.find("#c") == 0 || cleanNum.find("(") == 0) {
                    // Для комплексных чисел и вложенных структур
                    key2 = 0;
                } else {
                    // Для обычных чисел (включая отрицательные)
                    if (!cleanNum.empty() && cleanNum[0] == '-') {
                        long long val = std::stoll(cleanNum);
                        key2 = static_cast<unsigned long long>(val);
                    } else {
                        key2 = std::stoull(cleanNum);
                    }
                }
                return true;
            } catch (...) {
                key2 = 0;
                return true;
            }
        }
        return false;
    }
}

std::istream& operator>>(std::istream& in, DataStruct& data) {
    char ch;
    if (!(in >> ch) || ch != '(') {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

    while (true) {
        if (!(in >> ch) || ch != ':') break;

        std::string keyName;
        if (!(in >> keyName)) {
            in.setstate(std::ios_base::failbit);
            return in;
        }

        if (!(in >> ch) || ch != ':') {
            in.setstate(std::ios_base::failbit);
            return in;
        }

        if (keyName == "key1") {
            hasKey1 = parseKey1(in, data.key1);
        } else if (keyName == "key2") {
            hasKey2 = parseKey2(in, data.key2);
        } else if (keyName == "key3") {
            if ((in >> ch) && ch == '"') {
                std::getline(in, data.key3, '"');
                hasKey3 = true;
            }
        } else {
            in.setstate(std::ios_base::failbit);
            return in;
        }
    }

    if (!hasKey1 || !hasKey2 || !hasKey3) {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    if (!(in >> ch) || ch != ')') {
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

