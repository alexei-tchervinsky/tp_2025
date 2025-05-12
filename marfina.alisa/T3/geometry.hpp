#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <iosfwd>

struct Point
{
    int x, y;
};
struct Polygon
{
    std::vector<Point> points;
};
struct BoundingBox
{
    Point min;
    Point max;
};

struct AreaComparator
{
    bool operator()(const Polygon& a, const Polygon& b) const;
};

struct VertexCountComparator
{
    bool operator()(const Polygon& a, const Polygon& b) const;
};
double calculateArea(const Polygon& polygon);
double calculateArea(const std::vector<Polygon>& polygons);
BoundingBox calculateBoundingBox(const std::vector<Polygon>& polygons);
bool isPointInBoundingBox(const Point& p, const BoundingBox& box);
void areaCommand(const std::vector<Polygon>& polygons, const std::string& arg);
void maxMinCommand(const std::vector<Polygon>& polygons, const std::string& type, const std::string& arg);
void countCommand(const std::vector<Polygon>& polygons, const std::string& arg);
void inframeCommand(const std::vector<Polygon>& polygons, const std::string& arg);
void intersectionsCommand(const std::vector<Polygon>& polygons, const std::string& arg);
void echoCommand(std::vector<Polygon>& polygons, const std::string& arg);
void processCommands(std::vector<Polygon>& polygons);
std::vector<Polygon> readPolygonsFromFile(const std::string& filename);
bool parsePolygon(const std::string& str, Polygon& out);

#endif
