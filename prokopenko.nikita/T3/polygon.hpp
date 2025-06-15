#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace prokopenko {

  struct Point {
    int x;
    int y;
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
  };

  struct Polygon {
    std::vector<Point> points;
    double getArea() const;
    bool isRight() const;
    bool isPermOf(const Polygon& other) const;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream& in, Polygon& polygon);

} // namespace prokopenko

#endif // POLYGON_HPP
