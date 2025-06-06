#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <iostream>
#include <vector>
#include <functional>
namespace popov
{
  struct Polygon;
  struct DelimiterChar
  {
    char expected;
  };
  using CommandFunction = std::function<void(std::istream&, std::ostream&)>;
  using CommandMap = std::map<std::string, CommandFunction>;
  CommandMap createCommandMap(std::vector<Polygon>& polygons);
}
#endif
