#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iostream>
#include "polygon.hpp"

namespace prokopenko {

  void Area(std::vector<Polygon>&, std::ostream&);
  void Max(std::vector<Polygon>&, std::ostream&);
  void Min(std::vector<Polygon>&, std::ostream&);
  void Mean(std::vector<Polygon>&, std::ostream&);
  void Count(std::vector<Polygon>&, std::ostream&);
  void Perms(std::vector<Polygon>&, std::ostream&);
  void MaxSeq(std::vector<Polygon>&, std::ostream&);
  void RmEcho(std::vector<Polygon>&, std::ostream&);
  void Echo(std::vector<Polygon>&, std::ostream&);
  void LessArea(std::vector<Polygon>&, std::ostream&);
  void InFrame(std::vector<Polygon>&, std::ostream&);
  void Intersections(std::vector<Polygon>&, std::ostream&);
  void Same(std::vector<Polygon>&, std::ostream&);
  void Rects(std::vector<Polygon>&, std::ostream&);
  void RightShapes(std::vector<Polygon>&, std::ostream&);

} // namespace prokopenko

#endif // COMMANDS_HPP
