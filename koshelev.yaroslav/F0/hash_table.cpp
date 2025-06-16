#include "hash_table.h"
#include <iostream>

size_t HashTable::HashFunction(const std::string& key) const {
    ValidateKey(key);
    std::hash<std::string> hasher;
    return hasher(key);
}

void HashTable::ValidateKey(const std::string& key) const {
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
}

void HashTable::Insert(const std::string& key, const std::string& value) {
    ValidateKey(key);
    table_[key].insert(value);
}

std::vector<std::string> HashTable::Search(const std::string& key) const {
    ValidateKey(key);
    auto it = table_.find(key);
    if (it != table_.end()) {
        return std::vector<std::string>(it->second.begin(), it->second.end());
    }
    return {};
}

void HashTable::Remove(const std::string& key) {
    ValidateKey(key);
    table_.erase(key);
}

void HashTable::PrintBucket(size_t hash_value) const {
    for (const auto& pair : table_) {
        if (HashFunction(pair.first) == hash_value) {
            std::cout << "  " << pair.first << ": ";
            for (const auto& tr : pair.second) {
                std::cout << tr << ", ";
            }
            std::cout << "\n";
        }
    }
}

void HashTable::PrintAll() const {
    for (const auto& pair : table_) {
        std::cout << pair.first << ": ";
        for (const auto& tr : pair.second) {
            std::cout << tr << ", ";
        }
        std::cout << "\n";
    }
}