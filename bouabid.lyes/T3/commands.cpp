#include "commands.h"
#include <algorithm>
#include <numeric>

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

    if (all_points.empty()) return false;

auto min_max_x = std::minmax_element(all_points.begin(), all_points.end(),
    [](auto a, auto b) { return a.x < b.x; });
auto min_x = min_max_x.first;
auto max_x = min_max_x.second;

auto min_max_y = std::minmax_element(all_points.begin(), all_points.end(),
    [](auto a, auto b) { return a.y < b.y; });
auto min_y = min_max_y.first;
auto max_y = min_max_y.second;


return std::all_of(target.points.begin(), target.points.end(),
    [=](auto p) {
        return p.x >= (*min_x).x && p.x <= (*max_x).x && p.y >= (*min_y).y && p.y <= (*max_y).y;

        });
}
