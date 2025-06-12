#pragma once
#include "Polygon.hpp"
#include <string>
#include <vector>
#include <iostream>

namespace prokopenko {
  bool doCommand(const std::string& command, std::vector<Polygon>& data, std::istream& in);
}
