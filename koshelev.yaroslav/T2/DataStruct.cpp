#include "DataStruct.hpp"
#include "IO_Objects.hpp"
#include "iofmtguard.hpp"
#include <iomanip>
#include <cmath>
#include <sstream>
#include <cctype>
#include <iostream>

namespace solution {

    bool DataStruct::operator<(const DataStruct& other) const {
        if (std::abs(key1 - other.key1) > 1e-6)
            return key1 < other.key1;
        if (key2 != other.key2)
            return key2 < other.key2;
        return key3 < other.key3;
    }

    std::istream& operator>>(std::istream& in, DataStruct& value) {
        value = DataStruct{};
        char c;

        // Пропускаем пробелы и проверяем начало записи
        in >> std::ws;
        if (!in.get(c) || c != '(') {
            in.setstate(std::ios::failbit);
            return in;
        }

        // Читаем до закрывающей скобки
        std::string full_record;
        while (in.get(c) && c != ')') {
            full_record += c;
        }
        full_record += ')'; // Добавляем закрывающую скобку

        // Разбираем запись вручную
        std::istringstream record_stream(full_record);
        std::string part;
        int fields_found = 0;

        while (std::getline(record_stream, part, ':')) {
            if (part.find("key1") != std::string::npos) {
                std::istringstream key_stream(part);
                std::string key;
                key_stream >> key; // Пропускаем "key1"
                if (key_stream >> value.key1) {
                    fields_found++;
                }
            }
            else if (part.find("key2") != std::string::npos) {
                std::istringstream key_stream(part);
                std::string key;
                key_stream >> key; // Пропускаем "key2"
                std::string hex_str;
                if (key_stream >> hex_str) {
                    if (hex_str.substr(0, 2) == "0x") {
                        value.key2 = std::stoull(hex_str.substr(2), nullptr, 16);
                        fields_found++;
                    }
                }
            }
            else if (part.find("key3") != std::string::npos) {
                size_t quote_pos = part.find('"');
                if (quote_pos != std::string::npos) {
                    size_t end_quote = part.find('"', quote_pos+1);
                    if (end_quote != std::string::npos) {
                        value.key3 = part.substr(quote_pos+1, end_quote-quote_pos-1);
                        fields_found++;
                    }
                }
            }
        }

        if (fields_found != 3) {
            in.setstate(std::ios::failbit);
        }

        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& value) {
        iofmtguard guard(out);
        out << "(:key1 " << std::scientific << std::uppercase << value.key1;
        out << ":key2 0x" << std::hex << value.key2;
        out << std::dec << ":key3 \"" << value.key3 << "\":)";
        return out;
    }
}
