#include "geometry.hpp"
#include <cmath>

static int orientation(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

static bool onSegment(const Point& p, const Point& q, const Point& r) {
    if (orientation(p, q, r) != 0) {
        return false;
    }
    return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
}

static bool segmentsIntersect(const Point& p1, const Point& q1, const Point& p2, const Point& q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if ((o1 > 0 && o2 < 0) || (o1 < 0 && o2 > 0)) {
        if ((o3 > 0 && o4 < 0) || (o3 < 0 && o4 > 0)) {
            return true;
        }
    }

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

static bool isPointInPolygon(const Point& point, const Polygon& poly) {
    int count = 0;
    int n = poly.points.size();
    if (n < 3) return false;

    for (int i = 0; i < n; i++) {
        const Point& p1 = poly.points[i];
        const Point& p2 = poly.points[(i+1) % n];

        // Удалена строка с пропуском горизонтальных ребер
        bool cond1 = (p1.y <= point.y) && (point.y < p2.y);
        bool cond2 = (p2.y <= point.y) && (point.y < p1.y);

        if (cond1 || cond2) {
            int orient_val = orientation(p1, p2, point);
            if (cond1 && orient_val > 0) count++;
            else if (cond2 && orient_val < 0) count++;
        }
    }
    return count % 2 == 1;
}

static bool isPointOnPolygonEdge(const Point& point, const Polygon& poly) {
    int n = poly.points.size();
    for (int i = 0; i < n; i++) {
        const Point& p1 = poly.points[i];
        const Point& p2 = poly.points[(i+1) % n];
        if (onSegment(p1, point, p2)) return true;
    }
    return false;
}

static bool polygonsIntersect(const Polygon& poly1, const Polygon& poly2) {
    int n1 = poly1.points.size();
    int n2 = poly2.points.size();

    // Проверка пересечения ребер
    for (int i = 0; i < n1; i++) {
        const Point& a1 = poly1.points[i];
        const Point& a2 = poly1.points[(i+1) % n1];
        for (int j = 0; j < n2; j++) {
            const Point& b1 = poly2.points[j];
            const Point& b2 = poly2.points[(j+1) % n2];
            if (segmentsIntersect(a1, a2, b1, b2)) return true;
        }
    }

    // Проверка вхождения вершин
    for (const Point& p : poly1.points) {
        if (isPointInPolygon(p, poly2) || isPointOnPolygonEdge(p, poly2)) return true;
    }

    for (const Point& p : poly2.points) {
        if (isPointInPolygon(p, poly1) || isPointOnPolygonEdge(p, poly1)) return true;
    }

    return false;
}

std::size_t countIntersections(const std::vector<Polygon>& polygons, const Polygon& target) {
    std::size_t count = 0;
    for (const Polygon& poly : polygons) {
        if (polygonsIntersect(target, poly)) {
            count++;
        }
    }
    return count;
}
