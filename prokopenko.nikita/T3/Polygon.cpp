#include "Polygon.hpp"
#include <cmath>
#include <limits>

namespace prokopenko {

  std::istream& operator>>(std::istream& in, Point& p) {
    char ch;
    in >> ch;
    if (ch != '(') {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> p.x >> ch;
    if (ch != ';') {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> p.y >> ch;
    if (ch != ')') {
      in.setstate(std::ios::failbit);
      return in;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Point& p) {
    return out << '(' << p.x << ';' << p.y << ')';
  }

  std::istream& operator>>(std::istream& in, Polygon& poly) {
    size_t count;
    if (!(in >> count)) {
      in.setstate(std::ios::failbit);
      return in;
    }

    poly.points.clear();
    for (size_t i = 0; i < count; ++i) {
      Point p;
      if (!(in >> p)) {
        in.setstate(std::ios::failbit);
        return in;
      }
      poly.points.push_back(p);
    }

    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Polygon& poly) {
    out << poly.points.size();
    for (const auto& p : poly.points) {
      out << ' ' << p;
    }
    return out;
  }

  double getArea(const Polygon& poly) {
    double area = 0.0;
    const auto& pts = poly.points;
    size_t n = pts.size();

    for (size_t i = 0; i < n; ++i) {
      const Point& p1 = pts[i];
      const Point& p2 = pts[(i + 1) % n];
      area += (p1.x * p2.y) - (p2.x * p1.y);
    }

    return std::abs(area) / 2.0;
  }

}
