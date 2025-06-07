// Polygon.h
#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "Point.h"

struct Polygon {
    std::vector<Point> points;
};

std::istream& operator>>(std::istream& in, Polygon& poly);

#endif // POLYGON_H

