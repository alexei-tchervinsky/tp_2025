#include "polygon.hpp"
#include <cmath>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <numeric>

namespace prokopenko {

  bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }

  bool Polygon::operator==(const Polygon& other) const {
    return points == other.points;
  }

  double computeArea(const Polygon& poly) {
    const std::vector<Point>& pts = poly.points;
    if (pts.size() < 3) return 0.0;
    int sum = 0;
    for (size_t i = 0; i < pts.size(); ++i) {
      const Point& p1 = pts[i];
      const Point& p2 = pts[(i + 1) % pts.size()];
      sum += (p1.x * p2.y - p2.x * p1.y);
    }
    return std::abs(sum) / 2.0;
  }

  static int dotProduct(const Point& a, const Point& b, const Point& c) {
    int dx1 = b.x - a.x, dy1 = b.y - a.y;
    int dx2 = c.x - b.x, dy2 = c.y - b.y;
    return dx1 * dx2 + dy1 * dy2;
  }

  bool hasRightAngle(const Polygon& poly) {
    size_t n = poly.points.size();
    if (n < 3) return false;
    for (size_t i = 0; i < n; ++i) {
      const Point& a = poly.points[i];
      const Point& b = poly.points[(i + 1) % n];
      const Point& c = poly.points[(i + 2) % n];
      if (dotProduct(a, b, c) == 0) return true;
    }
    return false;
  }

  Polygon parsePolygon(const std::string& input) {
    Polygon poly;
    std::istringstream iss(input);
    int count;
    if (!(iss >> count)) return poly;
    poly.points.reserve(count);
    for (int i = 0; i < count; ++i) {
      char ch;
      int x, y;
      if (!(iss >> ch) || ch != '(') break;
      if (!(iss >> x)) break;
      if (!(iss >> ch) || ch != ';') break;
      if (!(iss >> y)) break;
      if (!(iss >> ch) || ch != ')') break;
      poly.points.push_back({ x, y });
    }
    if (poly.points.size() != static_cast<size_t>(count)) {
      poly.points.clear();
    }
    return poly;
  }

  std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
    os << poly.points.size();
    for (const auto& pt : poly.points) {
      os << " (" << pt.x << ";" << pt.y << ")";
    }
    return os;
  }

} // namespace prokopenko
