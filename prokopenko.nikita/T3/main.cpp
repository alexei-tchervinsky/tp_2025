#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <limits>
#include <functional>
#include <algorithm>
#include <tuple>
#include <cctype>
#include "commands.hpp"
#include "polygon.hpp"

using namespace prokopenko;

int main(int argc, char* argv[]) {
  std::vector<Polygon> polygons;

  if (argc == 2) {
    std::ifstream input(argv[1]);
    if (!input) {
      std::cerr << "Error: file cannot be opened\n";
      return 1;
    }

    while (!input.eof()) {
      Polygon poly;
      std::streampos pos = input.tellg();
      if (input >> poly) {
        double a = poly.getArea();
        if (a > 1e-6) {
          polygons.push_back(poly);
        }
      }
      else {
        input.clear();
        input.seekg(pos);
        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }

    std::cout << "With data:\n";
    for (const auto& p : polygons) {
      std::cout << "\t" << p << "\n";
    }
  }

  std::map<std::string, std::function<void(const std::vector<Polygon>&, std::ostream&)>> commands;
  commands["AREA"] = Area;
  commands["MAX"] = Max;
  commands["MIN"] = Min;
  commands["MEAN"] = Mean;
  commands["SAME"] = Same;
  commands["RIGHT"] = Right;
  commands["PERMS"] = Perms;
  commands["LESS"] = Less;
  commands["MORE"] = More;
  commands["EQUAL"] = Equal;
  commands["MAXSEQ"] = MaxSeq;
  commands["RMECHO"] = RmEcho;
  commands["ECHO"] = EchoCmd;
  commands["LESSAREA"] = LessArea;
  commands["INFRAME"] = InFrame;
  commands["INTERSECTIONS"] = Intersections;
  commands["RECTS"] = Rects;
  commands["RIGHTSHAPES"] = RightShapes;

  commands["COUNT"] = [](const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "ODD") {
      CountOdd(polys, out);
    }
    else if (param == "EVEN") {
      CountEven(polys, out);
    }
    else if (!param.empty() && std::all_of(param.begin(), param.end(), ::isdigit)) {
      try {
        size_t n = std::stoul(param);
        CountN(polys, out, n);
      }
      catch (...) {
        out << "<INVALID COMMAND>\n";
      }
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
    };

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
