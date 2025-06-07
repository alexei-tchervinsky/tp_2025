#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <iostream>

// Вариант 1: Кастомная хеш-функция на основе std::hash
struct CustomStringHash {
    std::size_t operator()(const std::string& key) const {
        // Используем стандартный std::hash<std::string> как основу
        std::hash<std::string> hasher;
        std::size_t h1 = hasher(key);

        // Добавляем дополнительное перемешивание для улучшения распределения
        // Используем FNV-1a подобный алгоритм поверх std::hash
        std::size_t hash = h1;
        hash ^= hash >> 16;
        hash *= 0x85ebca6b;
        hash ^= hash >> 13;
        hash *= 0xc2b2ae35;
        hash ^= hash >> 16;

        return hash;
    }
};

class HashTable {
private:
    std::unordered_map<std::string, std::vector<std::string>,
    CustomStringHash> dictionary;

    bool is_valid_key(const std::string& key) const;

public:
    HashTable() = default;
    ~HashTable() = default;

    void insert(const std::string& key, const std::string& translation);
    std::vector<std::string> search(const std::string& key) const;
    bool remove(const std::string& key);

    size_t size() const { return dictionary.size(); }
    bool empty() const { return dictionary.empty(); }
    double load_factor() const { return dictionary.load_factor(); }

    std::vector<std::string> get_all_keys() const;
    void clear() { dictionary.clear(); }
    bool contains(const std::string& key) const;

    void print_statistics() const;
    void print_hash_statistics() const;
    std::size_t get_hash_value(const std::string& key) const;
};

#endif
