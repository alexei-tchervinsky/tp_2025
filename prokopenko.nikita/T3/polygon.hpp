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
    bool intersects(const Polygon&) const; // 🔧 Добавлено
  };

  std::istream& operator>>(std::istream& in, Point& p);
  std::istream& operator>>(std::istream& in, Polygon& poly);
  std::ostream& operator<<(std::ostream& out, const Point& p);

} // namespace prokopenko

#endif // POLYGON_HPP
