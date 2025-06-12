#include "Polygon.hpp"
#include "Commands.hpp"
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::vector<Polygon> polygons;
  std::string line;

  while (std::getline(std::cin, line)) {
    executeCommand(line, polygons);
  }

  return 0;
}
