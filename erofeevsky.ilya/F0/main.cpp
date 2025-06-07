#include <iostream>
#include <string>
#include "dictionary.hpp"

void printHelp() {
    std::cout << "Available commands:\n"
              << "  insert <eng> <rus> - Add a word and its translation\n"
              << "  search <eng>      - Search for translations of a word\n"
              << "  remove <eng> [rus] - Remove a word or specific translation\n"
              << "  print             - Print all dictionary entries\n"
              << "  stats             - Print dictionary statistics\n"
              << "  load <filename>   - Load dictionary from file\n"
              << "  save <filename>    - Save dictionary to file\n"
              << "  help              - Show this help message\n"
              << "  exit              - Exit the program\n";
}

int main() {
    Dictionary dict;
    std::string command;

    std::cout << "Dictionary Console Interface\n";
    std::cout << "Type 'help' for list of commands\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, command)) {
            break;
        }

        try {
            if (command.empty()) {
                continue;
            }
            else if (command == "help") {
                printHelp();
            }
            else if (command == "exit") {
                break;
            }
            else if (command == "print") {
                dict.printAll();
            }
            else if (command == "stats") {
                dict.printStats();
            }
            else if (command.substr(0, 6) == "insert") {
                size_t space1 = command.find(' ', 7);
                if (space1 == std::string::npos) {
                    std::cerr << "Usage: insert <english> <russian>\n";
                    continue;
                }
                std::string eng = command.substr(7, space1 - 7);
                std::string rus = command.substr(space1 + 1);
                dict.insert(eng, rus);
                std::cout << "Word added successfully\n";
            }
            else if (command.substr(0, 6) == "search") {
                if (command.length() <= 7) {
                    std::cerr << "Usage: search <english>\n";
                    continue;
                }
                std::string eng = command.substr(7);
                auto translations = dict.search(eng);
                if (translations.empty()) {
                    std::cout << "No translations found\n";
                } else {
                    std::cout << "Translations: ";
                    for (const auto& t : translations) {
                        std::cout << t << ", ";
                    }
                    std::cout << "\n";
                }
            }
            else if (command.substr(0, 6) == "remove") {
                size_t space1 = command.find(' ', 7);
                if (space1 == std::string::npos) {
                    if (command.length() <= 7) {
                        std::cerr << "Usage: remove <english> [russian]\n";
                        continue;
                    }
                    std::string eng = command.substr(7);
                    if (dict.remove(eng)) {
                        std::cout << "Word removed successfully\n";
                    } else {
                        std::cout << "Word not found\n";
                    }
                } else {
                    std::string eng = command.substr(7, space1 - 7);
                    std::string rus = command.substr(space1 + 1);
                    if (dict.remove(eng, rus)) {
                        std::cout << "Translation removed successfully\n";
                    } else {
                        std::cout << "Translation not found\n";
                    }
                }
            }
            else if (command.substr(0, 4) == "load") {
                if (command.length() <= 5) {
                    std::cerr << "Usage: load <filename>\n";
                    continue;
                }
                std::string filename = command.substr(5);
                dict.loadFromFile(filename);
                std::cout << "Dictionary loaded from " << filename << "\n";
            }
            else if (command.substr(0, 4) == "save") {
                if (command.length() <= 5) {
                    std::cerr << "Usage: save <filename>\n";
                    continue;
                }
                std::string filename = command.substr(5);
                dict.saveToFile(filename);
                std::cout << "Dictionary saved to " << filename << "\n";
            }
            else {
                std::cerr << "Unknown command. Type 'help' for available commands.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
