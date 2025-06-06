#include "commands.hpp"
#include "polygon_operations.hpp"
#include <functional>
#include <map>
popov::CommandMap popov::createCommandMap(std::vector<Polygon>& polygons)
{
  CommandMap commands;
  using namespace std::placeholders;
  commands["AREA"] = std::bind(area, std::cref(polygons), _1, _2);
  commands["COUNT"] = std::bind(count, std::cref(polygons), _1, _2);
  commands["MAX"] = std::bind(max, std::cref(polygons), _1, _2);
  commands["MIN"] = std::bind(min, std::cref(polygons), _1, _2);
  commands["INFRAME"] = std::bind(inframe, std::cref(polygons), _1, _2);
  commands["ECHO"] = std::bind(echo, std::ref(polygons), _1, _2);
  commands["RIGHTSHAPES"] = std::bind(rightshapes, std::cref(polygons), _2);
  return commands;
}
