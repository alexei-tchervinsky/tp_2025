#ifndef T3_1_STRUCT_H
#define T3_1_STRUCT_H
#include <iostream>
#include <vector>

namespace wheatman
{
    struct Point
    {
        int x, y;

        bool operator < (const Point &other) const;
        bool operator == (const Point &other) const;

    };
    struct Polygon
    {
        std::vector<Point> points;
    };

    std::istream& operator >> (std::istream& in, Point& p);
    std::ostream& operator << (std::ostream& out, const Point& p);

}
#endif //T3_1_STRUCT_H
