#include "dictionary.hpp"
#include <algorithm>
DictionaryEntry::DictionaryEntry(const std::string& key, const std::string& translation)
    : key(key) {
    translations.push_back(translation);
}
void DictionaryEntry::addTranslation(const std::string& translation) {
    translations.push_back(translation);
    translations.sort();
}
bool DictionaryEntry::removeTranslation(const std::string& translation) {
    auto it = std::find(translations.begin(), translations.end(), translation);
    if (it != translations.end()) {
        translations.erase(it);
        return true;
    }
    return false;
}
const std::string& DictionaryEntry::getKey() const {
    return key;
}
const std::list<std::string>& DictionaryEntry::getTranslations() const {
    return translations;
}
bool DictionaryEntry::hasTranslation(const std::string& translation) const {
    return std::find(translations.begin(), translations.end(), translation) != translations.end();
}
DictionaryHashTable::DictionaryHashTable(size_t size) : table(size), tableSize(size) {}
void DictionaryHashTable::insert(const std::string& key, const std::string& translation) {
    size_t index = hash(key) % tableSize;
    table[index] = std::make_shared<DictionaryEntry>(key, translation);
}
std::shared_ptr<DictionaryEntry> DictionaryHashTable::search(const std::string& key) const {
    size_t index = hash(key) % tableSize;
    return table[index] && table[index]->getKey() == key ? table[index] : nullptr;
}
bool DictionaryHashTable::remove(const std::string& key) {
    size_t index = hash(key) % tableSize;
    if (table[index] && table[index]->getKey() == key) {
        table[index].reset();
        return true;
    }
    return false;
}
bool DictionaryHashTable::contains(const std::string& key) const {
    return search(key) != nullptr;
}
size_t DictionaryHashTable::size() const {
    return tableSize;
}
size_t DictionaryHashTable::hash(const std::string& key) const {
    size_t hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}
