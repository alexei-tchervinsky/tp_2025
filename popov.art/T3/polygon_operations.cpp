#include "polygon_operations.h"
#include <cmath>
#include <algorithm>
#include <limits>
using namespace std;
double calculateArea(const Polygon& poly) {
    if (poly.points.size() < 3) return 0.0;
    double area = 0.0;
    size_t n = poly.points.size();
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        area += (poly.points[i].x * poly.points[j].y) - (poly.points[j].x * poly.points[i].y);
    }
    return abs(area) / 2.0;
}
bool isPolygonInFrame(const Polygon& poly, const vector<Polygon>& polygons) {
    if (polygons.empty() || poly.points.empty()) return false;
    int min_x = numeric_limits<int>::max();
    int max_x = numeric_limits<int>::min();
    int min_y = numeric_limits<int>::max();
    int max_y = numeric_limits<int>::min();
    for (const auto& p : polygons) {
        if (p.points.size() < 3) continue;
        for (const auto& point : p.points) {
            min_x = min(min_x, point.x);
            max_x = max(max_x, point.x);
            min_y = min(min_y, point.y);
            max_y = max(max_y, point.y);
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
    if (a.points.size() < 3 || b.points.size() < 3) return false;
    auto a_min_x = min_element(a.points.begin(), a.points.end(),
        [](const Point& p1, const Point& p2) { return p1.x < p2.x; });
    auto a_max_x = max_element(a.points.begin(), a.points.end(),
        [](const Point& p1, const Point& p2) { return p1.x < p2.x; });
    auto a_min_y = min_element(a.points.begin(), a.points.end(),
        [](const Point& p1, const Point& p2) { return p1.y < p2.y; });
    auto a_max_y = max_element(a.points.begin(), a.points.end(),
        [](const Point& p1, const Point& p2) { return p1.y < p2.y; });
    auto b_min_x = min_element(b.points.begin(), b.points.end(),
        [](const Point& p1, const Point& p2) { return p1.x < p2.x; });
    auto b_max_x = max_element(b.points.begin(), b.points.end(),
        [](const Point& p1, const Point& p2) { return p1.x < p2.x; });
    auto b_min_y = min_element(b.points.begin(), b.points.end(),
        [](const Point& p1, const Point& p2) { return p1.y < p2.y; });
    auto b_max_y = max_element(b.points.begin(), b.points.end(),
        [](const Point& p1, const Point& p2) { return p1.y < p2.y; });
    return !(a_max_x->x < b_min_x->x || a_min_x->x > b_max_x->x ||
             a_max_y->y < b_min_y->y || a_min_y->y > b_max_y->y);
}
