#ifndef FILE_IO_H
#define FILE_IO_H
#include "geometry.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
std::vector<Polygon> readPolygonsFromFile(const std::string& filename);
inline Polygon parsePolygon(const std::string& input) {
    std::istringstream iss(input);
    int vertexCount;
    iss >> vertexCount;
    Polygon poly;
    for (int i = 0; i < vertexCount; ++i) {
        char c1, c2, c3;
        int x, y;
        iss >> c1 >> x >> c2 >> y >> c3;
        poly.points.push_back({x, y});
    }
    return poly;
}
#endif // FILE_IO_H
