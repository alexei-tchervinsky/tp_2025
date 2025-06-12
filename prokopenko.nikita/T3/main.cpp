#include "Commands.hpp"
#include <iostream>
#include <string>
#include <vector>

int main() {
  using namespace prokopenko;
  std::vector<Polygon> data;
  std::string command;

  while (std::cin >> command) {
    if (!doCommand(command, data, std::cin)) {
      std::cerr << "<INVALID COMMAND>\n";
      // очистка оставшегося ввода до конца строки
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  return 0;
}
