#include "Polygon.hpp"
#include "Commands.hpp"
#include "iofmtguard.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <inputfile>\n";
    return 1;
  }

  std::ifstream f(argv[1]);
  if (!f) {
    std::cerr << "Failed to open file\n";
    return 2;
  }

  std::vector<prokopenko::Polygon> polygons;
  prokopenko::Polygon p;
  while (f >> p) {
    polygons.push_back(p);
  }

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) continue;
    std::istringstream iss(line);
    std::string command;
    iss >> command;
    prokopenko::doCommand(command, polygons, iss);
  }

  return 0;
}
