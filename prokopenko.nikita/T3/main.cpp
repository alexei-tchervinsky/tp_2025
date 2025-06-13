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
    std::cerr << "Error: file cannot be opened\n";
    return 1;
  }

  std::vector<Polygon> polygons;
  while (!input.eof())
  {
    Polygon poly;
    std::streampos pos = input.tellg(); // запоминаем текущую позицию
    if (input >> poly)
    {
      polygons.push_back(poly);
    }
    else
    {
      input.clear();
      input.seekg(pos); // возвращаемся к началу ошибочной фигуры
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // пропускаем строку
    }
  }

  std::map<std::string, std::function<void(const std::vector<Polygon>&, std::ostream&)>> commands;
  commands["AREA"] = prokopenko::Area;
  commands["MAX"] = prokopenko::Max;
  commands["MIN"] = prokopenko::Min;
  commands["MEAN"] = prokopenko::Mean;
  commands["SAME"] = prokopenko::Same;
  commands["RIGHT"] = prokopenko::Right;
  commands["PERMS"] = prokopenko::Perms;
  commands["LESS"] = prokopenko::Less;
  commands["MORE"] = prokopenko::More;
  commands["EQUAL"] = prokopenko::Equal;

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
