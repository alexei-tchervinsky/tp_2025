#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

class HashTable
{
private:
    std::unordered_map<std::string, size_t> word_counts_;

public:
    void insert(const std::string& key);
    void remove(const std::string& key);
    size_t search(const std::string& key) const;
    void getThree() const;
};
