#include "HashTable.hpp"

void HashTable::insert(const std::string& key)
{
    word_counts_[key]++;
}

void HashTable::remove(const std::string& key) {
    word_counts_.erase(key);
}

size_t HashTable::search(const std::string& key) const
{
    auto it = word_counts_.find(key);
    return it != word_counts_.end() ? it->second : 0;
}

void HashTable::getThree() const
{
    std::vector<std::pair<std::string, size_t>> sorted_words(word_counts_.begin(), word_counts_.end());

    std::partial_sort(
        sorted_words.begin(),
        sorted_words.begin() + std::min(3, (int)sorted_words.size()),
        sorted_words.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; }
    );

    std::cout << "\n3 most frequent words:\n";
    for (int i = 0; i < std::min(3, (int)sorted_words.size()); ++i)
    {
        std::cout << sorted_words[i].first << ": " << sorted_words[i].second << "\n";
    }
    if (sorted_words.empty())
    {
        std::cout << "No words in table.\n";
    }
}
