#include "processor.hpp"
#include "utils.hpp"
#include <fstream>
#include <algorithm>

void parseWords(const std::string& text, std::unordered_map<std::string, int>& wordCount) {
    std::string currentWord;

    for (char c : text) {
        if (isWordChar(c)) {
            currentWord += c;
        }
        else if (!currentWord.empty()) {
            std::string lowerWord = toLower(currentWord);
            wordCount[lowerWord]++;
            currentWord.clear();
        }
    }

    if (!currentWord.empty()) {
        std::string lowerWord = toLower(currentWord);
        wordCount[lowerWord]++;
    }
}

std::vector<std::pair<std::string, int>> sortByFrequency(const std::unordered_map<std::string, int>& wordCount) {
    std::vector<std::pair<std::string, int>> sortedWords(wordCount.begin(), wordCount.end());

    std::sort(sortedWords.begin(), sortedWords.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        });

    return sortedWords;
}

void processFile(const std::string& filename, std::unordered_map<std::string, int>& wordCount) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string buffer(size, '\0');
    if (file.read(&buffer[0], size)) {
        parseWords(buffer, wordCount);
    }
}

