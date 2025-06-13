#include "polygon.hpp"
#include <cmath>
#include <algorithm>
#include <numeric>

namespace prokopenko
{
  bool Point::operator==(const Point& other) const
  {
    return x == other.x && y == other.y;
  }

  std::istream& operator>>(std::istream& in, Point& point)
  {
    in >> point.x >> point.y;
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& polygon)
  {
    size_t n;
    in >> n;
    polygon.points.resize(n);
    for (size_t i = 0; i < n; ++i)
    {
      in >> polygon.points[i];
    }
    return in;
  }

  double Polygon::getArea() const
  {
    if (points.size() < 3) return 0.0;

    double area = 0.0;
    for (size_t i = 0; i < points.size(); ++i)
    {
      size_t j = (i + 1) % points.size();
      area += static_cast<double>(points[i].x) * points[j].y;
      area -= static_cast<double>(points[j].x) * points[i].y;
    }
    return std::abs(area) / 2.0;
  }

  bool Polygon::isRight() const
  {
    for (size_t i = 0; i < points.size(); ++i)
    {
      const Point& a = points[i];
      const Point& b = points[(i + 1) % points.size()];
      const Point& c = points[(i + 2) % points.size()];

      int dx1 = b.x - a.x;
      int dy1 = b.y - a.y;
      int dx2 = c.x - b.x;
      int dy2 = c.y - b.y;

      int dot = dx1 * dx2 + dy1 * dy2;
      if (dot == 0) return true; // угол 90°
    }
    return false;
  }

  bool Polygon::operator==(const Polygon& other) const
  {
    return points == other.points;
  }

  bool Polygon::isPermOf(const Polygon& other) const
  {
    if (points.size() != other.points.size()) return false;

    for (size_t offset = 0; offset < points.size(); ++offset)
    {
      bool match = true;
      for (size_t i = 0; i < points.size(); ++i)
      {
        if (points[i] != other.points[(i + offset) % points.size()])
        {
          match = false;
          break;
        }
      }
      if (match) return true;

      // проверить в обратном порядке
      match = true;
      for (size_t i = 0; i < points.size(); ++i)
      {
        if (points[i] != other.points[(points.size() + offset - i) % points.size()])
        {
          match = false;
          break;
        }
      }
      if (match) return true;
    }

    return false;
  }
}
