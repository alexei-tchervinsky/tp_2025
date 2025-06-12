#include "Polygon.hpp"
#include <cmath>
#include <sstream>
#include <iomanip>

Polygon::Polygon(const std::vector<Point>& points) : points(points) {}

double Polygon::perimeter() const {
  double sum = 0.0;
  for (size_t i = 0; i < points.size(); ++i) {
    const Point& p1 = points[i];
    const Point& p2 = points[(i + 1) % points.size()];
    sum += std::hypot(p2.x - p1.x, p2.y - p1.y);
  }
  return sum;
}

size_t Polygon::vertexCount() const {
  return points.size();
}

bool Polygon::operator==(const Polygon& other) const {
  return points == other.points;
}

std::string Polygon::toString() const {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2);
  for (const auto& p : points) {
    oss << "(" << p.x << "," << p.y << ") ";
  }
  return oss.str();
}

void Polygon::print() const {
  std::cout << toString() << std::endl;
}
