#include "hash_table.h"
#include <iostream>
#include <sstream>
#include <string>

void ProcessCommand(HashTable& dict, const std::string& command) {
    std::istringstream iss(command);
    std::string cmd, key, value;
    iss >> cmd;

    try {
        if (cmd == "insert" && iss >> key >> value) {
            dict.Insert(key, value);
            std::cout << "Inserted: " << key << " -> " << value << "\n";
        }
        else if (cmd == "search" && iss >> key) {
            auto translations = dict.Search(key);
            if (translations.empty()) {
                std::cout << "No translations found for '" << key << "'\n";
            } else {
                std::cout << "Translations for '" << key << "':\n";
                for (const auto& tr : translations) {
                    std::cout << "  " << tr << "\n";
                }
            }
        }
        else if (cmd == "remove" && iss >> key) {
            dict.Remove(key);
            std::cout << "Removed: " << key << "\n";
        }
        else if (cmd == "print_all") {
            std::cout << "All dictionary entries:\n";
            dict.PrintAll();
        }
        else if (cmd == "print_bucket" && iss >> key) {
            size_t hash_val = dict.HashFunction(key);
            std::cout << "Bucket for '" << key << "' (hash " << hash_val << "):\n";
            dict.PrintBucket(hash_val);
        }
        else if (cmd == "help") {
            std::cout << "Available commands:\n"
                      << "  insert <key> <value> - Add translation\n"
                      << "  search <key>        - Search translations\n"
                      << "  remove <key>        - Remove word\n"
                      << "  print_all           - Print all entries\n"
                      << "  print_bucket <key>  - Print bucket for key\n"
                      << "  help                - Show this help\n"
                      << "  exit                - Exit program\n";
        }
        else if (cmd == "exit") {
            std::cout << "Exiting...\n";
            exit(0);
        }
        else {
            std::cout << "Invalid command. Type 'help' for available commands.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

int main() {
    HashTable dict;
    std::cout << "Dictionary program. Type 'help' for commands.\n";

    std::string command;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, command)) {
            break; // EOF reached
        }
        if (!command.empty()) {
            ProcessCommand(dict, command);
        }
    }

    return 0;
}