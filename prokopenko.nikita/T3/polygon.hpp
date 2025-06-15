#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace prokopenko {

  struct Point {
    int x;
    int y;
    bool operator==(const Point& other) const {
      return x == other.x && y == other.y;
    }
    bool operator!=(const Point& other) const {
      return !(*this == other);
    }
  };
  struct Polygon {
    std::vector<Point> points;
    double getArea() const;
    bool isRightRect() const;
    bool isPermOf(const Polygon& other) const;
    bool sameByTranslation(const Polygon& other) const;
  };
  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);

} // namespace prokopenko

#endif // POLYGON_HPP
