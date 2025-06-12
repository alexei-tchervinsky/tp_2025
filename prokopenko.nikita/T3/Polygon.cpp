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

}
