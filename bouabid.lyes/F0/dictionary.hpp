#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <list>
#include <vector>


struct DictionaryEntry {
    std::string key;
    std::list<std::string> translations;


    DictionaryEntry() = default;


    DictionaryEntry(const std::string& k, const std::string& translation);


    void addTranslation(const std::string& translation);
};


class HashDictionary {
private:

    enum class BucketState { EMPTY, OCCUPIED, DELETED };


    struct Bucket {
        DictionaryEntry entry;
        BucketState state = BucketState::EMPTY;
    };

    std::vector<Bucket> table;
    size_t num_entries = 0;
    static constexpr double MAX_LOAD_FACTOR = 0.7;


    size_t hash(const std::string& key) const;


    size_t findPosition(const std::string& key, bool forInsert = false) const;


    void rehash();

public:

    HashDictionary(size_t initial_size = 101);


    void insert(const std::string& key, const std::string& translation);

    // Replace std::optional with pointer return
    const std::list<std::string>* search(const std::string& key) const;


    bool remove(const std::string& key);


    void print() const;
};


void runDictionaryTests();

#endif
