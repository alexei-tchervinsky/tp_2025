// GeometryUtils.cpp
#include "GeometryUtils.h"
#include <cmath>
#include <algorithm>

double getArea(const Polygon& poly) {
    double area = 0.0;
    size_t n = poly.points.size();
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        area += static_cast<double>(poly.points[i].x * poly.points[j].y - poly.points[j].x * poly.points[i].y);
    }
    return std::abs(area) / 2.0;
}

bool isSamePolygon(const Polygon& a, const Polygon& b) {
    if (a.points.size() != b.points.size()) {
        return false;
    }

    std::vector<Point> aPoints = a.points;
    std::vector<Point> bPoints = b.points;

    auto pointLess = [](const Point& p1, const Point& p2) {
        return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x;
    };

    std::sort(aPoints.begin(), aPoints.end(), pointLess);
    std::sort(bPoints.begin(), bPoints.end(), pointLess);

    return aPoints == bPoints;
}

