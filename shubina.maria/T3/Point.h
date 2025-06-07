// Point.h
#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point {
    int x;
    int y;
};

bool operator==(const Point& a, const Point& b);
std::istream& operator>>(std::istream& in, Point& p);

#endif // POINT_H

