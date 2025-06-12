#include "Polygon.hpp"
#include <cmath>
#include <numeric>

namespace prokopenko {

  bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }

  bool Polygon::operator==(const Polygon& other) const {
    return points == other.points;
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
    size_t n = 0;
    in >> n;
    if (!in || n < 3) {
      in.setstate(std::ios::failbit);
      return in;
    }
    std::vector<Point> tmp;
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
    double sum = std::abs(std::accumulate(
      v.begin(), v.end(), 0.0,
      [&v](double acc, const Point& p) {
        size_t i = (&p - &v[0]);
        const Point& q = v[(i + 1) % v.size()];
        return acc + p.x * q.y - q.x * p.y;
      }
    )) / 2.0;
    return sum;
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
