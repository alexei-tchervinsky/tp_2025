#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace ponomarenko {

    struct Point {
        int x;
        int y;

        bool operator==(const Point& other) const;
        bool operator<(const Point& other) const;
    };

    struct Polygon {
        std::vector<Point> points;
        bool operator==(const Polygon& other) const;
    };

    std::istream& operator>>(std::istream& in, Point& point);
    std::istream& operator>>(std::istream& in, Polygon& polygon);
    double getArea(const Polygon& polygon);
    bool hasRightAngle(const Polygon& polygon);

}

#endif
