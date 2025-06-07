#ifndef ERDICTIONARY_HPP
#define ERDICTIONARY_HPP

#include <string>
#include <set>
#include <map>


namespace ryzhov {
    // Строка словаря, содержит английское слово и его переводы
    using ERDictionary = std::map<std::string, std::set<std::string>>;

    struct Delimiter {
        char delimiter;
    };

    struct Label {
        std::string label;
    };

    std::istream& operator>>(std::istream &is, Delimiter &&dest);
    std::istream& operator>>(std::istream &is, Label &&dest);
    std::istream& operator>>(std::istream &is, ERDictionary &dictionary);
    std::istream& operator>>(std::istream &is, std::set<std::string> &translations);
}

#endif
