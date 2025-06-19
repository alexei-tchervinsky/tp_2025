#include "Dictionary.h"
#include <algorithm>
#include <cctype>

namespace {
    bool isBlank(const std::string& str) {
        return str.empty() || std::all_of(str.begin(), str.end(), ::isspace);
    }

    void validateKey(const std::string& key) {
        if (key.empty() || isBlank(key)) {
            throw std::invalid_argument("Key cannot be empty or whitespace-only");
        }

        if (!std::all_of(key.begin(), key.end(), [](char c) {
            return std::isalpha(c) || c == '-';
        })) {
            throw std::invalid_argument("Key must contain only letters and hyphens");
        }
    }

    void validateTranslation(const std::string& translation) {
        if (translation.empty() || isBlank(translation)) {
            throw std::invalid_argument("Translation cannot be empty or whitespace-only");
        }
    }
}

void Dictionary::insert(const std::string& key, const std::string& translation) {
    validateKey(key);
    validateTranslation(translation);

    std::string lowerKey = key;
    std::transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(), ::tolower);

    data[lowerKey].insert(translation);
}

std::vector<std::string> Dictionary::search(const std::string& key) const {
    validateKey(key);

    std::string lowerKey = key;
    std::transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(), ::tolower);

    auto it = data.find(lowerKey);
    if (it != data.end()) {
        return std::vector<std::string>(it->second.begin(), it->second.end());
    }
    return {};
}

bool Dictionary::remove(const std::string& key) {
    validateKey(key);

    std::string lowerKey = key;
    std::transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(), ::tolower);

    return data.erase(lowerKey) > 0;
}

void Dictionary::printAll() const {
    for (const auto& pair : data) {
        std::cout << pair.first << ": ";
        for (const auto& translation : pair.second) {
            std::cout << translation << "; ";
        }
        std::cout << "\n";
    }
}

