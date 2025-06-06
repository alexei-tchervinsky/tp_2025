#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>
#include <limits>
#include "geometry.hpp"
#include "iofmtguard.hpp"
#include "commands.hpp"
#include <vector>
#include "file_io.hpp"
int main(int argc, char* argv[])
{
  using namespace popov;
  if (argc != 2)
  {
    std::cerr << "Wrong arguments\n";
    return 1;
  }
  try {
    std::vector<Polygon> polygons = readPolygonsFromFile(argv[1]);
    CommandMap commands = createCommandMap(polygons);
    std::string cmd = "";
    while (std::cin >> cmd)
    {
      try
      {
        commands.at(cmd)(std::cin, std::cout);
        std::cout << "\n";
      }
      catch (...)
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
