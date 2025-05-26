#ifndef POLYGON_OPERATIONS_H
#define POLYGON_OPERATIONS_H
#include "geometry.h"
#include <vector>
double calculateArea(const Polygon& poly);
bool isPolygonInFrame(const Polygon& poly, const std::vector<Polygon>& polygons);
bool doPolygonsIntersect(const Polygon& a, const Polygon& b);
#endif // POLYGON_OPERATIONS_H
