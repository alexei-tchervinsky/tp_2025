#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>
#include <string>
#include <functional>
#include <algorithm>

struct Point
{
    int x, y;
    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }
};

struct Polygon
{
    std::vector<Point> points;
    bool hasRightAngle() const;
};

double calculateArea(const Polygon& polygon);
std::vector<Polygon> readPolygonsFromFile(const std::string& filename);
void processCommands(std::vector<Polygon>& polygons);

void areaCommand(const std::vector<Polygon>& polygons, const std::string& arg);
void maxCommand(const std::vector<Polygon>& polygons, const std::string& arg);
void minCommand(const std::vector<Polygon>& polygons, const std::string& arg);
void countCommand(const std::vector<Polygon>& polygons, const std::string& arg);
void inframeCommand(std::vector<Polygon>& polygons, const std::string& arg);
void intersectionsCommand(const std::vector<Polygon>& polygons, const std::string& arg);
void rightShapesCommand(const std::vector<Polygon>& polygons);

bool isPolygonValid(const Polygon& poly);
bool doPolygonsIntersect(const Polygon& a, const Polygon& b);

#endif
