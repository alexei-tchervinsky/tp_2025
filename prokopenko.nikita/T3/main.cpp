#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <limits>
#include <functional>
#include "commands.hpp"

using namespace prokopenko;

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Error: wrong input\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input) {
    std::cerr << "Error: file cannot be opened\n";
    return 1;
  }
  std::vector<Polygon> polygons;
  const double EPS = 1e-6;
  while (!input.eof()) {
    Polygon poly;
    std::streampos pos = input.tellg();
    if (input >> poly) {
      if (poly.getArea() > EPS) {
        polygons.push_back(poly);
      }
    }
    else {
      input.clear();
      input.seekg(pos);
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  // При старте выводим "With data:" и текущий набор
  std::cout << "With data:\n";
  for (const auto& p : polygons) {
    std::cout << "\t" << p << "\n";
  }

  std::map<std::string, std::function<void(std::vector<Polygon>&, std::ostream&)>>
    commands;
  commands["AREA"] = Area;
  commands["MAX"] = Max;
  commands["MIN"] = Min;
  commands["MEAN"] = Mean;
  commands["COUNT"] = Count;
  commands["PERMS"] = Perms;
  commands["MAXSEQ"] = MaxSeq;
  commands["RMECHO"] = RmEcho;
  commands["ECHO"] = Echo;
  commands["LESSAREA"] = LessArea;
  commands["INFRAME"] = InFrame;
  commands["INTERSECTIONS"] = Intersections;
  commands["SAME"] = Same;
  commands["RECTS"] = Rects;
  commands["RIGHTSHAPES"] = RightShapes;

  std::string cmd;
  while (std::cin >> cmd) {
    auto it = commands.find(cmd);
    if (it != commands.end()) {
      it->second(polygons, std::cout);
    }
    else {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
