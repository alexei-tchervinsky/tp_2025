#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
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
  std::string line;
  while (std::getline(input, line))
  {
    if (line.empty())
      continue;

    std::istringstream iss(line);
    Polygon poly;
    if (iss >> poly)
    {
      char extra;
      if (!(iss >> extra)) // проверка: не должно быть ничего лишнего
      {
        polygons.push_back(poly);
      }
    }
  }

  std::map<std::string, std::function<void(const std::vector<Polygon>&, std::ostream&)>> commands;
  commands["AREA"] = [](const std::vector<Polygon>& polys, std::ostream& out)
    {
      std::string arg;
      if (std::cin.peek() != '\n' && std::cin >> arg)
      {
        out << "<INVALID COMMAND>\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
      }
      Area(polys, out);
    };
  commands["MAX"] = commands["MIN"] = commands["MEAN"] = commands["SAME"] =
    commands["RIGHT"] = commands["PERMS"] = commands["LESS"] =
    commands["MORE"] = commands["EQUAL"] = commands["AREA"];

  commands["COUNT"] = [](const std::vector<Polygon>& polys, std::ostream& out)
    {
      std::string param;
      std::cin >> param;
      if (param == "ODD")
      {
        CountOdd(polys, out);
      }
      else if (param == "EVEN")
      {
        CountEven(polys, out);
      }
      else
      {
        try
        {
          size_t n = std::stoul(param);
          CountN(polys, out, n);
        }
        catch (...)
        {
          out << "<INVALID COMMAND>\n";
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
    };

  std::string cmd;
  while (std::cin >> cmd)
  {
    auto it = commands.find(cmd);
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
