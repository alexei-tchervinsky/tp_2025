#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <istream>
#include <vector>
#include <cmath>
#include <cstddef>

namespace shubina {

    struct Point {
        int x = 0;
        int y = 0;

        Point() = default;
        Point(int x_, int y_) : x(x_), y(y_) {}

        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };

    struct Polygon {
        std::vector<Point> points;

        bool operator==(const Polygon& other) const {
            return points == other.points;
        }

        double area() const;
    };

    struct Delim {
        char expected = '\0';
    };

    std::istream& operator>>(std::istream& is, const Delim& dest);

    std::istream& operator>>(std::istream& is, Point& dest);

    std::istream& operator>>(std::istream& is, Polygon& dest);

}

#endif //DATASTRUCT_H

