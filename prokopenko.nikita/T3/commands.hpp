#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iostream>
#include "polygon.hpp"

namespace prokopenko {

  // AREA <EVEN|ODD|MEAN|num>
  void Area(std::vector<Polygon>&, std::ostream&);
  // MAX <AREA|VERTEXES>
  void Max(std::vector<Polygon>&, std::ostream&);
  // MIN <AREA|VERTEXES>
  void Min(std::vector<Polygon>&, std::ostream&);
  // MEAN: синоним AREA MEAN
  void Mean(std::vector<Polygon>&, std::ostream&);
  // COUNT <EVEN|ODD|num>
  void Count(std::vector<Polygon>&, std::ostream&);
  // PERMS <Polygon>
  void Perms(std::vector<Polygon>&, std::ostream&);
  // MAXSEQ <Polygon>
  void MaxSeq(std::vector<Polygon>&, std::ostream&);
  // RMECHO <Polygon>
  void RmEcho(std::vector<Polygon>&, std::ostream&);
  // ECHO <Polygon>
  void Echo(std::vector<Polygon>&, std::ostream&);
  // LESSAREA <Polygon>
  void LessArea(std::vector<Polygon>&, std::ostream&);
  // INFRAME <Polygon>
  void InFrame(std::vector<Polygon>&, std::ostream&);
  // INTERSECTIONS <Polygon>
  void Intersections(std::vector<Polygon>&, std::ostream&);
  // SAME <Polygon>
  void Same(std::vector<Polygon>&, std::ostream&);
  // RECTS
  void Rects(std::vector<Polygon>&, std::ostream&);
  // RIGHTSHAPES
  void RightShapes(std::vector<Polygon>&, std::ostream&);

} // namespace prokopenko

#endif // COMMANDS_HPP
