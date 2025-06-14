#ifndef KUZMINYKH_GEOMETRY_H
#define KUZMINYKH_GEOMETRY_H

#include <vector>
#include <iostream>

namespace kuzminykh
{
    struct Point
    {
        int x;
        int y;

        bool operator<(const Point& other) const;
        bool operator==(const Point& other) const;
    };

    struct Polygon
    {
        std::vector<Point> points;
    };

    std::istream& operator>>(std::istream& in, Point& p);
    std::ostream& operator<<(std::ostream& out, const Point& p);
    kuzminykh::Polygon parsePolygon(const std::string& str);
    std::vector<kuzminykh::Polygon> readFile(const std::string& fileName);
}
#endif
