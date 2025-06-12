#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace prokopenko {

  struct Point {
    int x, y;
    bool operator==(const Point& other) const;
  };

  struct Polygon {
    std::vector<Point> points;
    bool operator==(const Polygon& other) const;
  };

  std::istream& operator>>(std::istream& in, Point& pt);
  std::istream& operator>>(std::istream& in, Polygon& pg);
  double getArea(const Polygon& pg);
  bool hasRightAngle(const Polygon& pg);

}

#endif
