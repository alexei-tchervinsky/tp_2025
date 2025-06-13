#include "commands.hpp"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iterator>

namespace prokopenko
{
  static double area(const Polygon& poly)
  {
    if (poly.size() < 3)
      return 0.0;
    double sum = 0.0;
    for (size_t i = 0; i < poly.size(); ++i)
    {
      const Point& a = poly[i];
      const Point& b = poly[(i + 1) % poly.size()];
      sum += (a.x * b.y - b.x * a.y);
    }
    return std::abs(sum) / 2.0;
  }

  static bool isRightAngle(const Point& a, const Point& b, const Point& c)
  {
    int dx1 = a.x - b.x, dy1 = a.y - b.y;
    int dx2 = c.x - b.x, dy2 = c.y - b.y;
    return dx1 * dx2 + dy1 * dy2 == 0;
  }

  static bool isRightPolygon(const Polygon& poly)
  {
    if (poly.size() < 3)
      return false;
    for (size_t i = 0; i < poly.size(); ++i)
    {
      const Point& a = poly[(i + poly.size() - 1) % poly.size()];
      const Point& b = poly[i];
      const Point& c = poly[(i + 1) % poly.size()];
      if (!isRightAngle(a, b, c))
        return false;
    }
    return true;
  }

  void Area(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    for (const auto& p : polygons)
    {
      out << area(p) << '\n';
    }
  }

  void Max(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    if (polygons.empty())
      return;
    const Polygon* maxPoly = &polygons[0];
    double maxArea = area(polygons[0]);
    for (const auto& p : polygons)
    {
      double a = area(p);
      if (a > maxArea)
      {
        maxArea = a;
        maxPoly = &p;
      }
    }
    out << *maxPoly << '\n';
  }

  void Min(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    if (polygons.empty())
      return;
    const Polygon* minPoly = &polygons[0];
    double minArea = area(polygons[0]);
    for (const auto& p : polygons)
    {
      double a = area(p);
      if (a < minArea)
      {
        minArea = a;
        minPoly = &p;
      }
    }
    out << *minPoly << '\n';
  }

  void Mean(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      out << "0\n";
      return;
    }
    double total = 0.0;
    for (const auto& p : polygons)
    {
      total += area(p);
    }
    out << (total / polygons.size()) << '\n';
  }

  void Same(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    for (size_t i = 0; i < polygons.size(); ++i)
    {
      for (size_t j = i + 1; j < polygons.size(); ++j)
      {
        const Polygon& a = polygons[i];
        const Polygon& b = polygons[j];
        if (a.size() != b.size())
          continue;
        bool same = false;
        for (size_t shift = 0; shift < b.size(); ++shift)
        {
          same = true;
          for (size_t k = 0; k < a.size(); ++k)
          {
            if (a[k] != b[(k + shift) % b.size()])
            {
              same = false;
              break;
            }
          }
          if (same)
            break;
          same = true;
          for (size_t k = 0; k < a.size(); ++k)
          {
            if (a[k] != b[(b.size() + shift - k) % b.size()])
            {
              same = false;
              break;
            }
          }
          if (same)
            break;
        }
        if (same)
        {
          out << a.size();
          for (const Point& pt : a)
          {
            out << " " << pt;
          }
          out << '\n';
        }
      }
    }
  }

  void Right(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    for (const auto& p : polygons)
    {
      if (isRightPolygon(p))
      {
        out << p.size();
        for (const auto& pt : p)
        {
          out << " " << pt;
        }
        out << '\n';
      }
    }
  }

  void Perms(const std::vector<Polygon>&, std::ostream&) {}
  void Less(const std::vector<Polygon>&, std::ostream&) {}
  void More(const std::vector<Polygon>&, std::ostream&) {}
  void Equal(const std::vector<Polygon>&, std::ostream&) {}

  void CountOdd(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p) { return p.size() % 2 == 1; });
    out << count << '\n';
  }

  void CountEven(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p) { return p.size() % 2 == 0; });
    out << count << '\n';
  }

  void CountN(const std::vector<Polygon>& polygons, std::ostream& out, size_t n)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(),
      [n](const Polygon& p) { return p.size() == n; });
    out << count << '\n';
  }
}
