#include "polygon_operations.h"
#include <cmath>
#include <algorithm>
#include <sstream>
double calculateArea(const Polygon& poly) {
    double area = 0.0;
    int n = poly.points.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += (poly.points[i].x * poly.points[j].y) - (poly.points[j].x * poly.points[i].y);
    }
    return std::abs(area) / 2.0;
}
bool isPolygonInFrame(const Polygon& poly, const std::vector<Polygon>& polygons) {
    if (polygons.empty()) return false;
    int min_x = polygons[0].points[0].x;
    int max_x = polygons[0].points[0].x;
    int min_y = polygons[0].points[0].y;
    int max_y = polygons[0].points[0].y;
    for (const auto& p : polygons) {
        for (const auto& point : p.points) {
            min_x = std::min(min_x, point.x);
            max_x = std::max(max_x, point.x);
            min_y = std::min(min_y, point.y);
            max_y = std::max(max_y, point.y);
        }
    }
    for (const auto& point : poly.points) {
        if (point.x < min_x || point.x > max_x || point.y < min_y || point.y > max_y) {
            return false;
        }
    }
    return true;
}
bool doPolygonsIntersect(const Polygon& a, const Polygon& b) {
    int a_min_x = a.points[0].x, a_max_x = a.points[0].x;
    int a_min_y = a.points[0].y, a_max_y = a.points[0].y;
    for (const auto& p : a.points) {
        a_min_x = std::min(a_min_x, p.x);
        a_max_x = std::max(a_max_x, p.x);
        a_min_y = std::min(a_min_y, p.y);
        a_max_y = std::max(a_max_y, p.y);
    }
    int b_min_x = b.points[0].x, b_max_x = b.points[0].x;
    int b_min_y = b.points[0].y, b_max_y = b.points[0].y;
    for (const auto& p : b.points) {
        b_min_x = std::min(b_min_x, p.x);
        b_max_x = std::max(b_max_x, p.x);
        b_min_y = std::min(b_min_y, p.y);
        b_max_y = std::max(b_max_y, p.y);
    }
    return !(a_max_x < b_min_x || a_min_x > b_max_x || a_max_y < b_min_y || a_min_y > b_max_y);
}
