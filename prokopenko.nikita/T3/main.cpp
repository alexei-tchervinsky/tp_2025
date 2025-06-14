#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <limits>
#include <functional>
#include <algorithm>
#include <set>
#include "commands.hpp"

using namespace prokopenko;

// Проверка, что все точки в многоугольнике различны (по координатам)
static bool allPointsDistinct(const Polygon& poly) {
  std::set<std::pair<int, int>> st;
  for (auto& pt : poly.points) {
    st.insert({ pt.x, pt.y });
  }
  return st.size() == poly.points.size();
}

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
  // Читаем построчно полигоны: некорректные строки игнорируем
  while (!input.eof()) {
    Polygon poly;
    std::streampos pos = input.tellg();
    if (input >> poly) {
      double area = poly.getArea();
      if (area > 1e-6 && allPointsDistinct(poly)) {
        polygons.push_back(poly);
      }
    }
    else {
      input.clear();
      input.seekg(pos);
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  // Команды: принимают polygons, входной поток и выходной поток
  std::map<std::string, std::function<void(const std::vector<Polygon>&, std::istream&, std::ostream&)>> commands;
  commands["AREA"] = Area;
  commands["MAX"] = Max;
  commands["MIN"] = Min;
  commands["MEAN"] = [](const auto& polys, std::istream& in, std::ostream& out) {
    Mean(polys, out);
    };
  commands["SAME"] = Same;
  commands["RIGHT"] = [](const auto& polys, std::istream& in, std::ostream& out) {
    Right(polys, out);
    };
  commands["PERMS"] = Perms;
  commands["LESS"] = Less;
  commands["MORE"] = More;
  commands["EQUAL"] = Equal;
  commands["COUNT"] = Count;

  std::string cmd;
  while (std::cin >> cmd) {
    auto it = commands.find(cmd);
    if (it != commands.end()) {
      it->second(polygons, std::cin, std::cout);
    }
    else {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
