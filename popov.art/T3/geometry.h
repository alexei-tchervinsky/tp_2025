#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <string>

struct Point {
    int x, y;
    bool operator==(const Point& other) const;
};

struct Polygon {
    std::vector<Point> points;
    bool operator==(const Polygon& other) const;
};

#endif // GEOMETRY_H
