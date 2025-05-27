#ifndef DATA_STRUCTS_HPP
#define DATA_STRUCTS_HPP

#include <vector>
#include <iostream>

namespace narumov {
    struct Point {
        int x, y;

        bool operator==(const Point&) const;
        friend std::istream& operator>>(std::istream&, Point&);
    };

    struct Polygon {
        std::vector<Point> points;

        double getArea() const;
        bool isInsideFrame(const Point, const Point) const;

        bool operator==(const Polygon&) const;
        friend std::istream& operator>>(std::istream&, Polygon&);
    };
}

#endif
