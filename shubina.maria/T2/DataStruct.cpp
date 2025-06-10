#include "DataStruct.h"
#include <sstream>
#include <cctype>
#include <regex>

std::istream& operator>>(std::istream& in, DataStruct& data) {
    char ch;

    if (!(in >> ch) || ch != '(') {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

    while (in >> ch && ch == ':') {
        std::string key;
        if (!(in >> key)) {
            in.setstate(std::ios_base::failbit);
            return in;
        }

        if (!(in >> ch) || ch != ':') {
            in.setstate(std::ios_base::failbit);
            return in;
        }

        std::ostringstream valueStream;
        in >> std::noskipws;

        // Чтение значения до следующего : или конца записи
        int depth = 0;
        while (in >> ch) {
            if (ch == '(') depth++;
            else if (ch == ')') {
                if (--depth == 0) {
                    in.putback(ch); // Сохраняем закрывающую скобку
                    break;
                }
            } else if (ch == ':' && depth == 0) {
                in.putback(ch);
                break;
            }
            valueStream << ch;
        }

        std::string value = valueStream.str();

        if (key == "key1") {
            std::regex re(R"('([^']+)')");
            std::smatch match;
            if (!std::regex_match(value, match, re) || match[1].str().size() != 1) {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            data.key1 = match[1].str()[0];
            hasKey1 = true;
        } else if (key == "key2") {
            std::istringstream valStream(value);
            std::string temp;
            valStream >> temp;
            if (temp.empty()) {
                in.setstate(std::ios_base::failbit);
                return in;
            }

            // Поддержка различных форматов ULL
            unsigned long long ullVal = 0;
            try {
                size_t pos;
                if (temp.starts_with("0x") || temp.starts_with("0X")) {
                    ullVal = std::stoull(temp.substr(2), &pos, 16);
                } else if (temp.starts_with("0b") || temp.starts_with("0B")) {
                    ullVal = std::stoull(temp.substr(2), &pos, 2);
                } else if (temp.starts_with('0')) {
                    ullVal = std::stoull(temp, &pos, 8);
                } else {
                    ullVal = std::stoull(temp, &pos, 10);
                }

                if (pos != temp.size()) throw std::invalid_argument("Invalid number");
                data.key2 = ullVal;
            } catch (...) {
                in.setstate(std::ios_base::failbit);
                return in;
            }

            hasKey2 = true;
        } else if (key == "key3") {
            if (value.empty() || value.front() != '"' || value.back() != '"') {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            data.key3 = value.substr(1, value.size() - 2);
            hasKey3 = true;
        } else {
            in.setstate(std::ios_base::failbit);
            return in;
        }
    }

    if (hasKey1 && hasKey2 && hasKey3 && in >> ch && ch == ')') {
        return in;
    } else {
        in.setstate(std::ios_base::failbit);
        return in;
    }
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 '" << data.key1 << "':key2 " << data.key2 << "ull:key3 \""
        << data.key3 << "\":)";
    return out;
}

