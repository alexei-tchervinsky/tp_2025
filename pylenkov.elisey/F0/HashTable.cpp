#include "HashTable.hpp"
#include <iostream>

void HashTable::insert(const std::string& word, const std::vector<std::string>& translations)
{
    size_t index = hashFunction(word);
    auto& bucket = table_[index];

    for (const auto& entry : bucket)
    {
        if (entry.word == word)
        {
            throw std::invalid_argument("Слово \"" + word + "\" уже существует!");
        }
    }

    auto sorted_translations = translations;
    std::sort(sorted_translations.begin(), sorted_translations.end());
    bucket.push_front({word, sorted_translations});
}

std::vector<std::string> HashTable::search(const std::string& word) const
{
    size_t index = hashFunction(word);
    const auto& bucket = table_[index];

    for (const auto& entry : bucket)
    {
        if (entry.word == word)
        {
            return entry.translations;
        }
    }
    throw std::invalid_argument("Слово \"" + word + "\" не найдено!");
}

void HashTable::remove(const std::string& word)
{
    size_t index = hashFunction(word);
    auto& bucket = table_[index];
    auto prev = bucket.before_begin();

    for (auto it = bucket.begin(); it != bucket.end(); ++it, ++prev)
    {
        if (it->word == word)
        {
            bucket.erase_after(prev);
            return;
        }
    }
    throw std::invalid_argument("Слово \"" + word + "\" не найдено!");
}

void HashTable::display() const {
    for (size_t i = 0; i < tableSize_; ++i)
    {
        for (const auto& entry : table_[i])
        {
            std::cout << "Слово: " << entry.word << "; Переводы: ";
            if (!entry.translations.empty())
            {
                for (size_t j = 0; j < entry.translations.size(); ++j)
                {
                    std::cout << entry.translations[j];
                    if (j != entry.translations.size() - 1)
                    {
                        std::cout << ", ";
                    }
                }
            }
            std::cout << ";\n";
        }
    }
}
