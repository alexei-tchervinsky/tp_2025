#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "polygon.hpp"
#include "parser.hpp"
#include "commands.hpp"

int main(int argc, char* argv[]) {
  using namespace prokopenko;

  if (argc < 2) {
    std::cerr << "Filename not provided.\n";
    return 1;
  }

  std::ifstream input(argv[1]);
  if (!input) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  std::vector<Polygon> polygons = parseFile(input);
  std::string line;
  while (std::getline(std::cin, line)) {
    executeCommand(line, polygons);
  }

  return 0;
}
