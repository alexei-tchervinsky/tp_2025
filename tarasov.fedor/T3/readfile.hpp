#ifndef READFILE_HPP
#define READFILE_HPP
#include <sstream>
#include <fstream>
#include <ranges>
#include "structures.hpp"

namespace tarasov {
    Polygon parsePolygon(const std::string& str);

    std::vector<Polygon> readFile(const std::string& fileName);
}

#endif
