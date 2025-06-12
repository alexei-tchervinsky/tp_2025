#include "parser.hpp"
#include <string>
#include <sstream>

namespace prokopenko {

  std::vector<Polygon> parseFile(std::istream& input) {
    std::vector<Polygon> polygons;
    std::string line;
    while (std::getline(input, line)) {
      Polygon p = parsePolygon(line);
      if (!p.points.empty()) {
        polygons.push_back(p);
      }
    }
    return polygons;
  }

} // namespace prokopenko
