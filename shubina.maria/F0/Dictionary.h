#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <set>
#include <map>

class Dictionary {
private:
    std::map<std::string, std::set<std::string>> data;

public:
    void insert(const std::string& key, const std::string& translation);
    std::set<std::string> search(const std::string& key) const;
    bool remove(const std::string& key);
};

#endif // DICTIONARY_H

