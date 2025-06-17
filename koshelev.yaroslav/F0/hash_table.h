#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <stdexcept>

class HashTable {
public:
    void Insert(const std::string& key, const std::string& value);
    std::vector<std::string> Search(const std::string& key) const;
    void Remove(const std::string& key);
    void PrintBucket(size_t hash_value) const;
    void PrintAll() const;
    size_t HashFunction(const std::string& key) const;

private:
    std::unordered_map<std::string, std::set<std::string>> table_;

    void ValidateKey(const std::string& key) const;
};

#endif

