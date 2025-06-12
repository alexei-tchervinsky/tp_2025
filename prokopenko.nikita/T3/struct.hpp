#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>
#include <cstddef>

namespace prokopenko
{
  struct Point
  {
    int x;
    int y;
  };

  using Polygon = std::vector<Point>;

  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Point& point);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);
}

#endif
