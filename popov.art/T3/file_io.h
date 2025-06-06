#ifndef FILE_IO_HPP
#define FILE_IO_HPP
#include "geometry.hpp"
#include <vector>
#include <fstream>
namespace popov
{
  std::vector<Polygon> readPolygonsFromFile(const std::string& filename);
}
#endif
