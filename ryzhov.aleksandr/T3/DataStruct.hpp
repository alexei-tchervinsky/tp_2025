//
// Created by jdh99 on 01.05.2025.
//

#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <istream>
#include <vector>

namespace ryzhov {
    struct Point {
        int x, y;
        Point(int x = 0, int y = 0) : x(x), y(y) {}
        bool operator==(const Point &other) const;
    };

    struct Polygon {
        std::vector<Point> points;
        bool operator==(const Polygon &other) const;
        double area() const;
        bool isRectangle() const;
        bool isInsideFrame(Point, Point) const;
    };

    struct Delim {
        char delim = 0;
    };
    std::istream& operator>>(std::istream& is, const Delim& dest);
    std::istream& operator>>(std::istream& is, Point& dest);
    std::istream& operator>>(std::istream& is, Polygon& dest);
    bool isSame(const Polygon& first, const Polygon& second);
}
#endif //DATASTRUCT_HPP
