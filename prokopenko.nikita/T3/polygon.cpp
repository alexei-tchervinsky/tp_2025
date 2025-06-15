#include "polygon.hpp"
#include <cmath>
#include <algorithm>
#include <tuple>

namespace prokopenko {

  std::istream& operator>>(std::istream& in, Point& p) {
    char ch;
    return (in >> ch >> p.x >> ch >> p.y >> ch);
  }

  std::istream& operator>>(std::istream& in, Polygon& poly) {
    size_t n;
    in >> n;
    poly.points.clear();
    for (size_t i = 0; i < n; ++i) {
      Point pt;
      if (!(in >> pt)) {
        in.setstate(std::ios::failbit);
        return in;
      }
      poly.points.push_back(pt);
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << '(' << p.x << ';' << p.y << ')';
    return out;
  }

  double Polygon::getArea() const {
    if (points.size() < 3) return 0.0;
    long long area = 0;
    for (size_t i = 0; i < points.size(); ++i) {
      const Point& p1 = points[i];
      const Point& p2 = points[(i + 1) % points.size()];
      area += static_cast<long long>(p1.x) * p2.y -
        static_cast<long long>(p2.x) * p1.y;
    }
    return std::abs(area) / 2.0;
  }

  bool Polygon::isRight() const {
    if (points.size() < 3) return false;
    for (size_t i = 0; i < points.size(); ++i) {
      const Point& a = points[i];
      const Point& b = points[(i + 1) % points.size()];
      const Point& c = points[(i + 2) % points.size()];
      int dx1 = b.x - a.x;
      int dy1 = b.y - a.y;
      int dx2 = c.x - b.x;
      int dy2 = c.y - b.y;
      if (dx1 * dx2 + dy1 * dy2 != 0) return false;
    }
    return true;
  }

  bool Polygon::isPermOf(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    if (points.empty()) return true;

    std::vector<Point> a = points;
    std::vector<Point> b = other.points;

    auto cmp = [](const Point& p1, const Point& p2) {
      return std::tie(p1.x, p1.y) < std::tie(p2.x, p2.y);
      };

    for (size_t shift = 0; shift < b.size(); ++shift) {
      std::rotate(b.begin(), b.begin() + 1, b.end());
      if (a == b) return true;
      std::reverse(b.begin() + 1, b.end());
      if (a == b) return true;
      std::reverse(b.begin() + 1, b.end());
    }

    std::sort(a.begin(), a.end(), cmp);
    std::sort(b.begin(), b.end(), cmp);
    return a == b;
  }

  bool Polygon::intersects(const Polygon& other) const {
    for (const auto& p1 : points) {
      for (const auto& p2 : other.points) {
        if (p1.x == p2.x && p1.y == p2.y) return true;
      }
    }
    return false;
  }

} // namespace prokopenko
