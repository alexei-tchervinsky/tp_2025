#include "Dictionary.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// –азбивает строку по пробелам, сохран€€ краевые пустые токены при необходимости
std::vector<std::string> splitBySpace(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    // ≈сли строка начинаетс€ с пробела, добавл€ем пустой токен в начало
    if (!input.empty() && input.front() == ' ') {
        tokens.insert(tokens.begin(), "");
    }

    return tokens;
}

int main() {
    Dictionary dict;

    std::cout << "Enter commands:\n"
              << "  insert <word> <translation>\n"
              << "  search <word>\n"
              << "  delete <word>\n"
              << "  Ctrl+D (Linux) or Ctrl+Z (Windows) to exit\n";

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string command;
        if (!(iss >> command)) continue; // ѕропускаем пустую строку

        try {
            if (command == "insert") {
                auto parts = splitBySpace(line);

                if (parts.size() < 3 || parts[0] != "insert") {
                    std::cerr << "Invalid arguments for 'insert'\n";
                    continue;
                }

                std::string key = parts[1];
                std::string value = parts[2];

                if (key.empty() || isBlank(key)) {
                    std::cerr << "Error: Key cannot be empty or whitespace-only.\n";
                    continue;
                }

                if (value.empty() || isBlank(value)) {
                    std::cerr << "Error: Translation cannot be empty or whitespace-only.\n";
                    continue;
                }

                dict.insert(key, value);
                std::cout << "Inserted: " << key << " -> " << value << "\n";


            } else if (command == "search") {
                auto parts = splitBySpace(line);
                if (parts.size() < 2 || parts[0] != "search") {
                    std::cerr << "Missing argument for 'search'\n";
                    continue;
                }

                std::string key = parts[1];
                if (key.empty() || isBlank(key)) {
                    std::cerr << "Error: Key cannot be empty or whitespace-only.\n";
                    continue;
                }

                auto res = dict.search(key);
                if (!res.empty()) {
                    std::cout << key << ": ";
                    for (const auto& t : res)
                        std::cout << t << " ";
                    std::cout << "\n";
                } else {
                    std::cout << key << " not found\n";
                }


            } else if (command == "delete") {
                auto parts = splitBySpace(line);
                if (parts.size() < 2 || parts[0] != "delete") {
                    std::cerr << "Missing argument for 'delete'\n";
                    continue;
                }

                std::string key = parts[1];
                if (key.empty() || isBlank(key)) {
                    std::cerr << "Error: Key cannot be empty or whitespace-only.\n";
                    continue;
                }

                if (dict.remove(key))
                    std::cout << "Deleted: " << key << "\n";
                else
                    std::cout << key << " not found\n";


            } else {
                std::cerr << "Unknown command: " << command << "\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}

