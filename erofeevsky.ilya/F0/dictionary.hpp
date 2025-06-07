#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <vector>
#include <stdexcept>

class Dictionary{
private:
    static const size_t TABLE_SIZE = 100;
    struct DictionaryEntry
    {
        std::string englishWord;
        std::vector<std::string> russianTranslations;
        DictionaryEntry(const std::string& eng, const std::string& rus);
        void addTranslation(const std::string& rus);
        bool removeTranslation(const std::string& rus);
    };

    std::vector<DictionaryEntry> table[TABLE_SIZE];

    size_t hashFunction(const std::string& key) const;
    std::pair<size_t, std::vector<DictionaryEntry>::iterator> findEntry(const std::string& key);

public:
    Dictionary(const std::string& filename = "dictionary.txt");
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename = "dictionary.txt") const;
    bool insert(const std::string& eng, const std::string& rus);
    std::vector<std::string> search(const std::string& eng) const;
    bool remove(const std::string& eng, const std::string& rus = "");
    void printAll() const;
    void printStats() const;
};

#endif

