#ifndef POLYGON_OPERATIONS_H
#define POLYGON_OPERATIONS_H
#include "geometry.h"
#include <vector>
#include <sstream>
Polygon parsePolygon(const std::string& input) {
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
double calculateArea(const Polygon& poly);
bool isPolygonInFrame(const Polygon& poly, const std::vector<Polygon>& polygons);
bool doPolygonsIntersect(const Polygon& a, const Polygon& b);
#endif // POLYGON_OPERATIONS_H
