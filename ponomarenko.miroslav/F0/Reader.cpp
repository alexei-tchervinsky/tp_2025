#include "Reader.hpp"

#include <cctype>

namespace {
    std::string valWord(const std::string& word) {
        std::string res;
        for (char ch: word) {
            if (std::isalpha(ch)) {
                res += std::tolower(ch);
            }
        }

        return res;
    }
}

AVLDictionary Reader::read(std::istream& in, AVLDictionary& dict) const {
    std::string word;

    while (in >> word) {
        std::string valid = valWord(word);
        if (!valid.empty()) {
            dict.insert(valid);
        }
    }

    return dict;
}
