#include "Dictionary.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

void printHelp() {
    std::cout << "Available commands:\n"
              << "  insert <english_word> <translation> - Add word to dictionary\n"
              << "  search <english_word> - Search for word translations\n"
              << "  delete <english_word> - Remove word from dictionary\n"
              << "  list - Show all words in dictionary\n"
              << "  help - Show this help message\n"
              << "  exit - Exit the program\n";
}

std::vector<std::string> splitCommand(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

void processCommand(Dictionary& dict, const std::vector<std::string>& tokens) {
    if (tokens.empty()) return;

    const std::string& command = tokens[0];

    try {
        if (command == "insert" && tokens.size() >= 3) {
            std::string translations;
            for (size_t i = 2; i < tokens.size(); ++i) {
                if (i > 2) translations += " ";
                translations += tokens[i];
            }
            dict.insert(tokens[1], translations);
            std::cout << "Word '" << tokens[1] << "' added successfully.\n";
        }
        else if (command == "search" && tokens.size() >= 2) {
            auto translations = dict.search(tokens[1]);
            if (!translations.empty()) {
                std::cout << tokens[1] << " translations:\n";
                for (const auto& t : translations) {
                    std::cout << "- " << t << "\n";
                }
            } else {
                std::cout << "Word '" << tokens[1] << "' not found.\n";
            }
        }
        else if (command == "delete" && tokens.size() >= 2) {
            if (dict.remove(tokens[1])) {
                std::cout << "Word '" << tokens[1] << "' deleted successfully.\n";
            } else {
                std::cout << "Word '" << tokens[1] << "' not found.\n";
            }
        }
        else if (command == "list") {
            dict.printAll();
        }
        else if (command == "help") {
            printHelp();
        }
        else if (command == "exit") {
            exit(0);
        }
        else {
            std::cout << "Invalid command or arguments. Type 'help' for usage.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

int main() {
    Dictionary dict;
    std::cout << "English-Russian Dictionary (STL version)\n";
    printHelp();

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) {
            break; // Handle EOF (Ctrl+D or Ctrl+Z)
        }

        auto tokens = splitCommand(line);
        if (!tokens.empty()) {
            processCommand(dict, tokens);
        }
    }

    return 0;
}

