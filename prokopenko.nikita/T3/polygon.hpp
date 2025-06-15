#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iosfwd>

namespace prokopenko {

  struct Point {
    int x;
    int y;
  };

  class Polygon {
  public:
    std::vector<Point> points;

    double getArea() const;
    bool isRight() const;
    bool isPermOf(const Polygon& other) const;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& out, const Point& point);

  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);

  bool operator==(const Point& lhs, const Point& rhs);

} // namespace prokopenko

#endif // POLYGON_HPP
