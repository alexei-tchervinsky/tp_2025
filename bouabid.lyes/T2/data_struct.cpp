#include "data_struct.hpp"

std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::string line;
    while (std::getline(in, line)) {
    
        std::smatch match;

    // Проверка на обрамляющие скобки
    if (!std::regex_match(line, std::regex(R"(\(:.*:\))")))
        continue;

        // Регулярные выражения для поиска ключей
        std::regex dblRegex(R"(:key1 ([+-]?[\d]+\.[\d]+)[dD]:)");
        std::regex chrRegex(R"(:key2 '(.{1})':)");
        std::regex strRegex(R"(:key3 \"((?:[^"\\"\\\\]|\\\\.)*)\":)");

        bool ok = true;
        if (std::regex_search(line, match, dblRegex)) {
            data.key1 = std::stod(match[1]);
        } else {
            ok = false;
        }

        if (std::regex_search(line, match, chrRegex)) {
            data.key2 = match[1].str()[0];
        } else {
            ok = false;
        }

        if (std::regex_search(line, match, strRegex)) {
            data.key3 = match[1];
        } else {
            ok = false;
        }

    if (ok){ 
        return in;
    }
  }


  in.setstate(std::ios::failbit);

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 " << std::fixed << std::setprecision(1) << data.key1 << "d:"
        << "key2 '" << data.key2 << "':"
        << "key3 \"" << data.key3 << "\":)";
    return out;
}