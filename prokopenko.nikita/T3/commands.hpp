#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iostream>
#include "polygon.hpp"

namespace prokopenko {

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
  void CountN(const std::vector<Polygon>&, std::ostream&, size_t);

} // namespace prokopenko

#endif // COMMANDS_HPP
