#include "polygon.hpp"
#include <cmath>
#include <algorithm>
#include <ios>

namespace prokopenko {

  bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
  bool Point::operator!=(const Point& other) const {
    return !(*this == other);
  }

  double Polygon::getArea() const {
    double area = 0.0;
    size_t n = points.size();
    for (size_t i = 0; i < n; ++i) {
      const Point& a = points[i];
      const Point& b = points[(i + 1) % n];
      area += static_cast<double>(a.x) * b.y - static_cast<double>(b.x) * a.y;
    }
    return std::fabs(area) / 2.0;
  }

  bool Polygon::isRight() const {
    size_t n = points.size();
    if (n < 3) return false;
    for (size_t i = 0; i < n; ++i) {
      const Point& a = points[i];
      const Point& b = points[(i + 1) % n];
      const Point& c = points[(i + 2) % n];
      int dx1 = b.x - a.x;
      int dy1 = b.y - a.y;
      int dx2 = c.x - b.x;
      int dy2 = c.y - b.y;
      if (dx1 * dx2 + dy1 * dy2 == 0) {
        return true;
      }
    }
    return false;
  }

  bool Polygon::isPermOf(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    size_t n = points.size();
    for (size_t shift = 0; shift < n; ++shift) {
      bool ok = true;
      for (size_t i = 0; i < n; ++i) {
        if (!(points[i] == other.points[(i + shift) % n])) {
          ok = false;
          break;
        }
      }
      if (ok) return true;
      ok = true;
      for (size_t i = 0; i < n; ++i) {
        if (!(points[i] == other.points[(n + shift - i) % n])) {
          ok = false;
          break;
        }
      }
      if (ok) return true;
    }
    return false;
  }

  std::istream& operator>>(std::istream& in, Point& point) {
    char ch;
    in >> std::ws >> ch;
    if (!in || ch != '(') {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> point.x;
    if (!in) { in.setstate(std::ios::failbit); return in; }
    in >> ch;
    if (!in || ch != ';') {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> point.y;
    if (!in) { in.setstate(std::ios::failbit); return in; }
    in >> ch;
    if (!in || ch != ')') {
      in.setstate(std::ios::failbit);
      return in;
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& polygon) {
    size_t sz;
    in >> sz;
    if (!in) return in;
    std::vector<Point> pts;
    Point pt;
    for (size_t i = 0; i < sz; ++i) {
      if (!(in >> pt)) {
        in.setstate(std::ios::failbit);
        return in;
      }
      pts.push_back(pt);
    }
    polygon.points = std::move(pts);
    return in;
  }

} // namespace prokopenko
