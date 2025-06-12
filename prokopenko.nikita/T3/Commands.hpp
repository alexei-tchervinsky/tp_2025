#ifndef PROKOPENKO_COMMANDS_HPP
#define PROKOPENKO_COMMANDS_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Polygon.hpp"

namespace prokopenko {
  void doCommand(const std::string& command, std::vector<Polygon>& data, std::istream& in);
}

#endif
