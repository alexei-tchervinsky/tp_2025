#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

struct Point {
  int x, y;
};
// Сравнение и равенство точек для удобства
inline bool operator<(const Point& a, const Point& b) {
  if (a.x != b.x) return a.x < b.x;
  return a.y < b.y;
}
inline bool operator==(const Point& a, const Point& b) {
  return a.x == b.x && a.y == b.y;
}

struct Polygon {
  std::vector<Point> points;
  double getArea() const;
};

bool operator==(const Polygon& a, const Polygon& b);
bool operator<(const Polygon& a, const Polygon& b);
std::istream& operator>>(std::istream& is, Polygon& poly);
std::ostream& operator<<(std::ostream& os, const Polygon& poly);

#endif // POLYGON_HPP
