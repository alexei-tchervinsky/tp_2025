#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <istream>
#include "Polygon.hpp"

namespace prokopenko {

  void areaCommand(const std::vector<Polygon>&, std::istream&);
  void countCommand(const std::vector<Polygon>&, std::istream&);
  void maxCommand(const std::vector<Polygon>&, std::istream&);
  void minCommand(const std::vector<Polygon>&, std::istream&);
  void echoCommand(std::vector<Polygon>&, std::istream&);
  void rightShapesCommand(const std::vector<Polygon>&, std::istream&);
  void doCommand(const std::string&, std::vector<Polygon>&, std::istream&);

}

#endif
