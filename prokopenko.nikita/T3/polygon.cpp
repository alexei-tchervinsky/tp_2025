#include "polygon.hpp"
#include <cmath>
#include <sstream>

namespace prokopenko {

  Polygon::Polygon(const std::vector<Point>& vertices) : points(vertices) {}

  void Polygon::addPoint(const Point& point) {
    points.push_back(point);
  }

  double Polygon::distance(const Point& a, const Point& b) const {
    return std::hypot(b.x - a.x, b.y - a.y);
  }

  double Polygon::perimeter() const {
    if (points.size() < 2) return 0.0;
    double result = 0.0;
    for (size_t i = 0; i < points.size(); ++i) {
      const Point& current = points[i];
      const Point& next = points[(i + 1) % points.size()];
      result += distance(current, next);
    }
    return result;
  }

  double Polygon::area() const {
    if (points.size() < 3) return 0.0;
    double sum = 0.0;
    for (size_t i = 0; i < points.size(); ++i) {
      const Point& p1 = points[i];
      const Point& p2 = points[(i + 1) % points.size()];
      sum += (p1.x * p2.y - p2.x * p1.y);
    }
    return std::abs(sum) / 2.0;
  }

  std::string Polygon::toString() const {
    std::ostringstream oss;
    oss << "Polygon with " << points.size() << " points: ";
    for (const auto& p : points) {
      oss << "(" << p.x << ", " << p.y << ") ";
    }
    return oss.str();
  }

} // namespace prokopenko
