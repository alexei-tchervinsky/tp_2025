#ifndef METHODS_HPP
#define METHODS_HPP

#include <unordered_map>
#include <string>

void printTopWords(const std::unordered_map<std::string, int>& wordCount, int n);
void searchWord(const std::unordered_map<std::string, int>& wordCount, const std::string& word);
void printAllWords(const std::unordered_map<std::string, int>& wordCount);

#endif // METHODS_HPP