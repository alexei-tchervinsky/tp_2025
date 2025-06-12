#include "Polygon.hpp"
#include <cmath>

namespace prokopenko {

  double getArea(const Polygon& p) {
    double area = 0.0;
    int n = static_cast<int>(p.points.size());
    for (int i = 0; i < n; ++i) {
      const Point& a = p.points[i];
      const Point& b = p.points[(i + 1) % n];
      area += (a.x * b.y - b.x * a.y);
    }
    return std::abs(area) / 2.0;
  }

  std::istream& operator>>(std::istream& in, Point& p) {
    char c1, c2, c3;
    in >> c1 >> p.x >> c2 >> p.y >> c3;
    if (c1 != '(' || c2 != ';' || c3 != ')') {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& p) {
    int n;
    if (!(in >> n) || n < 3) {
      in.setstate(std::ios::failbit);
      return in;
    }

    p.points.clear();
    for (int i = 0; i < n; ++i) {
      Point pt;
      if (!(in >> pt)) {
        in.setstate(std::ios::failbit);
        return in;
      }
      p.points.push_back(pt);
    }

    return in;
  }

}
