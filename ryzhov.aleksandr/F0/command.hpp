#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <set>
#include <map>
#include <functional>
#include <iosfwd>

#include "ERDictionary.hpp"

namespace ryzhov {
    // Команда
    using CommandFunction = std::function<void(ERDictionary &dictionary, std::istream &is, std::ostream &os)>;
    // Список команд
    using CommandMap = std::map<std::string, CommandFunction>;

    CommandMap createCommandMap();

    void executeCommand(const CommandMap &commands,
                        ERDictionary &dictionary,
                        const std::string &command,
                        std::istream &is,
                        std::ostream &os);

    // Вставка нового слова/перевода в словарь
    void insertCommand(ERDictionary &dictionary, std::istream &is, std::ostream &os);
    // Удаление слова/перевода из словаря
    void removeCommand(ERDictionary &dictionary, std::istream &is, std::ostream &os);
    // Вывод словаря в поток вывода
    void outputCommand(ERDictionary &dictionary, std::istream &is, std::ostream &os);
    // Поиск слова в словаре и вывод его переводов в поток вывода
    void searchCommand(ERDictionary &dictionary, std::istream &is, std::ostream &os);
    // Вывод количества слов в словаре
    void countCommand(ERDictionary &dictionary, std::istream &is, std::ostream &os);
    // Автоматическое тестирование словаря
    void testingCommand(ERDictionary &dictionary, std::istream &is, std::ostream &os);
    // Вывод списка команд словаря
    void helpCommand(ERDictionary &dictionary, std::istream &is, std::ostream &os);
}

#endif
