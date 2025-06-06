#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "point.hpp"

struct Polygon {
    std::vector<Point> points;
    bool operator==(const Polygon& other) const {
        return points == other.points;
    }
};

#endif // POLYGON_HPP