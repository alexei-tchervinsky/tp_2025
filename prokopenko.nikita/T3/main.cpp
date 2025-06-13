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
    if (line.empty()) continue;

    std::istringstream iss(line);
    Polygon poly;
    if (iss >> poly)
    {
      char extra;
      if (!(iss >> extra)) // make sure full line is valid
        polygons.push_back(poly);
    }
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    if (cmd == "COUNT")
    {
      std::string arg;
      if (!(std::cin >> arg))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      if (arg == "ODD")
        CountOdd(polygons, std::cout);
      else if (arg == "EVEN")
        CountEven(polygons, std::cout);
      else
      {
        try
        {
          size_t n = std::stoul(arg);
          if (n < 3)
            std::cout << "<INVALID COMMAND>\n";
          else
            CountN(polygons, std::cout, n);
        }
        catch (...)
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    }
    else if (cmd == "AREA")
    {
      std::string arg;
      if (!(std::cin >> arg))
      {
        Area(polygons, std::cout);
        continue;
      }

      if (arg == "ODD")
        AreaOdd(polygons, std::cout);
      else if (arg == "EVEN")
        AreaEven(polygons, std::cout);
      else if (arg == "MEAN")
        MeanArea(polygons, std::cout);
      else
      {
        try
        {
          size_t n = std::stoul(arg);
          AreaN(polygons, std::cout, n);
        }
        catch (...)
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    }
    else if (cmd == "MAX")
    {
      std::string arg;
      if (!(std::cin >> arg))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      if (arg == "AREA")
        MaxArea(polygons, std::cout);
      else if (arg == "VERTEXES")
        MaxVertexes(polygons, std::cout);
      else
        std::cout << "<INVALID COMMAND>\n";
    }
    else if (cmd == "MIN")
    {
      std::string arg;
      if (!(std::cin >> arg))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      if (arg == "AREA")
        MinArea(polygons, std::cout);
      else if (arg == "VERTEXES")
        MinVertexes(polygons, std::cout);
      else
        std::cout << "<INVALID COMMAND>\n";
    }
    else if (cmd == "MEAN")
    {
      std::string arg;
      if (!(std::cin >> arg) || arg != "AREA")
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }
      MeanArea(polygons, std::cout);
    }
    else if (cmd == "SAME")
    {
      std::string maybeNext;
      std::getline(std::cin, maybeNext);
      if (!maybeNext.empty() && maybeNext.find_first_not_of(" \t\n") != std::string::npos)
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      else
      {
        Same(polygons, std::cout);
      }
    }
    else if (cmd == "RIGHT")
    {
      Right(polygons, std::cout);
    }
    else if (cmd == "PERMS")
    {
      Perms(polygons, std::cout);
    }
    else if (cmd == "LESS")
    {
      Less(polygons, std::cout);
    }
    else if (cmd == "MORE")
    {
      More(polygons, std::cout);
    }
    else if (cmd == "EQUAL")
    {
      Equal(polygons, std::cout);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  return 0;
}
