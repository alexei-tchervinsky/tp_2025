#include "dictionary.hpp"
#include <iostream>
#include <algorithm>
#include <functional>
#include <stdexcept>

DictionaryEntry::DictionaryEntry(const std::string& k, const std::string& translation)
    : key(k) {
    translations.push_back(translation);
    translations.sort();
}

void DictionaryEntry::addTranslation(const std::string& translation) {
    if (std::find(translations.begin(), translations.end(), translation) != translations.end()) {
        return;
    }

    auto it = translations.begin();
    while (it != translations.end() && *it < translation) {
        ++it;
    }
    translations.insert(it, translation);
}

HashDictionary::HashDictionary(size_t initial_size) : table(initial_size) {}

size_t HashDictionary::hash(const std::string& key) const {
    return std::hash<std::string>{}(key);
}

size_t HashDictionary::findPosition(const std::string& key, bool forInsert) const {
    size_t start_index = hash(key) % table.size();
    size_t index = start_index;
    size_t first_deleted = table.size();

    do {
        switch (table[index].state) {
            case BucketState::OCCUPIED:
                if (table[index].entry.key == key) {
                    return index;
                }
                break;

            case BucketState::DELETED:
                if (forInsert && first_deleted == table.size()) {
                    first_deleted = index;
                }
                break;

            case BucketState::EMPTY:
                return forInsert ? (first_deleted != table.size() ? first_deleted : index)
                                : table.size();
        }

        index = (index + 1) % table.size();
    } while (index != start_index);

    return forInsert ? first_deleted : table.size();
}

void HashDictionary::rehash() {
    std::vector<Bucket> old_table = table;
    table.clear();
    table.resize(old_table.size() * 2);
    num_entries = 0;

    for (auto& bucket : old_table) {
        if (bucket.state == BucketState::OCCUPIED) {
            for (const auto& translation : bucket.entry.translations) {
                insert(bucket.entry.key, translation);
            }
        }
    }
}

void HashDictionary::insert(const std::string& key, const std::string& translation) {
    if (key.empty() || translation.empty()) {
        throw std::invalid_argument("Key and translation must be non-empty");
    }

    if (static_cast<double>(num_entries) / table.size() >= MAX_LOAD_FACTOR) {
        rehash();
    }

    size_t pos = findPosition(key, true);

    if (pos == table.size()) {
        throw std::runtime_error("Hash table is full");
    }

    if (table[pos].state == BucketState::OCCUPIED) {
        table[pos].entry.addTranslation(translation);
    } else {
        table[pos].entry = DictionaryEntry(key, translation);
        table[pos].state = BucketState::OCCUPIED;
        num_entries++;
    }
}

const std::list<std::string>* HashDictionary::search(const std::string& key) const {
    if (key.empty()) return nullptr;

    size_t pos = findPosition(key);
    if (pos < table.size()) {
        return &table[pos].entry.translations;
    }
    return nullptr;
}

bool HashDictionary::remove(const std::string& key) {
    if (key.empty()) return false;

    size_t pos = findPosition(key);
    if (pos < table.size()) {
        table[pos].state = BucketState::DELETED;
        num_entries--;
        return true;
    }
    return false;
}

void HashDictionary::print() const {
    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i].state == BucketState::OCCUPIED) {
            std::cout << table[i].entry.key << ": ";
            for (const auto& t : table[i].entry.translations) {
                std::cout << t << ", ";
            }
            std::cout << "\n";
        }
    }
}

void runDictionaryTests() {
    HashDictionary dict(5);

    dict.insert("apple", "яблоко");
    dict.insert("book", "книга");

    const std::list<std::string>* results = dict.search("apple");
    if (results) {
        std::cout << "apple: ";
        for (const auto& t : *results) std::cout << t << " ";
        std::cout << "\n";
    }

    dict.insert("apple", "яблоневый плод");
    dict.insert("run", "бежать");
    dict.insert("run", "запускать");

    dict.insert("dog", "собака");
    dict.insert("cat", "кошка");

    std::cout << "\nDictionary contents:\n";
    dict.print();

    std::cout << "\nRemoving 'book': " << (dict.remove("book") ? "Success" : "Failed") << "\n";
    std::cout << "Search for 'book': " << (dict.search("book") ? "Found" : "Not found") << "\n\n";

    try {
        dict.insert("", "пустое слово");
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}
