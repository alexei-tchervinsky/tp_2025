#ifndef COMMANDS_H
#define COMMANDS_H

#include "geometry.h"
#include <vector>

// Existing functions
size_t handleEcho(std::vector<Polygon>& polygons, const Polygon& target);
bool handleInFrame(const std::vector<Polygon>& polygons, const Polygon& target);

// New functions for COUNT commands
size_t countPolygonsByVertices(const std::vector<Polygon>& polygons, int vertices);
size_t countEvenPolygons(const std::vector<Polygon>& polygons);
size_t countOddPolygons(const std::vector<Polygon>& polygons);

// New functions for AREA commands
double calculateArea(const Polygon& polygon);
double calculateAreaByVertices(const std::vector<Polygon>& polygons, int vertices);
double calculateEvenArea(const std::vector<Polygon>& polygons);
double calculateOddArea(const std::vector<Polygon>& polygons);
double calculateMeanArea(const std::vector<Polygon>& polygons);

// New functions for MAX commands
double getMaxArea(const std::vector<Polygon>& polygons);
int getMaxVertices(const std::vector<Polygon>& polygons);

#endif
