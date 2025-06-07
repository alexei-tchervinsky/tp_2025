#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>


struct Point
{
    int x, y;
    Point(){}
    Point(int xx, int yy) : x(xx), y(yy) {}
};

struct Polygon
{
    std::vector<Point> points;
};

struct DelimiterChar
{
    char expected;
};

std::istream & operator>>(std::istream& in, DelimiterChar&& exp);
std::istream& operator>>(std::istream& in, Polygon& polygon);
std::istream& operator>>(std::istream& in, Point& point);
std::ostream& operator<<(std::ostream& out, const Polygon& poly);
std::ostream& operator<<(std::ostream& out, const Point& p);

bool isRectangle(const Polygon& polygon);
void Rects(const std::vector<Polygon>& polygons);
std::size_t countIntersections(const std::vector<Polygon>& polygons, const Polygon& target);

#endif
