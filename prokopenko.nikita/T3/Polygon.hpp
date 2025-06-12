#ifndef PROKOPENKO_POLYGON_HPP
#define PROKOPENKO_POLYGON_HPP

#include <iostream>
#include <vector>

namespace prokopenko {

  struct Point {
    int x = 0, y = 0;
  };

  struct Polygon {
    std::vector<Point> points;
  };

  double getArea(const Polygon& p);
  std::istream& operator>>(std::istream& in, Point& p);
  std::istream& operator>>(std::istream& in, Polygon& p);

}

#endif
