#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "polygon.hpp"
#include <vector>
#include <ostream>

namespace prokopenko {

  void Max(const std::vector<Polygon>& polygons, std::ostream& out);
  void Min(const std::vector<Polygon>& polygons, std::ostream& out);
  void Mean(const std::vector<Polygon>& polygons, std::ostream& out);
  void Area(const std::vector<Polygon>& polygons, std::ostream& out);
  void Same(const std::vector<Polygon>& polygons, std::ostream& out);
  void Right(const std::vector<Polygon>& polygons, std::ostream& out);
  void Perms(const std::vector<Polygon>& polygons, std::ostream& out);
  void Less(const std::vector<Polygon>& polygons, std::ostream& out);
  void More(const std::vector<Polygon>& polygons, std::ostream& out);
  void Equal(const std::vector<Polygon>& polygons, std::ostream& out);

} // namespace prokopenko

#endif // COMMANDS_HPP
