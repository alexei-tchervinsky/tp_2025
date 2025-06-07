#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>
#include "helpFunctions.h"

int main() {

    std::unordered_map<std::string, std::set<size_t>> index;
    std::ifstream in ("input.txt");

    if (!in.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл." << std::endl;
        return 1;
    }

    if (in.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Файл пуст." << std::endl;
        return 0;
    }

    std::string line;
    size_t nLine {1};
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            std::cout << nLine << ": " << line << std::endl;
            for (const auto& word : splitToWords(line))
            {
                index[word].insert(nLine);
            }
            ++nLine;
        }
    }

    std::cout << "\n\n";
    std::string command;

    while (std::getline(std::cin, command))
    {
        if(std::cin.eof()) break;

        std::istringstream iss(command);
        std::string cmd, parameter;
        iss >> cmd;
        if (cmd == "EXIT")
        {
            std::cout << "Завершение программы.\n";
            break;
        }
        else if (cmd == "PRINT")
        {
            std::vector<std::string> words;

            for (const auto& entry : index)
            {
              const auto& word = entry.first;
              words.push_back(word);
            }

            std::sort(words.begin(), words.end());

            for (const auto& word : words) {
                std::cout << word << ": ";
                for (auto line : index[word]) std::cout << line << " ";
                std::cout << '\n';
            }
        }
        else if (cmd == "FIND")
        {
            iss >> parameter;
            if (index.find(parameter) != index.end())
            {
                std::cout << "Слово '" << parameter << "' встречается в строках: ";
                for (const auto& line : index[parameter])
                {
                    std::cout << line << " ";
                }
                std::cout << '\n';
            }
            else
            {
                std::cout << "Слово '" << parameter << "' не найдено! \n";
            }
        }
        else
        {
            std::cerr << "Неизвестная команда!\n";
        }
    }


    return 0;
}
