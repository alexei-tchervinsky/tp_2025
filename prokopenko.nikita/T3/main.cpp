#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <limits>
#include <algorithm>
#include <cctype>
#include "commands.hpp"
#include "polygon.hpp"

using namespace prokopenko;

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Error: wrong input\n";
    return 1;
  }
  std::ifstream infile(argv[1]);
  if (!infile) {
    std::cerr << "Error: file cannot be opened\n";
    return 1;
  }

  std::vector<Polygon> polygons;
  while (!infile.eof()) {
    Polygon poly;
    std::streampos pos = infile.tellg();
    if (infile >> poly) {
      polygons.push_back(poly);
    }
    else {
      infile.clear();
      infile.seekg(pos);
      infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
      size_t n = 0;
      try {
        n = std::stoul(param);
      }
      catch (...) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      CountN(polys, out, n);
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
