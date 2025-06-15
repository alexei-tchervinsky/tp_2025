#include "polygon.hpp"
#include <cmath>
#include <algorithm>
#include <iterator>
#include <iomanip>

namespace prokopenko {

  static double crossProduct(const Point& a, const Point& b, const Point& c) {
    return static_cast<double>(b.x - a.x) * (c.y - a.y) -
      static_cast<double>(b.y - a.y) * (c.x - a.x);
  }

  // Используем crossProduct в "заглушке", чтобы избежать ошибки "unused-function"
  namespace {
    volatile double __unused_cross = crossProduct({ 0, 0 }, { 1, 0 }, { 0, 1 });
  }

  double Polygon::getArea() const {
    double area = 0.0;
    size_t n = points.size();
    for (size_t i = 0; i < n; ++i) {
      const Point& p1 = points[i];
      const Point& p2 = points[(i + 1) % n];
      area += static_cast<double>(p1.x) * p2.y - static_cast<double>(p2.x) * p1.y;
    }
    return std::abs(area) / 2.0;
  }

  bool Polygon::isRight() const {
    size_t n = points.size();
    if (n < 3) {
      return false;
    }

    for (size_t i = 0; i < n; ++i) {
      const Point& a = points[i];
      const Point& b = points[(i + 1) % n];
      const Point& c = points[(i + 2) % n];

      int dx1 = b.x - a.x;
      int dy1 = b.y - a.y;
      int dx2 = c.x - b.x;
      int dy2 = c.y - b.y;

      int dot = dx1 * dx2 + dy1 * dy2;
      if (dot == 0) {
        return true;
      }
    }
    return false;
  }

  bool Polygon::isPermOf(const Polygon& other) const {
    if (points.size() != other.points.size()) {
      return false;
    }

    std::vector<Point> rotated = other.points;
    for (size_t i = 0; i < rotated.size(); ++i) {
      std::rotate(rotated.begin(), rotated.begin() + 1, rotated.end());
      if (points == rotated) {
        return true;
      }
      std::reverse(rotated.begin(), rotated.end());
      if (points == rotated) {
        return true;
      }
      std::reverse(rotated.begin(), rotated.end()); // undo reverse
    }
    return false;
  }

  std::istream& operator>>(std::istream& in, Point& point) {
    char sep1 = 0, sep2 = 0, sep3 = 0;
    in >> sep1 >> point.x >> sep2 >> point.y >> sep3;
    if (sep1 != '(' || sep2 != ';' || sep3 != ')') {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << '(' << point.x << ';' << point.y << ')';
    return out;
  }

  std::istream& operator>>(std::istream& in, Polygon& polygon) {
    polygon.points.clear();
    size_t n = 0;
    if (!(in >> n)) {
      in.setstate(std::ios::failbit);
      return in;
    }

    polygon.points.reserve(n);
    for (size_t i = 0; i < n; ++i) {
      Point p;
      if (!(in >> p)) {
        in.setstate(std::ios::failbit);
        return in;
      }
      polygon.points.push_back(p);
    }

    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Polygon& polygon) {
    out << polygon.points.size();
    for (const Point& p : polygon.points) {
      out << ' ' << p;
    }
    return out;
  }

  bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

} // namespace prokopenko
