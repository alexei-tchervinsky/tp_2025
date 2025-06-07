#include "Graph.hpp"
#include <iostream>
#include <sstream>

int main() {
  Graph g;
  std::string line, command;

  std::cout << "Введите команду (help — список команд):\n";

  while (std::cout << "> ", std::getline(std::cin, line)) {
    std::istringstream iss(line);
    iss >> command;

    try {
      if (command == "add_vertex") {
        std::string name;
        iss >> name;
        g.add_vertex(name);
      }
      else if (command == "remove_vertex") {
        std::string name;
        iss >> name;
        g.remove_vertex(name);
      }
      else if (command == "add_edge") {
        std::string from, to;
        iss >> from >> to;
        g.add_edge(from, to);
      }
      else if (command == "dfs") {
        std::string start;
        iss >> start;
        g.dfs(start);
      }
      else if (command == "super_dfs") {
        g.SuperDfs();
      }
      else if (command == "topsort") {
        g.Topsort();
      }
      else if (command == "print") {
        g.print();
      }
      else if (command == "help") {
        std::cout << "Список доступных команд:\n"
          << "add_vertex <name>       — добавить вершину\n"
          << "remove_vertex <name>    — удалить вершину\n"
          << "add_edge <from> <to>    — добавить ребро\n"
          << "dfs <start_vertex>      — выполнить DFS от заданной вершины\n"
          << "super_dfs               — DFS по всем вершинам\n"
          << "topsort                 — топологическая сортировка\n"
          << "print                   — вывести граф\n"
          << "help                    — список доступных команд\n"
          << "exit                    — выход из программы\n";
      }
      else if (command == "exit") {
        std::cout << "Выход...\n";
        break;
      }
      else {
        std::cerr << "Неизвестная команда. Введите 'help' для списка команд.\n";
      }
    }
    catch (const std::exception& e) {
      std::cerr << "Ошибка: " << e.what() << "\n";
    }
  }

  return 0;
}
