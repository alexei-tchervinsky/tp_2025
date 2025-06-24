#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <forward_list>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

struct Translation
{
    std::string word;
    std::vector<std::string> translations;
};

class HashTable
{
private:
    std::vector<std::forward_list<Translation>> table_;
    size_t tableSize_;

    size_t hashFunction(const std::string& key) const
    {
        size_t hash = 0;
        for (char ch : key)
        {
            hash = (hash * 31 + ch) % tableSize_;
        }
        return hash;
    }

public:
    HashTable(size_t size = 100) : tableSize_(size), table_(size) {}

    void insert(const std::string& word, const std::vector<std::string>& translations);
    std::vector<std::string> search(const std::string& word) const;
    void remove(const std::string& word);
    void display() const;
};

#endif
