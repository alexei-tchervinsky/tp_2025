#pragma once
#include "polygon.hpp"
#include <vector>
#include <istream>

namespace prokopenko {

  std::vector<Polygon> parseFile(std::istream& input);

} // namespace prokopenko
