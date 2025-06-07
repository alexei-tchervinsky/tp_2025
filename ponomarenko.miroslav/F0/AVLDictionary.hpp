#ifndef AVL_DICTIONARY_HPP
#define AVL_DICTIONARY_HPP

#include <map>
#include <string>
#include <ostream>
#include <vector>

class AVLDictionary {
private:
    std::map<std::string, std::size_t> dict_;

public:
    void insert(const std::string& word);
    bool removeWord(const std::string& word);
    void clear();
    std::size_t getFreq(const std::string& word) const;
    bool isEmpty() const;
    std::size_t size() const;

    void printAll(std::ostream& out) const;
    std::vector<std::pair<std::string, size_t>> getTopN(std::size_t n) const;
    void printTopThree(std::ostream& out) const;

};

#endif
