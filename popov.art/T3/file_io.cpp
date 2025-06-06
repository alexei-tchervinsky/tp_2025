#include "file_io.hpp"
#include <iterator>
#include <limits>
std::vector<popov::Polygon> popov::readPolygonsFromFile(const std::string& filename)
{
  std::ifstream in(filename);
  if (!in.is_open())
  {
    throw std::runtime_error("File not open");
  }
  std::vector<Polygon> polygons;
  using input_it_t = std::istream_iterator<Polygon>;
  while (!in.eof())
  {
    std::copy(input_it_t{in}, input_it_t{}, std::back_inserter(polygons));
    if (in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  in.close();
  return polygons;
}
