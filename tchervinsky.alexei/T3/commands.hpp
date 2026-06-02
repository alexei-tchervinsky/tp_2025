#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "DataStruct.hpp"

namespace nspace
{
    void area(const std::vector<Polygon>& polygons, const std::string& param);
    void max(const std::vector<Polygon>& polygons, const std::string& param);
    void min(const std::vector<Polygon>& polygons, const std::string& param);
    void count(const std::vector<Polygon>& polygons, const std::string& param);
    void echo(std::vector<Polygon>& polygons, const Polygon& target, const std::string& filename);
    void maxSeq(const std::vector<Polygon>& polygons, const Polygon& target);
}

#endif
