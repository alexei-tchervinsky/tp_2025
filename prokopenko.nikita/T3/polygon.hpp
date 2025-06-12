#pragma once

#include <vector>
#include <string>
#include <utility>

namespace prokopenko {

  struct Point {
    double x;
    double y;
  };

  class Polygon {
  public:
    Polygon() = default;
    explicit Polygon(const std::vector<Point>& vertices);

    void addPoint(const Point& point);
    double area() const;
    double perimeter() const;
    std::string toString() const;

  private:
    std::vector<Point> points;
    double distance(const Point& a, const Point& b) const;
  };

} // namespace prokopenko
