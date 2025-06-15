#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <compare>

struct Point {
    int x, y;
    auto operator<=>(const Point&) const = default;
    bool operator==(const Point&) const = default;
};

std::istream& operator>>(std::istream& in, Point& p);
std::ostream& operator<<(std::ostream& out, const Point& p);

#endif

