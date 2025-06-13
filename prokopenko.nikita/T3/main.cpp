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
  if (argc != 2)
  {
    std::cerr << "Error: wrong input\n";
    return 1;
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Error: cannot open file\n";
    return 1;
  }

  std::vector<Polygon> polygons;
  Polygon polygon;
  while (input >> polygon)
  {
    polygons.push_back(polygon);
  }
  input.clear();
  input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::map<std::string, std::function<void(const std::vector<Polygon>&, std::ostream&)>> commands = {
    {"AREA", Area},
    {"MAX", Max},
    {"MIN", Min},
    {"MEAN", Mean},
    {"SAME", Same},
    {"RIGHT", Right},
    {"PERMS", Perms},
    {"LESS", Less},
    {"MORE", More},
    {"EQUAL", Equal}
  };

  std::string parameter;
  while (std::cin >> parameter)
  {
    auto it = commands.find(parameter);
    if (it != commands.end())
    {
      it->second(polygons, std::cout);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  return 0;
}
