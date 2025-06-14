#include "Structs.hpp"

namespace vlad {

bool Point::operator<(const Point &other) const {
    if (x != other.x) {
        return x < other.x;
    }
    return y < other.y;
};

bool Point::operator==(const Point &other) const {
    return x == other.x && y == other.y;
}

bool Polygon::operator==(const Polygon& other) const {
    return points == other.points;
}

std::istream& operator>>(std::istream& in, Point& p) {
    const std::istream::sentry sentry(in);
    if (!sentry) return in;

    char dummy;
    in >> dummy >> p.x >> dummy >> p.y >> dummy;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
    const std::ostream::sentry sentry(out);
    if (!sentry) return out;

    out << "(" << p.x << ";" << p.y << ")";
    return out;
}

}

