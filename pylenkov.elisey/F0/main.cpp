#include "HashTable.hpp"
#include <iostream>
#include <sstream>
#include <string>

void processCommand(HashTable& dictionary, const std::string& command)
{
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    try {
        if (cmd == "add")
        {
            std::string word;
            iss >> word;
            std::vector<std::string> translations;
            std::string tr;
            while (iss >> tr)
            {
                translations.push_back(tr);
            }
            dictionary.insert(word, translations);
            std::cout << "OK: Слово \"" << word << "\" добавлено.\n";
        }
        else if (cmd == "find")
        {
            std::string word;
            iss >> word;
            auto translations = dictionary.search(word);
            std::cout << "Переводы: ";
            if (!translations.empty())
            {
                std::cout << translations[0];
                for (size_t i = 1; i < translations.size(); ++i)
                {
                    std::cout << ", " << translations[i];
                }
            }
            std::cout << ";\n";
        }
        else if (cmd == "remove")
        {
            std::string word;
            iss >> word;
            dictionary.remove(word);
            std::cout << "OK: Слово \"" << word << "\" удалено.\n";
        }
        else if (cmd == "display")
        {
            dictionary.display();
        }
        else if (cmd == "exit")
        {
            std::exit(0);
        }
        else
        {
            std::cout << "Ошибка: Неизвестная команда.\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}

int main()
{
    HashTable dictionary(10);

    std::cout << "Англо-русский словарь. Команды:\n"
              << "add <слово> <перевод1> <перевод2> ...\n"
              << "find <слово>\n"
              << "remove <слово>\n"
              << "display\n"
              << "exit\n";

    std::string command;
    while (std::cout << "> " && std::getline(std::cin, command))
    {
        processCommand(dictionary, command);
    }

    return 0;
}