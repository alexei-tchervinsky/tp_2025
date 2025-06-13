main.cpp
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <limits>
#include <functional>
#include "commands.hpp"

using namespace prokopenko;

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: wrong input\n";
    return 1;
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Error: file cannot be opened\n";
    return 1;
  }

  std::vector<Polygon> polygons;
  while (!input.eof())
  {
    Polygon poly;
    std::streampos pos = input.tellg();
    if (input >> poly)
    {
      polygons.push_back(poly);
    }
    else
    {
      input.clear();
      input.seekg(pos);
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::map<std::string, std::function<void(const std::vector<Polygon>&, std::ostream&)>> commands;
  commands["AREA"] = Area;
  commands["MAX"] = Max;
  commands["MIN"] = Min;
  commands["MEAN"] = Mean;
  commands["SAME"] = Same;
  commands["RIGHT"] = Right;
  commands["PERMS"] = Perms;
  commands["LESS"] = Less;
  commands["MORE"] = More;
  commands["EQUAL"] = Equal;
  commands["COUNT"] = [](const std::vector<Polygon>& polys, std::ostream& out)
    {
      std::string param;
      std::cin >> param;
      if (param == "ODD")
      {
        CountOdd(polys, out);
      }
      else if (param == "EVEN")
      {
        CountEven(polys, out);
      }
      else
      {
        try
        {
          size_t n = std::stoul(param);
          CountN(polys, out, n);
        }
        catch (...)
        {
          out << "<INVALID COMMAND>\n";
        }
      }
    };

  std::string cmd;
  while (std::cin >> cmd)
  {
    auto it = commands.find(cmd);
    if (it != commands.end())
    {
      it->second(polygons, std::cout);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  return 0;
}

commands.hpp
#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iostream>
#include "polygon.hpp"

namespace prokopenko
{
  void Area(const std::vector<Polygon>&, std::ostream&);
  void Max(const std::vector<Polygon>&, std::ostream&);
  void Min(const std::vector<Polygon>&, std::ostream&);
  void Mean(const std::vector<Polygon>&, std::ostream&);
  void Same(const std::vector<Polygon>&, std::ostream&);
  void Right(const std::vector<Polygon>&, std::ostream&);
  void Perms(const std::vector<Polygon>&, std::ostream&);
  void Less(const std::vector<Polygon>&, std::ostream&);
  void More(const std::vector<Polygon>&, std::ostream&);
  void Equal(const std::vector<Polygon>&, std::ostream&);

  void CountOdd(const std::vector<Polygon>&, std::ostream&);
  void CountEven(const std::vector<Polygon>&, std::ostream&);
  void CountN(const std::vector<Polygon>&, std::ostream&, size_t n);
}

#endif

polygon.hpp
#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace prokopenko
{
  struct Point
  {
    int x, y;
    bool operator==(const Point& other) const;
  };

  using Polygon = std::vector<Point>;

  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Point& point);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);
}

#endif

polygon.cpp
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

commands.cpp
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