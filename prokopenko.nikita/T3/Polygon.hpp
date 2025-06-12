#pragma once

#include <vector>
#include <ostream>
#include <string>

namespace prokopenko {

  struct Point {
    int x, y;
    bool operator==(const Point& other) const;
  };

  struct Polygon {
    std::vector<Point> points;
    bool operator==(const Polygon& other) const;
  };

  double computeArea(const Polygon& polygon);
  bool isRectangle(const Polygon& polygon);
  bool hasRightAngle(const Polygon& polygon);
  Polygon parsePolygon(const std::string& input);
  std::ostream& operator<<(std::ostream& os, const Polygon& poly);

} // namespace prokopenko
