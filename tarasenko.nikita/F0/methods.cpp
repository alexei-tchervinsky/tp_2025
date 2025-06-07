#include "methods.hpp"
#include "processor.hpp"
#include "utils.hpp"
#include <iostream>

void printTopWords(const std::unordered_map<std::string, int>& wordCount, int n) {
    auto sortedWords = sortByFrequency(wordCount);

    std::cout << "Top " << n << " most frequent words:\n";
    for (int i = 0; i < n && i < sortedWords.size(); ++i) {
        const auto& pair = sortedWords[i];
        std::cout << pair.first << " - " << pair.second;
        std::cout << (pair.second == 1 ? " time\n" : " times\n");
    }
}

void searchWord(const std::unordered_map<std::string, int>& wordCount, const std::string& word) {
    std::string lowerWord = toLower(word);
    auto it = wordCount.find(lowerWord);

    if (it != wordCount.end()) {
        std::cout << "Word '" << lowerWord << "' appears " << it->second;
        std::cout << (it->second == 1 ? " time\n" : " times\n");
    }
    else {
        std::cout << "Word '" << lowerWord << "' not found\n";
    }
}

void printAllWords(const std::unordered_map<std::string, int>& wordCount) {
    auto sortedWords = sortByFrequency(wordCount);

    std::cout << "All words (sorted by frequency):\n";
    for (const auto& pair : sortedWords) {
        std::cout << pair.first << " - " << pair.second;
        std::cout << (pair.second == 1 ? " time\n" : " times\n");
    }
}

