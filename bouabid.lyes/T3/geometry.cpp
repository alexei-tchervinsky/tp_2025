#include "geometry.h"
#include <sstream>
#include <algorithm>
#include <fstream>

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

bool Polygon::operator==(const Polygon& other) const {
    return points == other.points;
}

Polygon parsePolygon(const std::string& line) {
    std::istringstream iss(line);
    int numVertices;
    if (!(iss >> numVertices) || numVertices < 3) return {};

    Polygon poly;
    std::string token;
    for (int i = 0; i < numVertices; ++i) {
        if (!(iss >> token) || token.size() < 3 || token.front() != '(' || token.back() != ')')
            return {};

        token = token.substr(1, token.size() - 2);
        std::replace(token.begin(), token.end(), ';', ' ');
        std::istringstream pss(token);
        Point p;
        if (!(pss >> p.x >> p.y)) return {};
        poly.points.push_back(p);
    }
    return poly.points.size() == static_cast<size_t>(numVertices) ? poly : Polygon{};
}

std::vector<Polygon> readPolygons(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Polygon> polygons;
    std::string line;
    while (std::getline(file, line)) {
        Polygon poly = parsePolygon(line);
        if (!poly.points.empty()) polygons.push_back(poly);
    }
    return polygons;
}

auto min_max_x = std::minmax_element(all_points.begin(), all_points.end(),
    [](const Point& a, const Point& b) { return a.x < b.x; });
auto min_x = min_max_x.first;
auto max_x = min_max_x.second;

auto min_max_y = std::minmax_element(all_points.begin(), all_points.end(),
    [](const Point& a, const Point& b) { return a.y < b.y; });
auto min_y = min_max_y.first;
auto max_y = min_max_y.second;
