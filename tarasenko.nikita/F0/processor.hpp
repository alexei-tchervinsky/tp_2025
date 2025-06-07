#ifndef WORD_PROCESSOR_HPP
#define WORD_PROCESSOR_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <utility> 

void parseWords(const std::string& text, std::unordered_map<std::string, int>& wordCount);
std::vector<std::pair<std::string, int>> sortByFrequency(const std::unordered_map<std::string, int>& wordCount);
void processFile(const std::string& filename, std::unordered_map<std::string, int>& wordCount);

#endif // WORD_PROCESSOR_HPP