// Polygon.cpp
#include "Polygon.h"
#include <iostream>

std::istream& operator>>(std::istream& in, Polygon& poly) {
    int n = 0;
    if (!(in >> n)) {
        return in;
    }

    if (n < 3) {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    poly.points.clear();
    for (int i = 0; i < n; ++i) {
        Point p;
        if (!(in >> p)) {
            in.setstate(std::ios_base::failbit);
            return in;
        }
        poly.points.push_back(p);
    }

    return in;
}

