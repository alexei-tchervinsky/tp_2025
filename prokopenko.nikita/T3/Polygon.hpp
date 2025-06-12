#pragma once
#include <vector>
#include <iostream>

namespace prokopenko {

  struct Point {
    int x, y;
  };

  struct Polygon {
    std::vector<Point> points;
  };

  std::istream& operator>>(std::istream& in, Point& p);
  std::ostream& operator<<(std::ostream& out, const Point& p);
  std::istream& operator>>(std::istream& in, Polygon& poly);
  std::ostream& operator<<(std::ostream& out, const Polygon& poly);
  double getArea(const Polygon& poly);

}
