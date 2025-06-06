#ifndef FILE_IO_H
#define FILE_IO_H
#include "geometry.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
std::vector<Polygon> readPolygonsFromFile(const std::string& filename);
inline Polygon parsePolygon(const std::string& input) {
    std::istringstream iss(input);
    int vertexCount;
    if (!(iss >> vertexCount) || vertexCount < 3) {
        throw std::invalid_argument("Invalid number of vertices");
    }
    Polygon poly;
    for (int i = 0; i < vertexCount; ++i) {
        char c1, c2, c3;
        int x, y;
        if (!(iss >> c1 >> x >> c2 >> y >> c3) || c1 != '(' || c2 != ';' || c3 != ')') {
            throw std::invalid_argument("Invalid point format");
        }
        if (i > 0 && x == poly.points.back().x && y == poly.points.back().y) {
            throw std::invalid_argument("Duplicate points");
        }
        poly.points.push_back({x, y});
    }
    if (poly.points.size() != static_cast<size_t>(vertexCount)) {
        throw std::invalid_argument("Vertex count mismatch");
    }
    return poly;
}
#endif // FILE_IO_H
