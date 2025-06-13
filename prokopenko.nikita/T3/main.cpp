#include "commands.hpp"
#include "polygon.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

int main(int argc, char* argv[]) {
  // Проверка аргументов командной строки
  if (argc < 2) {
    std::cerr << "Error: missing input file" << std::endl;
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Error: cannot open file" << std::endl;
    return 1;
  }
  // Чтение фигур из файла
  std::vector<Polygon> shapes;
  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) continue;
    std::istringstream iss(line);
    Polygon poly;
    if (!(iss >> poly)) {
      // Некорректная строка, игнорируем
      continue;
    }
    if (poly.getArea() > 1e-6) {
      shapes.push_back(poly);
    }
  }
  file.close();

  // Удаление дубликатов фигур
  std::sort(shapes.begin(), shapes.end());
  shapes.erase(std::unique(shapes.begin(), shapes.end()), shapes.end());

  // Обработка команд из стандартного ввода
  while (std::getline(std::cin, line)) {
    if (line.empty()) continue;
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;
    if (cmd == "SAME" || cmd == "PERMS" || cmd == "EQUAL" || cmd == "COUNT") {
      Polygon param;
      if (!(iss >> param)) {
        std::cout << "<INVALID COMMAND>" << std::endl;
        continue;
      }
      if (cmd == "SAME") {
        doSAME(param, shapes);
      }
      else if (cmd == "PERMS") {
        doPERMS(param, shapes);
      }
      else if (cmd == "EQUAL") {
        doEQUAL(param, shapes);
      }
      else if (cmd == "COUNT") {
        doCOUNT(param, shapes);
      }
    }
    else {
      std::cout << "<INVALID COMMAND>" << std::endl;
    }
  }
  return 0;
}
