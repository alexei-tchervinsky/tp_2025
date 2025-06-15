#include "HashTable.hpp"
#include "extra_functions.hpp"
#include <iostream>
#include <string>

int main()
{
    HashTable table;
    std::string filename;
    std::string command;
    std::string word;

    std::cout << "Available commands:\n";
    std::cout << "  load <filename> - Load words from file\n";
    std::cout << "  add <word>      - Add a word manually\n";
    std::cout << "  search <word>   - Search for a word\n";
    std::cout << "  remove <word>   - Remove a word\n";
    std::cout << "  top             - Show top 3 words\n";
    std::cout << "  exit            - Exit the program\n\n";

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command.substr(0, 5) == "load ")
        {
            filename = command.substr(5);
            if (fillTable(table, filename))
            {
                std::cout << "File loaded successfully.\n";
            }
        }
        else if (command.substr(0, 4) == "add ")
        {
            word = command.substr(4);
            word = checkWord(word);
            if (!word.empty()) {
                table.insert(word);
                std::cout << "Word added: " << word << "\n";
            }
            else {
                std::cout << "Invalid word.\n";
            }
        }
        else if (command.substr(0, 7) == "search ")
        {
            word = command.substr(7);
            size_t count = table.search(word);
            std::cout << word << " appears " << count << " times.\n";
        }
        else if (command.substr(0, 7) == "remove ")
        {
            word = command.substr(7);
            table.remove(word);
            std::cout << "Word removed (if existed).\n";
        }
        else if (command == "top")
        {
            table.getThree();
        }
        else if (command == "exit")
        {
            break;
        }
        else
        {
            std::cerr << "FATAL ERROR: Unknown command.\n";
            return 1;
        }
    }

    return 0;
}
