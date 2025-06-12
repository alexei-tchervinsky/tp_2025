#include "Polygon.hpp"
#include <cmath>
#include <numeric>

namespace prokopenko {

  bool Point::operator==(const Point& o) const {
    return x == o.x && y == o.y;
  }

  bool Polygon::operator==(const Polygon& o) const {
    return points == o.points;
  }

  std::istream& operator>>(std::istream& in, Point& pt) {
    std::istream::sentry s(in);
    if (!s) return in;
    char o, sep, c;
    int x, y;
    in >> o >> x >> sep >> y >> c;
    if (!in || o != '(' || sep != ';' || c != ')') {
      in.setstate(std::ios::failbit);
      return in;
    }
    pt = { x, y };
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& pg) {
    std::istream::sentry s(in);
    if (!s) return in;
    size_t n;
    in >> n;
    if (!in || n < 3) {
      in.setstate(std::ios::failbit);
      return in;
    }
    std::vector<Point> tmp;
    tmp.reserve(n);
    for (size_t i = 0; i < n; ++i) {
      Point p;
      if (!(in >> p)) {
        in.setstate(std::ios::failbit);
        return in;
      }
      tmp.push_back(p);
    }
    pg.points = std::move(tmp);
    return in;
  }

  double getArea(const Polygon& pg) {
    const auto& v = pg.points;
    size_t n = v.size();
    double sum = 0;
    for (size_t i = 0; i < n; ++i) {
      const auto& a = v[i];
      const auto& b = v[(i + 1) % n];
      sum += a.x * b.y - b.x * a.y;
    }
    return fabs(sum) / 2.0;
  }

  bool hasRightAngle(const Polygon& pg) {
    const auto& v = pg.points;
    size_t n = v.size();
    for (size_t i = 0; i < n; ++i) {
      const auto& A = v[(i + n - 1) % n];
      const auto& B = v[i];
      const auto& C = v[(i + 1) % n];
      int abx = B.x - A.x, aby = B.y - A.y;
      int cbx = B.x - C.x, cby = B.y - C.y;
      if (abx * cbx + aby * cby == 0) return true;
    }
    return false;
  }

}
