#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <map>

namespace ilyaerofick {

struct Point {
    int x;
    int y;
};

struct Polygon {
    std::vector<Point> points;
};

double getArea(const Polygon& polygon);
Polygon getFrame(const std::vector<Polygon>& polygons);
bool isInside(const Polygon& poly, const Polygon& frame);
bool hasRightAngle(const Polygon& poly);

std::istream& operator>>(std::istream& in, Point& point);
bool operator==(const Point& lhs, const Point& rhs);
std::istream& operator>>(std::istream& in, Polygon& polygon);
bool operator==(const Polygon& lhs, const Polygon& rhs);

void areaCommand(const std::vector<Polygon>& polygons,
                std::istream& in, std::ostream& out);
void maxCommand(const std::vector<Polygon>& polygons,
               std::istream& in, std::ostream& out);
void minCommand(const std::vector<Polygon>& polygons,
               std::istream& in, std::ostream& out);
void countCommand(const std::vector<Polygon>& polygons,
                 std::istream& in, std::ostream& out);
void rmEchoCommand(std::vector<Polygon>& polygons,
                  std::istream& in, std::ostream& out);
void inframeCommand(const std::vector<Polygon>& polygons,
                   std::istream& in, std::ostream& out);
void rightshapesCommand(const std::vector<Polygon>& polygons,
                       std::ostream& out);

}
#endif
