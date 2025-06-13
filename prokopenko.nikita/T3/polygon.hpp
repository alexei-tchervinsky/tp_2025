#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <cstddef>
#include <tuple>
#include <iostream>

namespace prokopenko {

  struct Point {
    int x;
    int y;

    bool operator<(const Point& other) const {
      return std::tie(x, y) < std::tie(other.x, other.y);
    }

    bool operator==(const Point& other) const {
      return x == other.x && y == other.y;
    }
  };

  using Polygon = std::vector<Point>;

  double getArea(const Polygon& polygon);

  struct DelimiterIO {
    char del;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream& in, Polygon& polygon);

} // namespace prokopenko

#endif // POLYGON_HPP
