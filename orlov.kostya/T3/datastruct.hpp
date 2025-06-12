#ifndef DATASTRUCTS_HPP
#define DATASTRUCTS_HPP

#include <vector>
#include <iostream>

namespace orlov
{
    struct Point
    {
        int x_;
        int y_;

        bool operator==(const Point&) const;
        friend std::istream& operator>>(std::istream& is, Point& src);
    };

    struct Polygon
    {
        std::vector<Point> points;

        double getArea() const;
        bool isInsideFrame(const Point leftBottom, const Point rightTop) const;

        bool operator==(const Polygon& other) const;
        friend std::istream& operator>>(std::istream& is, Polygon& src);
    };
}

#endif // !__DATASTRUCTS_HPP

