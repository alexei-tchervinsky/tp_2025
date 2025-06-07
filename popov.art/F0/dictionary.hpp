#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#include <string>
#include <list>
#include <vector>
#include <memory>
class DictionaryEntry {
public:
    DictionaryEntry(const std::string& key, const std::string& translation);
    void addTranslation(const std::string& translation);
    bool removeTranslation(const std::string& translation);
    const std::string& getKey() const;
    const std::list<std::string>& getTranslations() const;
    bool hasTranslation(const std::string& translation) const;
private:
    std::string key;
    std::list<std::string> translations;
};
class DictionaryHashTable {
public:
    explicit DictionaryHashTable(size_t size = 101);
    void insert(const std::string& key, const std::string& translation);
    std::shared_ptr<DictionaryEntry> search(const std::string& key) const;
    bool remove(const std::string& key);
    bool contains(const std::string& key) const;
    size_t size() const;
private:
    std::vector<std::shared_ptr<DictionaryEntry>> table;
    size_t tableSize;
    size_t hash(const std::string& key) const;
};
#endif
