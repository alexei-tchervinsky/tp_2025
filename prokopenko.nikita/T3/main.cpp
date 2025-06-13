#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <limits>
#include <functional>
#include <iterator>
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
  std::vector<Polygon> polygons;
  while (!input.eof())
  {
    std::copy(
      std::istream_iterator<Polygon>{input},
      std::istream_iterator<Polygon>{},
      std::back_inserter(polygons));
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
