#include "commands.h"
#include <algorithm>
#include <numeric>
#include <cmath>

size_t handleEcho(std::vector<Polygon>& polygons, const Polygon& target) {
    std::vector<Polygon> newPolygons;
    size_t count = std::accumulate(polygons.begin(), polygons.end(), 0UL,
        [&](size_t acc, const Polygon& p) {
            newPolygons.push_back(p);
            if (p == target) {
                newPolygons.push_back(p);
                return acc + 1;
            }
            return acc;
        });
    polygons.swap(newPolygons);
    return count;
}

bool handleInFrame(const std::vector<Polygon>& polygons, const Polygon& target) {
    if (polygons.empty() || target.points.empty()) return false;

    auto all_points = std::accumulate(polygons.begin(), polygons.end(), std::vector<Point>(),
        [](auto acc, const auto& poly) {
            acc.insert(acc.end(), poly.points.begin(), poly.points.end());
            return acc;
        });

    auto min_max_x = std::minmax_element(all_points.begin(), all_points.end(),
        [](const Point& a, const Point& b) { return a.x < b.x; });
    auto min_x = min_max_x.first;
    auto max_x = min_max_x.second;

    auto min_max_y = std::minmax_element(all_points.begin(), all_points.end(),
        [](const Point& a, const Point& b) { return a.y < b.y; });
    auto min_y = min_max_y.first;
    auto max_y = min_max_y.second;

    return std::all_of(target.points.begin(), target.points.end(),
        [&](const Point& p) {
            return p.x >= (*min_x).x && p.x <= (*max_x).x &&
                   p.y >= (*min_y).y && p.y <= (*max_y).y;
        });
}

double calculateArea(const Polygon& polygon) {
    if (polygon.points.size() < 3) return 0.0;

    double area = 0.0;
    size_t n = polygon.points.size();

    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        area += polygon.points[i].x * polygon.points[j].y;
        area -= polygon.points[j].x * polygon.points[i].y;
    }

    return std::abs(area) / 2.0;
}

size_t countPolygonsByVertices(const std::vector<Polygon>& polygons, int vertices) {
    return std::count_if(polygons.begin(), polygons.end(),
        [vertices](const Polygon& p) { return p.points.size() == vertices; });
}

size_t countEvenPolygons(const std::vector<Polygon>& polygons) {
    return std::count_if(polygons.begin(), polygons.end(),
        [](const Polygon& p) { return p.points.size() % 2 == 0; });
}

size_t countOddPolygons(const std::vector<Polygon>& polygons) {
    return std::count_if(polygons.begin(), polygons.end(),
        [](const Polygon& p) { return p.points.size() % 2 != 0; });
}

double calculateAreaByVertices(const std::vector<Polygon>& polygons, int vertices) {
    return std::accumulate(polygons.begin(), polygons.end(), 0.0,
        [vertices](double sum, const Polygon& p) {
            return sum + (p.points.size() == vertices ? calculateArea(p) : 0.0);
        });
}

double calculateEvenArea(const std::vector<Polygon>& polygons) {
    return std::accumulate(polygons.begin(), polygons.end(), 0.0,
        [](double sum, const Polygon& p) {
            return sum + (p.points.size() % 2 == 0 ? calculateArea(p) : 0.0);
        });
}

double calculateOddArea(const std::vector<Polygon>& polygons) {
    return std::accumulate(polygons.begin(), polygons.end(), 0.0,
        [](double sum, const Polygon& p) {
            return sum + (p.points.size() % 2 != 0 ? calculateArea(p) : 0.0);
        });
}

double calculateMeanArea(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) return 0.0;
    double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
        [](double sum, const Polygon& p) { return sum + calculateArea(p); });
    return std::round(totalArea / polygons.size() * 10) / 10.0;  // Round to 1 decimal place
}

double getMaxArea(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) return 0.0;
    return calculateArea(*std::max_element(polygons.begin(), polygons.end(),
        [](const Polygon& a, const Polygon& b) {
            return calculateArea(a) < calculateArea(b);
        }));
}

int getMaxVertices(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) return 0;
    return std::max_element(polygons.begin(), polygons.end(),
        [](const Polygon& a, const Polygon& b) {
            return a.points.size() < b.points.size();
        })->points.size();
}
