#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
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
  std::vector<Polygon> data;
  std::string line;
  while (std::getline(f, line)) {
    std::istringstream iss(line);
    Polygon p;
    if (!(iss >> p)) continue;
    iss >> std::ws;
    if (!iss.eof()) continue;
    data.push_back(std::move(p));
  }
  std::map<std::string,
    std::function<void(std::vector<Polygon>&, std::istream&)>>
    cmds = {
        {"AREA",
         [](auto& d, auto& in) { areaCommand(d, in); }},
        {"COUNT",
         [](auto& d, auto& in) { countCommand(d, in); }},
        {"MAX",
         [](auto& d, auto& in) { maxCommand(d, in); }},
        {"MIN",
         [](auto& d, auto& in) { minCommand(d, in); }},
        {"ECHO",
         [](auto& d, auto& in) { echoCommand(d, in); }},
        {"RIGHTSHAPES",
         [](auto& d, auto& in) { rightShapesCommand(d, in); }}
  };
  while (std::getline(std::cin, line)) {
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;
    auto it = cmds.find(cmd);
    if (it != cmds.end()) {
      it->second(data, iss);
    }
    else {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
  return 0;
}
