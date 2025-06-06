#ifndef POLYGON_OPERATIONS_HPP
#define POLYGON_OPERATIONS_HPP
#include "geometry.hpp"
#include <vector>
#include <iostream>
namespace popov
{
  void area(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void max(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void min(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void count(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void rightshapes(const std::vector< Polygon >& value, std::ostream& out);
  void echo(std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void inframe(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void lessArea(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void intersections(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
}
#endif
