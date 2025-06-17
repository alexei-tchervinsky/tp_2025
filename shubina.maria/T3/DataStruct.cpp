#include "DataStruct.h"
#include <cmath>

namespace shubina {

    std::istream& operator>>(std::istream& is, const Delim& dest) {
        char c = '\0';
        is >> c;
        if (c != dest.expected) {
            is.setstate(std::ios_base::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, Point& dest) {
        char lpar, sep, rpar;
        int x = 0, y = 0;

        is >> lpar >> x >> sep >> y >> rpar;

        if (!is || lpar != '(' || sep != ';' || rpar != ')') {
            is.setstate(std::ios_base::failbit);
            return is;
        }

        dest.x = x;
        dest.y = y;
        return is;
    }

    std::istream& operator>>(std::istream& is, Polygon& dest) {
        size_t n = 0;
        is >> n;

        if (n < 3) {
            is.setstate(std::ios_base::failbit);
            return is;
        }

        dest.points.clear();
        dest.points.reserve(n);

        for (size_t i = 0; i < n; ++i) {
            Point p;
            if (!(is >> p)) {
                dest.points.clear();
                break;
            }
            dest.points.push_back(p);
        }

        if (dest.points.size() < 3) {
            is.setstate(std::ios_base::failbit);
        }

        return is;
    }

    double Polygon::area() const {
        if (points.size() < 3) {
            return 0.0;
        }

        double sum = 0.0;
        size_t n = points.size();

        for (size_t i = 0; i < n; ++i) {
            const Point& p1 = points[i];
            const Point& p2 = points[(i + 1) % n];
            sum += static_cast<double>(p1.x) * p2.y - static_cast<double>(p2.x) * p1.y;
        }

        return std::abs(sum) / 2.0;
    }

}

