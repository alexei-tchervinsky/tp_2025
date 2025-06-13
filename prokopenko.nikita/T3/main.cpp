#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <limits>
#include "commands.hpp"
#include "polygon.hpp"

using namespace prokopenko;

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Error: wrong input\n";
    return 1;
  }
  std::ifstream infile(argv[1]);
  if (!infile) {
    std::cerr << "Error: file cannot be opened\n";
    return 1;
  }

  // Построчно читаем файл; блоки разделены пустыми строками.
  // Для каждого блока сразу ожидаем одну команду из stdin и выполняем её на блоке.
  std::string line;
  std::vector<std::string> blockLines;
  // Читаем все команды заранее в очередь
  std::vector<std::string> commandsQueue;
  {
    std::string cmd;
    while (std::cin >> cmd) {
      commandsQueue.push_back(cmd);
    }
  }
  size_t cmdIdx = 0;

  auto processBlock = [&](const std::vector<std::string>& lines) {
    // Парсим все валидные полигоны из lines
    std::vector<Polygon> polys;
    for (const auto& ln : lines) {
      std::istringstream iss(ln);
      Polygon p;
      if (iss >> p) {
        polys.push_back(p);
      }
      // иначе пропускаем некорректную строку
    }
    if (cmdIdx < commandsQueue.size()) {
      const std::string& cmd = commandsQueue[cmdIdx++];
      static std::map<std::string, std::function<void(const std::vector<Polygon>&, std::ostream&)>> cmap = {
          {"AREA", Area},
          {"MAX", Max},
          {"MIN", Min},
          {"MEAN", Mean},
          {"SAME", Same},
          {"RIGHT", Right},
          {"PERMS", Perms},
          {"LESS", Less},
          {"MORE", More},
          {"EQUAL", Equal},
          {"COUNT", nullptr} // обрабатывается ниже
      };
      if (cmd == "COUNT") {
        // вызываем лямбду из commands.cpp
        std::string param;
        if (!(std::cin >> param)) {
          std::cout << "<INVALID COMMAND>\n";
        }
        else if (param == "ODD") {
          CountOdd(polys, std::cout);
        }
        else if (param == "EVEN") {
          CountEven(polys, std::cout);
        }
        else if (std::all_of(param.begin(), param.end(), ::isdigit)) {
          try {
            size_t n = std::stoul(param);
            CountN(polys, std::cout, n);
          }
          catch (...) {
            std::cout << "<INVALID COMMAND>\n";
          }
        }
        else {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
      else {
        auto it = cmap.find(cmd);
        if (it != cmap.end() && it->second) {
          it->second(polys, std::cout);
        }
        else {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    }
    };

  while (std::getline(infile, line)) {
    if (line.empty()) {
      // конец блока
      processBlock(blockLines);
      blockLines.clear();
    }
    else {
      blockLines.push_back(line);
    }
  }
  // последний блок, если есть
  if (!blockLines.empty()) {
    processBlock(blockLines);
  }
  // если команд осталось, но блоков закончилось, для каждой лишней команды выводим <INVALID COMMAND>
  while (cmdIdx < commandsQueue.size()) {
    std::cout << "<INVALID COMMAND>\n";
    ++cmdIdx;
  }
  return 0;
}
