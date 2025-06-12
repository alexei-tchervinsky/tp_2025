#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Polygon.hpp"
#include "Commands.hpp"

using namespace prokopenko;

int main() {
  std::vector<Polygon> polygons;
  std::string line;

  while (std::getline(std::cin, line) && !line.empty()) {
    std::istringstream iss(line);
    Polygon p;
    if (iss >> p) {
      polygons.push_back(p);
    }
  }

  while (std::getline(std::cin, line)) {
    if (line.empty()) continue;
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;

    if (cmd == "AREA") areaCommand(polygons, iss);
    else if (cmd == "COUNT") countCommand(polygons, iss);
    else if (cmd == "MAX") maxCommand(polygons, iss);
    else if (cmd == "MIN") minCommand(polygons, iss);
    else if (cmd == "ECHO") echoCommand(polygons, iss);
    else if (cmd == "RIGHT") rightShapesCommand(polygons, iss);
    else std::cout << "<INVALID COMMAND>\n";
  }

  return 0;
}
