#include "FrequencyDictionary.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>

FrequencyDictionary::FrequencyDictionary(size_t size) : wordCounts(size) {
  if (size == 0) {
    throw DictionaryError("Table size must be positive");
  }
}

std::string FrequencyDictionary::toLower(const std::string &word) const {
  std::string lowerWord;
  for (char c : word) {
    lowerWord += static_cast<char>(std::tolower(c));
  }
  return lowerWord;
}

void FrequencyDictionary::INSERT(const std::string &input) {
  if (input.empty()) {
    throw DictionaryError("Empty input is not allowed");
  }
  processText(input);
}

int FrequencyDictionary::getWordCount(const std::string &word) const {
  std::string lowerWord = toLower(word);
  auto it = wordCounts.find(lowerWord);
  return it != wordCounts.end() ? it->second : 0;
}

void FrequencyDictionary::REMOVE(const std::string &word) {
  if (word.empty()) {
    throw DictionaryError("Empty word is not allowed");
  }
  std::string lowerWord = toLower(word);
  if (wordCounts.find(lowerWord) == wordCounts.end()) {
    throw DictionaryError("Word not found: " + word);
  }
  wordCounts.erase(lowerWord);
}

void FrequencyDictionary::processText(const std::string &text) {
  std::string currentWord;
  for (char c : text) {
    if (std::isalpha(c) || c == '\'') {
      currentWord += static_cast<char>(std::tolower(c));
    } else if (!currentWord.empty()) {
      wordCounts[currentWord]++;
      currentWord.clear();
    }
  }
  if (!currentWord.empty()) {
    wordCounts[currentWord]++;
  }
}

std::vector<std::pair<std::string, int>>
FrequencyDictionary::getTopWords(size_t count) const {
  if (count == 0) {
    throw DictionaryError("Number of top words must be positive");
  }
  std::vector<std::pair<std::string, int>> allEntries(wordCounts.begin(),
                                                      wordCounts.end());
  std::sort(allEntries.begin(), allEntries.end(),
            [](const auto &a, const auto &b) {
              if (a.second != b.second)
                return a.second > b.second;
              return a.first < b.first;
            });
  if (allEntries.size() > count) {
    allEntries.resize(count);
  }
  return allEntries;
}

void FrequencyDictionary::printDictionary() const {
  std::vector<std::string> keys;
  for (const auto &pair : wordCounts) {
    keys.push_back(pair.first);
  }
  std::sort(keys.begin(), keys.end());
  std::cout << "Dictionary Contents:\n";
  for (const auto &key : keys) {
    std::cout << key << ": " << wordCounts.at(key) << "\n";
  }
}
