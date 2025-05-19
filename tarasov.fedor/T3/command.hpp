#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <functional>
#include <numeric>
#include "readfile.hpp"
#include "structures.hpp"

namespace tarasov {
    double calculateArea(const Polygon& polygon);

    void areaCommand(const std::vector<Polygon>& polygons, const std::string& sub_command);

    void maxCommand(const std::vector<Polygon>& polygons, const std::string& sub_command);

    void minCommand(const std::vector<Polygon>& polygons, const std::string& sub_command);

    void countCommand(const std::vector<Polygon>& polygons, const std::string& sub_command);

    bool perms(Polygon p1, Polygon p2);

    void permsCommand(const std::vector<Polygon>& polygons, std::stringstream& params);

    bool isRightAngle(Point a, Point b, Point c);

    bool hasRightAngle(const Polygon& polygon);

    void rightShapesCommand(const std::vector<Polygon>& polygons);
}

#endif //COMMAND_HPP
