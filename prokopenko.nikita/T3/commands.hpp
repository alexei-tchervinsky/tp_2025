#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace prokopenko
{
  void CountEven(const std::vector<Polygon>&, std::ostream&);
  void CountOdd(const std::vector<Polygon>&, std::ostream&);
  void CountN(const std::vector<Polygon>&, std::ostream&, size_t n);

  void Area(const std::vector<Polygon>&, std::ostream&);
  void AreaEven(const std::vector<Polygon>&, std::ostream&);
  void AreaOdd(const std::vector<Polygon>&, std::ostream&);
  void AreaN(const std::vector<Polygon>&, std::ostream&, size_t n);

  void MeanArea(const std::vector<Polygon>&, std::ostream&);

  void MaxArea(const std::vector<Polygon>&, std::ostream&);
  void MaxVertexes(const std::vector<Polygon>&, std::ostream&);
  void MinArea(const std::vector<Polygon>&, std::ostream&);
  void MinVertexes(const std::vector<Polygon>&, std::ostream&);

  void Same(const std::vector<Polygon>&, std::ostream&);
  void Right(const std::vector<Polygon>&, std::ostream&);
  void Perms(const std::vector<Polygon>&, std::ostream&);
  void Less(const std::vector<Polygon>&, std::ostream&);
  void More(const std::vector<Polygon>&, std::ostream&);
  void Equal(const std::vector<Polygon>&, std::ostream&);
}

#endif
