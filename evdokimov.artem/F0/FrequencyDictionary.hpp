#ifndef FREQUENCY_DICTIONARY_HPP
#define FREQUENCY_DICTIONARY_HPP

#include <string>
#include <unordered_map>
#include <vector>

class DictionaryError : public std::exception {
private:
  std::string message;

public:
  DictionaryError(const std::string &msg) : message(msg) {}
  const char *what() const noexcept override { return message.c_str(); }
};

class FrequencyDictionary {
private:
  std::unordered_map<std::string, int> wordCounts;
  std::string toLower(const std::string &word) const;

public:
  explicit FrequencyDictionary(size_t size = 1000);
  void INSERT(const std::string &input);
  int getWordCount(const std::string &word) const;
  void REMOVE(const std::string &word);
  void processText(const std::string &text);
  std::vector<std::pair<std::string, int>> getTopWords(size_t count) const;
  void printDictionary() const;
};

#endif
