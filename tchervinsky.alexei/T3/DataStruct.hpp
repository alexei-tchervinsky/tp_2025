#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <vector>
#include <iostream>
#if 1
#include "settings.hpp"
#endif

namespace nspace
{
    struct Point
    {
        int x, y;
        bool operator==(const Point &other) const;
    };

    struct Polygon
    {
        std::vector<Point> points;
        bool operator==(const Polygon &other) const;
        double area() const;
    };

    std::istream& operator>>(std::istream& in, Point& point);
    std::istream& operator>>(std::istream& in, Polygon& poly);
    std::ostream& operator<<(std::ostream& out, const Point& point);
    std::ostream& operator<<(std::ostream& out, const Polygon& poly);

    struct AreaComparator
    {
        bool operator()(const Polygon& a, const Polygon& b) const;
    };

    struct VertexCountComparator
    {
        bool operator()(const Polygon& a, const Polygon& b) const;
    };
}

#endif
