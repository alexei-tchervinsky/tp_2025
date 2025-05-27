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

    // Check if there are more tokens than expected
    std::string extraToken;
    if (iss >> extraToken) {
        return {}; // More tokens than expected, invalid polygon
    }

    return poly.points.size() == static_cast<size_t>(numVertices) ? poly : Polygon{};
}

std::vector<Polygon> readPolygons(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return {};

    std::vector<Polygon> polygons;
    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        Polygon poly = parsePolygon(line);
        if (!poly.points.empty()) polygons.push_back(poly);
    }
    return polygons;
}

