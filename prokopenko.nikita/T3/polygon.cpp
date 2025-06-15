#include "polygon.hpp"
#include <cmath>
#include <limits>
#include <algorithm>

namespace prokopenko {

  double Polygon::getArea() const {
    double area = 0.0;
    size_t n = points.size();
    for (size_t i = 0; i < n; ++i) {
      const Point& a = points[i];
      const Point& b = points[(i + 1) % n];
      area += static_cast<double>(a.x) * b.y
        - static_cast<double>(b.x) * a.y;
    }
    return std::fabs(area) / 2.0;
  }

  bool Polygon::isPermOf(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    size_t n = points.size();
    for (size_t shift = 0; shift < n; ++shift) {
      bool ok = true;
      for (size_t i = 0; i < n; ++i) {
        if (points[i] != other.points[(i + shift) % n]) {
          ok = false;
          break;
        }
      }
      if (ok) return true;
      ok = true;
      for (size_t i = 0; i < n; ++i) {
        if (points[i] != other.points[(n + shift - i) % n]) {
          ok = false;
          break;
        }
      }
      if (ok) return true;
    }
    return false;
  }

  bool Polygon::sameByTranslation(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    size_t n = points.size();
    // Try aligning points[0] to each other.points[j]
    for (size_t j = 0; j < n; ++j) {
      int dx = other.points[j].x - points[0].x;
      int dy = other.points[j].y - points[0].y;
      bool ok = true;
      for (size_t i = 0; i < n; ++i) {
        Point shifted{ points[i].x + dx, points[i].y + dy };
        if (shifted != other.points[(j + i) % n]) {
          ok = false;
          break;
        }
      }
      if (ok) return true;
    }
    return false;
  }

  bool Polygon::isRightRect() const {
    // Check if 4 vertices and consecutive right angles (convex)
    if (points.size() != 4) return false;
    // Compute cross products for each consecutive triple
    for (size_t i = 0; i < 4; ++i) {
      const Point& a = points[i];
      const Point& b = points[(i + 1) % 4];
      const Point& c = points[(i + 2) % 4];
      int dx1 = b.x - a.x;
      int dy1 = b.y - a.y;
      int dx2 = c.x - b.x;
      int dy2 = c.y - b.y;
      if (dx1 * dx2 + dy1 * dy2 != 0) {
        return false;
      }
    }
    return true;
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

  std::ostream& operator<<(std::ostream& out,
    const Polygon& polygon) {
    out << polygon.points.size();
    for (auto& pt : polygon.points) {
      out << " (" << pt.x << ";" << pt.y << ")";
    }
    return out;
  }

} // namespace prokopenko
