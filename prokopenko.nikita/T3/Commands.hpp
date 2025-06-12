#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "polygon.hpp"
#include <vector>
#include <iostream>

namespace prokopenko
{
  double area_param(const std::vector<Polygon>& data, std::istream& in, std::ostream& out);
  double max_param(const std::vector<Polygon>& data, std::istream& in, std::ostream& out);
  double min_param(const std::vector<Polygon>& data, std::istream& in, std::ostream& out);
  size_t count_param(const std::vector<Polygon>& data, std::istream& in, std::ostream& out);
  std::vector<Polygon> rects_param(const std::vector<Polygon>& data, std::istream& in, std::ostream& out);
  size_t maxseq_param(const std::vector<Polygon>& data, std::istream& in, std::ostream& out);
}

#endif
