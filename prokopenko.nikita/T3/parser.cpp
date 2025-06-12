#include "parser.hpp"
#include <sstream>
#include <cctype>
#include <stdexcept>

Polygon parsePolygon(const std::string& input) {
  std::vector<Point> points;
  std::istringstream iss(input);
  char ch;
  double x, y;

  while (iss >> ch) {
    if (ch != '(') continue;
    if (!(iss >> x >> ch) || ch != ',') throw std::runtime_error("Invalid point format");
    if (!(iss >> y >> ch) || ch != ')') throw std::runtime_error("Invalid point format");
    points.push_back({ x, y });
  }

  return Polygon(points);
}
