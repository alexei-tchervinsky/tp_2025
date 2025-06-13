#include "polygon.hpp"
#include <cctype>
#include <limits>

namespace prokopenko
{
  bool Point::operator==(const Point& other) const
  {
    return x == other.x && y == other.y;
  }

  std::istream& operator>>(std::istream& in, Point& point)
  {
    char ch = 0;
    in >> std::ws >> ch;
    if (ch != '(')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> point.x >> ch;
    if (ch != ';')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> point.y >> ch;
    if (ch != ')')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& polygon)
  {
    size_t size = 0;
    in >> size;
    if (!in)
    {
      return in;
    }
    Polygon temp;
    for (size_t i = 0; i < size; ++i)
    {
      Point point;
      in >> point;
      if (!in)
      {
        return in;
      }
      temp.push_back(point);
    }
    polygon = std::move(temp);
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Point& point)
  {
    return out << "(" << point.x << ";" << point.y << ")";
  }

  std::ostream& operator<<(std::ostream& out, const Polygon& polygon)
  {
    out << polygon.size();
    for (const Point& pt : polygon)
    {
      out << " " << pt;
    }
    return out;
  }
}
