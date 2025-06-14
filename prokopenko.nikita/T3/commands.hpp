#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iostream>
#include <istream>
#include "polygon.hpp"

namespace prokopenko {

  // Основные команды: принимают polygons, входной поток и выходной поток
  void Area(const std::vector<Polygon>&, std::istream&, std::ostream&);
  void Max(const std::vector<Polygon>&, std::istream&, std::ostream&);
  void Min(const std::vector<Polygon>&, std::istream&, std::ostream&);
  void Mean(const std::vector<Polygon>&, std::ostream&); // не требует дополнительного параметра
  void Same(const std::vector<Polygon>&, std::istream&, std::ostream&);
  void Right(const std::vector<Polygon>&, std::ostream&);
  void Perms(const std::vector<Polygon>&, std::istream&, std::ostream&);
  void Less(const std::vector<Polygon>&, std::istream&, std::ostream&);
  void More(const std::vector<Polygon>&, std::istream&, std::ostream&);
  void Equal(const std::vector<Polygon>&, std::istream&, std::ostream&);

  // Для COUNT
  void Count(const std::vector<Polygon>&, std::istream&, std::ostream&);
  void CountOdd(const std::vector<Polygon>&, std::ostream&);
  void CountEven(const std::vector<Polygon>&, std::ostream&);
  void CountN(const std::vector<Polygon>&, std::ostream&, size_t);

} // namespace prokopenko

#endif // COMMANDS_HPP
