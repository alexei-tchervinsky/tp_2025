#include "helpFunctions.h"

std::vector<std::string> splitToWords(const std::string& line)
{
    std::vector<std::string> words;
    std::istringstream in(line);
    std::string word;

    while (in >> word)
    {
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (!word.empty() && !std::all_of(word.begin(), word.end(), ::isdigit)) {
            words.push_back(word);
        }
    }
    return words;
}
