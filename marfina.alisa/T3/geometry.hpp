#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <vector>
#include <string>
#include <functional>

struct Point
{
    int x, y;
};

struct Polygon
{
    std::vector<Point> points;
};

bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);
double calculateArea(const Polygon& polygon);
double calculateArea(const std::vector<Polygon>& polygons);
std::vector<Polygon> readPolygonsFromFile(const std::string& filename);
void processCommands(const std::vector<Polygon>& polygons);

void areaCommand(const std::vector<Polygon>& polygons, const std::string& arg);
void maxCommand(const std::vector<Polygon>& polygons, const std::string& arg);
void minCommand(const std::vector<Polygon>& polygons, const std::string& arg);
void countCommand(const std::vector<Polygon>& polygons, const std::string& arg);
void inframeCommand(const std::vector<Polygon>& polygons, const std::string& arg);
void intersectionsCommand(const std::vector<Polygon>& polygons, const std::string& arg);

#endif
