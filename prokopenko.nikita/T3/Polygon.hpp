#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <string>
#include <iostream>

struct Point {
  double x;
  double y;

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
};

class Polygon {
public:
  Polygon() = default;
  Polygon(const std::vector<Point>& points);

  double perimeter() const;
  size_t vertexCount() const;
  bool operator==(const Polygon& other) const;

  std::string toString() const;
  void print() const;

private:
  std::vector<Point> points;
};

#endif // POLYGON_HPP
