#include "polygon.hpp"
#include <cmath>
#include <algorithm>

namespace prokopenko
{
  bool Polygon::isRight() const
  {
    const size_t n = points_.size();
    for (size_t i = 0; i < n; ++i)
    {
      const Point& a = points_[i];
      const Point& b = points_[(i + 1) % n];
      const Point& c = points_[(i + 2) % n];

      int abx = b.x - a.x;
      int aby = b.y - a.y;
      int bcx = c.x - b.x;
      int bcy = c.y - b.y;

      int dot = abx * bcx + aby * bcy;
      if (dot == 0)
        return true;
    }
    return false;
  }

  bool Polygon::isPermOf(const Polygon& other) const
  {
    if (points_.size() != other.points_.size())
      return false;

    std::vector<Point> a = points_;
    std::vector<Point> b = other.points_;

    for (size_t shift = 0; shift < b.size(); ++shift)
    {
      bool equal = true;
      for (size_t i = 0; i < a.size(); ++i)
      {
        if (a[i] != b[(i + shift) % b.size()])
        {
          equal = false;
          break;
        }
      }
      if (equal)
        return true;
    }

    std::reverse(b.begin(), b.end());

    for (size_t shift = 0; shift < b.size(); ++shift)
    {
      bool equal = true;
      for (size_t i = 0; i < a.size(); ++i)
      {
        if (a[i] != b[(i + shift) % b.size()])
        {
          equal = false;
          break;
        }
      }
      if (equal)
        return true;
    }

    return false;
  }

  double Polygon::getArea() const
  {
    double area = 0.0;
    for (size_t i = 0; i < points_.size(); ++i)
    {
      const Point& a = points_[i];
      const Point& b = points_[(i + 1) % points_.size()];
      area += (a.x * b.y - b.x * a.y);
    }
    return std::abs(area) / 2.0;
  }
}
