#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace prokopenko {

  struct Point {
    int x, y;
  };

  struct Polygon {
    std::vector<Point> points;

    double getArea() const;
    bool isRight() const;
    bool isPermOf(const Polygon&) const;
  };

  std::istream& operator>>(std::istream&, Polygon&);
  std::ostream& operator<<(std::ostream&, const Polygon&);

} // namespace prokopenko

#endif
