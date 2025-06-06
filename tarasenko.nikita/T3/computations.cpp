#include "computations.hpp"
#include <cmath>
#include <sstream>
#include <algorithm>

double computeArea(const Polygon& poly) {
    double area = 0.0;
    size_t n = poly.points.size();
    for (size_t i = 0; i < n; ++i) {
        const Point& p1 = poly.points[i];
        const Point& p2 = poly.points[(i + 1) % n];
        area += (p1.x * p2.y) - (p1.y * p2.x);
    }
    return std::abs(area) / 2.0;
}

bool doSegmentsIntersect(const Point& p1, const Point& p2, const Point& q1, const Point& q2) {
    auto orientation = [](const Point& a, const Point& b, const Point& c) {
        int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
        if (val == 0) return 0;
        return (val > 0) ? 1 : 2;
        };

    auto onSegment = [](const Point& p, const Point& q, const Point& r) {
        return q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y);
        };

    int o1 = orientation(p1, p2, q1);
    int o2 = orientation(p1, p2, q2);
    int o3 = orientation(q1, q2, p1);
    int o4 = orientation(q1, q2, p2);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(p1, q1, p2)) return true;
    if (o2 == 0 && onSegment(p1, q2, p2)) return true;
    if (o3 == 0 && onSegment(q1, p1, q2)) return true;
    if (o4 == 0 && onSegment(q1, p2, q2)) return true;

    return false;
}

bool doPolygonsIntersect(const Polygon& a, const Polygon& b) {
    for (size_t i = 0; i < a.points.size(); ++i) {
        const Point& a1 = a.points[i];
        const Point& a2 = a.points[(i + 1) % a.points.size()];

        for (size_t j = 0; j < b.points.size(); ++j) {
            const Point& b1 = b.points[j];
            const Point& b2 = b.points[(j + 1) % b.points.size()];

            if (doSegmentsIntersect(a1, a2, b1, b2)) {
                return true;
            }
        }
    }
    return false;
}

bool parsePolygon(const std::string& str, Polygon& poly) {
    std::istringstream iss(str);
    size_t numVertices;
    if (!(iss >> numVertices)) return false;

    poly.points.clear();
    for (size_t i = 0; i < numVertices; ++i) {
        char c1, c2, c3;
        int x, y;
        if (!(iss >> c1 >> x >> c2 >> y >> c3) || c1 != '(' || c2 != ';' || c3 != ')') {
            return false;
        }
        poly.points.push_back({ x, y });
    }

    return true;
}