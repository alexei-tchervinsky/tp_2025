#include "polygon.hpp"
#include <cmath>
#include <algorithm>
#include <tuple> // для std::tie

namespace prokopenko {

  bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
  }

  double Polygon::getArea() const {
    double area = 0.0;
    size_t n = points.size();
    if (n < 3) return 0.0;
    for (size_t i = 0; i < n; ++i) {
      const auto& a = points[i];
      const auto& b = points[(i + 1) % n];
      area += (a.x * b.y - b.x * a.y);
    }
    return std::abs(area) / 2.0;
  }

  bool Polygon::isRight() const {
    if (points.size() < 3) return false;
    size_t n = points.size();
    for (size_t i = 0; i < n; ++i) {
      const auto& a = points[i];
      const auto& b = points[(i + 1) % n];
      const auto& c = points[(i + 2) % n];
      int dx1 = b.x - a.x, dy1 = b.y - a.y;
      int dx2 = c.x - b.x, dy2 = c.y - b.y;
      if (dx1 * dx2 + dy1 * dy2 != 0) return false;
    }
    return true;
  }

  bool Polygon::isPermOf(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    std::vector<Point> a = points, b = other.points;
    auto cmp = [](const Point& p1, const Point& p2) {
      return std::tie(p1.x, p1.y) < std::tie(p2.x, p2.y);
      };
    std::sort(a.begin(), a.end(), cmp);
    std::sort(b.begin(), b.end(), cmp);
    return a == b;
  }

  std::istream& operator>>(std::istream& in, Polygon& poly) {
    poly.points.clear();
    size_t n;
    if (!(in >> n)) return in;
    if (n < 2) {
      in.setstate(std::ios::failbit);
      return in;
    }
    for (size_t i = 0; i < n; ++i) {
      char ch1, ch2, ch3;
      int x, y;
      if (!(in >> ch1 >> x >> ch2 >> y >> ch3)
        || ch1 != '(' || ch2 != ';' || ch3 != ')') {
        in.setstate(std::ios::failbit);
        return in;
      }
      poly.points.push_back({ x, y });
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Polygon& poly) {
    out << poly.points.size();
    for (const auto& pt : poly.points) {
      out << " (" << pt.x << ';' << pt.y << ')';
    }
    return out;
  }

} // namespace prokopenko
