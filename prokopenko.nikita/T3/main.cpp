#include <iostream>
#include <map>
#include <functional>
#include "polygon.hpp"

namespace prokopenko
{
  double area_param(const std::vector<Polygon>, std::istream&, std::ostream&);
  double max_param(const std::vector<Polygon>, std::istream&, std::ostream&);
  double min_param(const std::vector<Polygon>, std::istream&, std::ostream&);
  size_t count_param(const std::vector<Polygon>, std::istream&, std::ostream&);
  std::vector<Polygon> rects_param(const std::vector<Polygon>, std::istream&, std::ostream&);
  size_t maxseq_param(const std::vector<Polygon>, std::istream&, std::ostream&);
}

int main()
{
  using namespace prokopenko;

  std::vector<Polygon> data;
  Polygon polygon;

  while (std::cin >> polygon)
  {
    data.push_back(polygon);
  }

  if (!std::cin.eof())
  {
    std::cerr << "Error while reading input\n";
    return 1;
  }

  std::map<std::string, std::function<void(const std::vector<Polygon>, std::istream&, std::ostream&)>> commands{
    {"AREA", prokopenko::area_param},
    {"MAX", prokopenko::max_param},
    {"MIN", prokopenko::min_param},
    {"COUNT", prokopenko::count_param},
    {"RECTS", prokopenko::rects_param},
    {"MAXSEQ", prokopenko::maxseq_param}
  };

  std::string command;
  while (std::cin >> command)
  {
    auto it = commands.find(command);
    if (it != commands.end())
    {
      it->second(data, std::cin, std::cout);
    }
    else
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}
