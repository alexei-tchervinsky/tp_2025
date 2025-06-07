#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <iostream>
#include <vector>
#include <functional>

namespace geom_lab
{
  struct DelimiterChar
  {
    char expected;
  };
  std::istream & operator>>(std::istream& in, DelimiterChar&& exp);

  struct DelimiterString
  {
    const char * expected;
  };
  std::istream& operator>>(std::istream& in, DelimiterString&& exp);

  struct Point
  {
    int x;
    int y;
  };
  std::istream& operator>>(std::istream& in, Point& point);
  bool operator==(const Point& lhs, const Point& rhs);

  struct Polygon
  {
    std::vector< Point > points;
  };
  double getPolygonArea(const Polygon& polygon);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  bool operator==(const Polygon& lhs, const Polygon& rhs);
  bool operator<=(const Polygon& lhs, const Polygon& rhs);
  bool isRightAngle(const Polygon& polygon);
  int findMaxX(const Polygon& polygon);
  int findMaxY(const Polygon& polygon);
  int findMinX(const Polygon& polygon);
  int findMinY(const Polygon& polygon);
  Polygon getBoundingBox(const std::vector< Polygon >& polygon);

  struct AreaPolygon
  {
    Point p1;
    double operator()(double area, const Point& p2, const Point& p3);
  };

  struct accumulateRightAngle
  {
    Point p1;
    Point p2;
    bool operator()(const Point& p3);
  };

  void area(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void max(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void min(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void count(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void rightshapes(const std::vector< Polygon >& value, std::ostream& out);
  void echo(std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void inframe(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);

  void perms(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void maxseq(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
}

#endif
