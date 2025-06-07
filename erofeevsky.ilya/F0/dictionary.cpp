#include "dictionary.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

Dictionary::DictionaryEntry::DictionaryEntry(const std::string& eng, const std::string& rus)
    : englishWord(eng) {
    if (eng.empty() || rus.empty()){
        throw std::invalid_argument("English word and translation cannot be empty");
    }
    russianTranslations.push_back(rus);
}


void Dictionary::DictionaryEntry::addTranslation(const std::string& rus){
    if (rus.empty()){
        throw std::invalid_argument("Translation cannot be empty");
    }
    russianTranslations.push_back(rus);
    std::sort(russianTranslations.begin(), russianTranslations.end());
}

bool Dictionary::DictionaryEntry::removeTranslation(const std::string& rus){
    auto it = std::find(russianTranslations.begin(), russianTranslations.end(), rus);
    if (it != russianTranslations.end()){
        russianTranslations.erase(it);
        return true;
    }
    return false;
}

size_t Dictionary::hashFunction(const std::string& key) const{
    size_t hash = 0;
    for (char c : key) {
        hash = hash * 31 + c;
    }
    return hash % TABLE_SIZE;
}

std::pair<size_t, std::vector<Dictionary::DictionaryEntry>::iterator>
Dictionary::findEntry(const std::string& key){
    size_t hashValue = hashFunction(key);
    for (auto it = table[hashValue].begin(); it != table[hashValue].end(); ++it){
        if (it->englishWord == key){
            return {hashValue, it};
        }
    }
    return {hashValue, table[hashValue].end()};
}

Dictionary::Dictionary(const std::string& filename){
    try{
        loadFromFile(filename);
    } catch (const std::exception& e){
        std::cerr << "Warning: " << e.what() << "\n";
        std::cerr << "Creating empty dictionary\n";
    }
}

void Dictionary::loadFromFile(const std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()){
        throw std::runtime_error("Cannot open dictionary file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)){
        size_t delimiterPos = line.find(" -- ");
        if (delimiterPos != std::string::npos) {
            std::string eng = line.substr(0, delimiterPos);
            std::string rus = line.substr(delimiterPos + 4);
            try {
                insert(eng, rus);
            } catch (const std::exception& e){
                std::cerr << "Skipping invalid entry: " << line << " - " << e.what() << "\n";
            }
        }
    }
    file.close();
}

void Dictionary::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()){
        throw std::runtime_error("Cannot open dictionary file for writing: " + filename);
    }

    for (size_t i = 0; i < TABLE_SIZE; ++i){
        for (const auto& entry : table[i]){
            for (const auto& translation : entry.russianTranslations){
                file << entry.englishWord << " -- " << translation << "\n";
            }
        }
    }
    file.close();
}

bool Dictionary::insert(const std::string& eng, const std::string& rus){

    if (eng.empty() || rus.empty()){
        throw std::invalid_argument("English eord and translationcannot be empty");
    }

    auto result = findEntry(eng);
    size_t hashValue = result.first;
    auto it = result.second;

    if (it != table[hashValue].end()){
        it->addTranslation(rus);
        return false;
    } else{
        table[hashValue].emplace_back(eng, rus);
        return true;
    }
}

std::vector<std::string> Dictionary::search(const std::string& eng) const{
    if (eng.empty()){
        throw std::invalid_argument("Engkish word cannot be empty");
    }

    size_t hashValue = hashFunction(eng);
    for (const auto& entry : table[hashValue]){
        if (entry.englishWord == eng) {
            return entry.russianTranslations;
        }
    }
    return {};
}

bool Dictionary::remove(const std::string& eng, const std::string& rus){
    if (eng.empty()){
        throw std::invalid_argument("English word cannot be empty");
    }

    auto result = findEntry(eng);
    size_t hashValue = result.first;
    auto it = result.second;

    if (it != table[hashValue].end()){
        if (rus.empty()){
            table[hashValue].erase(it);
            return true;
        } else {
            return it->removeTranslation(rus);
        }
    }
    return false;
}

void Dictionary::printAll() const{
    for (size_t i = 0; i < TABLE_SIZE; ++i){
        for (const auto& entry : table[i]){
            std::cout << entry.englishWord << " -- ";
            for (const auto& translation : entry.russianTranslations){
                std::cout << translation << ", ";
            }
            std::cout << "\n";
        }
    }
}


void Dictionary::printStats() const {
    size_t  totalWords = 0;
    size_t nonEmptyBuckets = 0;
    size_t maxChainLength = 0;


    for (size_t i = 0; i < TABLE_SIZE; ++i){
        if (!table[i].empty()){
            nonEmptyBuckets++;
            totalWords += table[i].size();
            if (table[i].size() > maxChainLength){
                maxChainLength = table[i].size();
            }
        }
    }

    std::cout << "Dictionary statistics:\n";
    std::cout << "Total words: " << totalWords << "\n";
    std::cout << "Hash table size: " << TABLE_SIZE << "\n";
    std::cout << "Load factor: " << static_cast<double>(nonEmptyBuckets) / TABLE_SIZE << "\n";
    std::cout << "Longest chain: " << maxChainLength << "\n";
}

