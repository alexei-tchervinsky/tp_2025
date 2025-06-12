#include "Polygon.hpp"
#include <cmath>

namespace prokopenko {

  double getArea(const Polygon& p) {
    double area = 0.0;
    int n = p.points.size();
    for (int i = 0; i < n; ++i) {
      const Point& a = p.points[i];
      const Point& b = p.points[(i + 1) % n];
      area += (a.x * b.y - b.x * a.y);
    }
    return std::abs(area) / 2.0;
  }

  std::istream& operator>>(std::istream& in, Point& p) {
    char c;
    in >> c >> p.x >> c >> p.y >> c;
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& p) {
    int n;
    in >> n;
    p.points.clear();
    p.points.reserve(n);
    for (int i = 0; i < n; ++i) {
      Point pt;
      in >> pt;
      p.points.push_back(pt);
    }
    return in;
  }

}
