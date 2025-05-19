#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP
#include <iostream>
#include <vector>

namespace tarasov {
    struct Point {
        int x,y;

        bool operator<(const Point &other) const;

        bool operator==(const Point &other) const;
    };

    struct Polygon {
        std::vector <Point> points{};
    };

    std::istream& operator>>(std::istream& in, Point& p);

    std::ostream& operator<<(std::ostream& out, const Point& p);
}

#endif //STRUCTURES_HPP
