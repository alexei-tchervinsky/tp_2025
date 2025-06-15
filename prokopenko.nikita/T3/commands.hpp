#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace prokopenko {

  void Area(const std::vector<Polygon>& polys, std::ostream& out);

  void Max(const std::vector<Polygon>& polys, std::ostream& out);

  void Min(const std::vector<Polygon>& polys, std::ostream& out);

  void Mean(const std::vector<Polygon>& polys, std::ostream& out);

  void CountOdd(const std::vector<Polygon>& polys, std::ostream& out);

  void CountEven(const std::vector<Polygon>& polys, std::ostream& out);

  void CountN(const std::vector<Polygon>& polys, std::ostream& out, size_t n);

  void Same(const std::vector<Polygon>& polys, std::ostream& out);

  void Right(const std::vector<Polygon>& polys, std::ostream& out);

  void Perms(const std::vector<Polygon>& polys, std::ostream& out);

  void Less(const std::vector<Polygon>& polys, std::ostream& out);

  void More(const std::vector<Polygon>& polys, std::ostream& out);

  void Equal(const std::vector<Polygon>& polys, std::ostream& out);

} // namespace prokopenko

#endif // COMMANDS_HPP
