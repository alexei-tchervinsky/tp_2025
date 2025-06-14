#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <functional>
#include <numeric>
#include "read.hpp"
#include "Structs.hpp"

namespace vlad {
    double calculateArea(const Polygon& polygon);
    void area(const std::vector<Polygon>& polygons, const std::string& sub_command);
    void max(const std::vector<Polygon>& polygons, const std::string& sub_command);
    void min(const std::vector<Polygon>& polygons, const std::string& sub_command);
    void count(const std::vector<Polygon>& polygons, const std::string& sub_command);
    bool perms(Polygon p1, Polygon p2);
    void perms(const std::vector<Polygon>& polygons, std::stringstream& params);
    void maxSeq(const std::vector<vlad::Polygon>& poly, std::stringstream& ss);
}

#endif

