#include "HashTable.hpp"
#include "extra_functions.hpp"
#include <fstream>
#include <cctype>

std::string checkWord(const std::string& symb)
{
    if (symb.empty())
    {
        return "";
    }

    size_t start = 0;
    size_t end = symb.size() - 1;

    while (start < symb.size()
        && std::ispunct(static_cast<unsigned char>(symb[start]))
        && symb[start] != '\''
        && symb[start] != '-')
        start++;

    while (end > start
        && std::ispunct(static_cast<unsigned char>(symb[end]))
        && symb[end] != '\''
        && symb[end] != '-')
        end--;

    std::string empty = symb.substr(start, end - start + 1);

    std::string word;
    for (char c : empty)
    {
        if (std::isalpha(static_cast<unsigned char>(c)) || c == '-' || c == '\'')
        {
            word += std::tolower(static_cast<unsigned char>(c));
        }
        else
        {
            return "";
        }
    }

    return word;
}

bool fillTable(HashTable& table, const std::string& filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Failed to open file.\n";
        return false;
    }

    std::string word;
    bool hasWords = false;

    while (file >> word)
    {
        word = checkWord(word);
        if (!word.empty())
        {
            table.insert(word);
            hasWords = true;
        }
    }

    file.close();

    if (!hasWords)
    {
        std::cerr << "No valid words found in file.\n";
        return false;
    }

    return true;
}
