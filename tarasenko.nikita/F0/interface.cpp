#include "interface.hpp"
#include "processor.hpp"
#include "methods.hpp"
#include <iostream>
#include <sstream>
#include <unordered_map>

void showHelp() {
    std::cout << "Available commands:\n";
    std::cout << "  load <filename> - Load and process a file\n";
    std::cout << "  top <n> - Show top n most frequent words\n";
    std::cout << "  search <word> - Search for a specific word\n";
    std::cout << "  all - Show all words with frequencies\n";
    std::cout << "  clear - Clear all data\n";
    std::cout << "  help - Show this help message\n";
    std::cout << "  exit - Exit the program\n";
}

void interactiveMode() {
    std::unordered_map<std::string, int> wordCount;
    std::string command;

    std::cout << "Word Frequency Analyzer\n";
    showHelp();
    std::cout << std::endl;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, command)) {
            break; // EOF detected
        }

        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "load") {
            std::string filename;
            if (iss >> filename) {
                try {
                    wordCount.clear();
                    processFile(filename, wordCount);
                    std::cout << "File processed successfully. Total unique words: "
                        << wordCount.size() << "\n";
                }
                catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
            }
            else {
                std::cerr << "Error: Missing filename\n";
            }
        }
        else if (cmd == "top") {
            int n;
            if (iss >> n && n > 0) {
                printTopWords(wordCount, n);
            }
            else {
                std::cerr << "Error: Invalid number\n";
            }
        }
        else if (cmd == "search") {
            std::string word;
            if (iss >> word) {
                searchWord(wordCount, word);
            }
            else {
                std::cerr << "Error: Missing word\n";
            }
        }
        else if (cmd == "all") {
            printAllWords(wordCount);
        }
        else if (cmd == "clear") {
            wordCount.clear();
            std::cout << "All data cleared\n";
        }
        else if (cmd == "help") {
            showHelp();
        }
        else if (cmd == "exit") {
            break;
        }
        else if (!cmd.empty()) {
            std::cerr << "Error: Unknown command. Type 'help' for available commands.\n";
        }
    }
}