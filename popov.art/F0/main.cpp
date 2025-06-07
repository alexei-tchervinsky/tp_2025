#include "dictionary.hpp"
#include <iostream>
#include <sstream>
void runDictionary() {
    DictionaryHashTable dict;
    std::string command;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, command)) break;
        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;
        if (cmd == "INSERT") {
            std::string key, translation;
            if (iss >> key >> translation) {
                dict.insert(key, translation);
            }
        }
        else if (cmd == "SEARCH") {
            std::string key;
            if (iss >> key) {
                auto entry = dict.search(key);
                if (entry) {
                    for (const auto& tr : entry->getTranslations()) {
                        std::cout << tr << " ";
                    }
                    std::cout << "\n";
                }
            }
        }
        else if (cmd == "REMOVE") {
            std::string key;
            if (iss >> key) {
                dict.remove(key);
            }
        }
        else if (cmd == "EXIT") {
            break;
        }
    }
}
int main() {
    runDictionary();
    return 0;
}
