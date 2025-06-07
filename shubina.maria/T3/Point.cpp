// Point.cpp
#include "Point.h"
#include <iostream>

bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

std::istream& operator>>(std::istream& in, Point& p) {
    char ch;
    if (!(in >> ch) || ch != '(') {
        in.setstate(std::ios_base::failbit);
        return in;
    }
    if (!(in >> p.x >> ch >> p.y >> ch) || ch != ')') {
        in.setstate(std::ios_base::failbit);
    }
    return in;
}

