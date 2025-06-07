#include <set>
#include <map>
#include <functional>
#include <iosfwd>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iterator>
#include <limits>

#include "command.hpp"
#include "ERDictionary.hpp"
#include "iofmtguard.hpp"

namespace ryzhov {

    CommandMap createCommandMap() {
        using namespace std::placeholders;
        return {{"-i", std::bind(insertCommand, _1, _2, _3)},
                  {"-r", std::bind(removeCommand, _1, _2, _3)},
                  {"-o", std::bind(outputCommand, _1, _2, _3)},
                  {"-s", std::bind(searchCommand, _1, _2, _3)},
                  {"-c", std::bind(countCommand, _1, _2, _3)},
                  {"-at", std::bind(testingCommand, _1, _2, _3)},
                  {"-h", std::bind(helpCommand, _1, _2, _3)}
        };
    }

    void executeCommand(const CommandMap &commands,
                        ERDictionary &dictionary,
                        const std::string &command,
                        std::istream &is,
                        std::ostream &os) {
        auto it = commands.find(command);
        if (it == commands.end())
            throw std::invalid_argument("Invalid command. Check -h for list of commands.");
        it->second(dictionary, is, os);
    }

    void insertCommand(ERDictionary &dictionary, std::istream &is, std::ostream &) {
        is >> dictionary;
    }

    void removeCommand(ERDictionary &dictionary, std::istream &is, std::ostream &os) {
        std::string line;
        std::string enWord;
        std::string ruTranslate;
        // Получаем строку переводов с пробелами
        std::getline(is, line);
        // Превращаем ее в поток
        std::istringstream iss(line);
        // Достаем английское слово
        iss >> enWord;
        // Выходим, если слова нет
        if (dictionary.find(enWord) == dictionary.end()){
            os << "Word not found.\n";
            return;
        }
        // Флаг для разделения удаления английского и русского слова
        bool deleted = false;
        // Достаем из потока переводы
        while (iss >> ruTranslate) {
            dictionary[enWord].erase(ruTranslate);
            deleted = true;
        }
        if (!deleted) dictionary.erase(enWord);
    }


    void outputCommand(ERDictionary &dictionary, std::istream &, std::ostream &os) {
        iofmtguard guard(os);
        for (auto miter{dictionary.begin()}; miter != dictionary.end(); ++miter)
        {
            os << miter->first;
            os << ": ";
            std::copy(miter->second.begin(), miter->second.end(),
                      std::ostream_iterator<std::string>(os, ", "));
            os << "\n";
        }
    }

    void searchCommand(ERDictionary &dictionary, std::istream &is, std::ostream &os) {
        iofmtguard guard(os);
        std::string word;
        is >> word;

        if (is && dictionary.find(word) != dictionary.end()) {
            std::copy(dictionary[word].begin(), dictionary[word].end(),
                      std::ostream_iterator<std::string>(os, ", "));
            std::cout << "\n";
        }
        else {
            os << "Word not found.\n";
        }
    }

    void countCommand(ERDictionary &dictionary, std::istream &, std::ostream &os) {
        iofmtguard guard(os);
        os << "Words in dictionary: " << dictionary.size() << ".\n";
    }

    void testingCommand(ERDictionary &, std::istream &, std::ostream &os) {
        // TODO: автотесты
        os << "no tests yet...\n";
    }

    void helpCommand(ERDictionary &, std::istream &, std::ostream &os) {
        os << "Список команд (почти как в линуксе):\n"
              "-i <enWord> <ruTranslation> <ruTranslation> ...\n"
              "    - добавление нового слова в словарь"
              " или добавление нового перевода слову в словаре.\n"
              "-r <enWord> | <enWord> <ruTranslate> <ruTranslate> ...\n"
              "    - удаление английского слова из словаря.\n"
              "-o\n"
              "    - вывод словаря в консоль списком "
              "в отсортированном по возрастанию.\n"
              "-s <enWord>\n"
              "    - поиск слова в словаре.\n"
              "-c\n"
              "    - вывод количества английских слов в словаре.\n"
              "-at\n"
              "    - автоматическое тестирование.\n"
              "-h\n"
              "    - вывод списка команд (этого сообщения).\n";
    }
}
