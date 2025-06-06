#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <functional>
#include <vector>

#include "AVLDictionary.hpp"
#include "Reader.hpp"
#include "Writer.hpp"

int main() {
    AVLDictionary dict;
    Reader reader;
    Writer writer;

    std::map<std::string, std::function<void(std::istream&)>> commands;

    commands["help"] = [&](std::istream&) {
        std::cout << "Доступные команды:\n";
        std::cout << "  read <filename> - считать слова из файла\n";
        std::cout << "  insert <word> - добавить слово в словарь\n";
        std::cout << "  remove <word> - удалить слово из словаря\n";
        std::cout << "  clear - очистить словарь\n";
        std::cout << "  freq <word> - вывести частоту слова\n";
        std::cout << "  print - вывести все слова и частоты\n";
        std::cout << "  top - вывести топ-3 самых частых слова\n";
        std::cout << "  help - вывести список команд\n";
        std::cout << "  (Ctrl+D / Ctrl+Z) - завершить ввод\n";
    };

    commands["read"] = [&](std::istream& in) {
        std::string filename;
        if (!(in >> filename)) {
            std::cerr << "<ENTER FILE>\n";
            return;
        }

        std::ifstream file(filename);
        if (!file) {
            std::cerr << "<CANNOT OPEN>\n";
            return;
        }
        dict = reader.read(file, dict);
    };

    commands["insert"] = [&](std::istream& in) {
        std::string word;
        if (!(in >> word)) {
            std::cerr << "<ENTER WORD>\n";
            return;
        };

        dict.insert(word);
    };


    commands["remove"] = [&](std::istream& in) {
        std::string word;
        if (!(in >> word)) {
            std::cerr << "<ENTER WORD>\n";
            return;
        };

        if (!dict.removeWord(word)) {
            std::cerr << "<NOT FOUND>\n";
        }
    };

    commands["clear"] = [&](std::istream& in) {
        dict.clear();
    };

    commands["freq"] = [&](std::istream& in) {
        std::string word;
        if (!(in >> word)) {
            std::cerr << "<ENTER WORD>\n";
            return;
        };
        std::cout << dict.getFreq(word) << "\n";
    };

    commands["print"] = [&](std::istream& in) {
        dict.printAll(std::cout);
    };

    commands["top"] = [&](std::istream& in) {
        dict.printTopThree(std::cout);
    };

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        auto it = commands.find(cmd);
        if (it != commands.end()) {
            it->second(iss);
        } else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}
