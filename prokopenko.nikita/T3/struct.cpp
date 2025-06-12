#include "polygon.hpp"
#include <iostream>

namespace prokopenko
{
  std::istream& operator>>(std::istream& in, Point& point)
  {
    char ch1 = 0;
    char ch2 = 0;
    in >> ch1 >> point.x >> ch2 >> point.y;
    if (ch1 != '(' || ch2 != ')')
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& polygon)
  {
    size_t size = 0;
    in >> size;
    if (size < 3)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    polygon.clear();
    for (size_t i = 0; i < size; ++i)
    {
      Point point;
      in >> point;
      if (!in)
      {
        return in;
      }
      polygon.push_back(point);
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Point& point)
  {
    out << '(' << point.x << ';' << point.y << ')';
    return out;
  }

  std::ostream& operator<<(std::ostream& out, const Polygon& polygon)
  {
    for (size_t i = 0; i < polygon.size(); ++i)
    {
      out << polygon[i];
      if (i + 1 < polygon.size())
      {
        out << ' ';
      }
    }
    return out;
  }
}
