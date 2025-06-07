#include "ERDictionary.hpp"

#include <algorithm>
#include <istream>
#include <sstream>
#include <iterator>
#include <limits>

namespace ryzhov {

    std::istream& operator>>(std::istream &is, Delimiter &&dest) {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        char c = 0;
        is.get(c);
        if (is && c != dest.delimiter) is.setstate(std::ios::failbit);
        return is;
    }

    std::istream& operator>>(std::istream &is, Label &&dest) {
        std::istream::sentry sentry(is);
        if (!sentry) return is;

        std::string l;
        std::copy_n(
            std::istream_iterator<char>(is),
            dest.label.length(),
            std::back_inserter(l)
        );

        if (is && l != dest.label) is.setstate(std::ios::failbit);
        return is;
    }

    std::istream& operator>>(std::istream &is, ERDictionary &dictionary) {
        std::string line;
        std::string enWord;
        std::string ruTranslate;
        // Получаем строку переводов с пробелами
        std::getline(is, line);
        // Превращаем ее в поток
        std::istringstream iss(line);
        // Достаем английское слово
        iss >> enWord;
        // Достаем из потока переводы
        while (iss >> ruTranslate) {
            dictionary[enWord].insert(ruTranslate);
        }
        return is;
    }
}
