#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <iostream>
#include "point.h"

struct Polygon {
    std::vector<Point> points;
    double area() const;
    bool hasRightAngle() const;
    bool isPermutation(const Polygon& other) const;
    size_t vertexCount() const;
};

std::istream& operator>>(std::istream& in, Polygon& poly);
std::ostream& operator<<(std::ostream& out, const Polygon& poly);

#endif
