#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <map>
#include <functional>
#include <istream>
#include <string>
#include <vector>
#include "geometry.hpp"
namespace popov
{
  using CommandFunction = std::function<void(std::istream&, std::ostream&)>;
  using CommandMap = std::map<std::string, CommandFunction>;
  
  CommandMap createCommandMap(std::vector<Polygon>& polygons);
}
#endif
