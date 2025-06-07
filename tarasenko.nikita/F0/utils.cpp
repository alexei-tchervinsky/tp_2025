#include "utils.hpp"

bool isWordChar(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) || c == '\'';
}

std::string toLower(const std::string& str) {
    std::string result;
    for (char c : str) {
        result += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return result;
}