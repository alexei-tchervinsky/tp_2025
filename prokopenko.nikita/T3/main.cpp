#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Polygon.hpp"
#include "Commands.hpp"

using namespace prokopenko;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "<INVALID COMMAND>\n";
    return 1;
  }
  std::ifstream f(argv[1]);
  if (!f) {
    std::cerr << "<INVALID COMMAND>\n";
    return 1;
  }
  std::vector<Polygon> polygons;
  std::string line;
  while (std::getline(f, line)) {
    std::istringstream iss(line);
    Polygon p;
    if (iss >> p) {
      iss >> std::ws;
      if (iss.eof()) {
        polygons.push_back(std::move(p));
      }
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
    else if (cmd == "RIGHTSHAPES") rightShapesCommand(polygons, iss);
    else std::cout << "<INVALID COMMAND>\n";
  }
  return 0;
}
