#include "geometry.h"

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

bool Polygon::operator==(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    for (size_t i = 0; i < points.size(); ++i) {
        if (!(points[i] == other.points[i])) return false;
    }
    return true;
}
