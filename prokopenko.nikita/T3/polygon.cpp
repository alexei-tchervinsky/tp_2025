#include "polygon.hpp"
#include <cmath>
#include <algorithm>

namespace prokopenko {

  bool Point::operator==(const Point& other) const {
    return std::abs(x - other.x) < 1e-6 && std::abs(y - other.y) < 1e-6;
  }
  bool Point::operator!=(const Point& other) const {
    return !(*this == other);
  }

  bool Polygon::isRight() const {
    const size_t n = points.size();
    for (size_t i = 0; i < n; ++i) {
      const Point& a = points[i];
      const Point& b = points[(i + 1) % n];
      const Point& c = points[(i + 2) % n];
      int dx1 = b.x - a.x;
      int dy1 = b.y - a.y;
      int dx2 = c.x - b.x;
      int dy2 = c.y - b.y;
      int dot = dx1 * dx2 + dy1 * dy2;
      if (dot == 0)
        return true;
    }
    return false;
  }

  bool Polygon::isPermOf(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    size_t n = points.size();
    for (size_t offset = 0; offset < n; ++offset) {
      bool matchCW = true;
      for (size_t i = 0; i < n; ++i) {
        if (points[i] != other.points[(i + offset) % n]) {
          matchCW = false;
          break;
        }
      }
      if (matchCW) return true;

      bool matchCCW = true;
      for (size_t i = 0; i < n; ++i) {
        if (points[i] != other.points[(n + offset - i) % n]) {
          matchCCW = false;
          break;
        }
      }
      if (matchCCW) return true;
    }
    return false;
  }

  double Polygon::getArea() const {
    double area = 0.0;
    size_t n = points.size();
    for (size_t i = 0; i < n; ++i) {
      const Point& a = points[i];
      const Point& b = points[(i + 1) % n];
      area += (a.x * b.y - b.x * a.y);
    }
    return std::abs(area) / 2.0;
  }

} // namespace prokopenko
