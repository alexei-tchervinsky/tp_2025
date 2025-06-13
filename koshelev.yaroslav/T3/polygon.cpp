#include "polygon.h"
#include "iofmtguard.h"
#include <algorithm>
#include <numeric>
#include <cmath>

double Polygon::area() const {
    if (points.size() < 3) return 0.0;
    double sum = 0.0;
    for (size_t i = 0; i < points.size(); ++i) {
        const Point& curr = points[i];
        const Point& next = points[(i + 1) % points.size()];
        sum += (curr.x * next.y) - (next.x * curr.y);
    }
    return std::abs(sum) / 2.0;
}

bool Polygon::hasRightAngle() const {
    if (points.size() < 3) return false;
    for (size_t i = 0; i < points.size(); ++i) {
        const Point& a = points[i];
        const Point& b = points[(i + 1) % points.size()];
        const Point& c = points[(i + 2) % points.size()];
        int dx1 = b.x - a.x, dy1 = b.y - a.y;
        int dx2 = c.x - b.x, dy2 = c.y - b.y;
        if (dx1 * dx2 + dy1 * dy2 == 0) return true;
    }
    return false;
}

bool Polygon::isPermutation(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    std::vector<Point> this_sorted = points;
    std::vector<Point> other_sorted = other.points;
    std::sort(this_sorted.begin(), this_sorted.end());
    std::sort(other_sorted.begin(), other_sorted.end());
    return this_sorted == other_sorted;
}

size_t Polygon::vertexCount() const {
    return points.size();
}

std::istream& operator>>(std::istream& in, Polygon& poly) {
    koshelev::iofmtguard guard(in);
    size_t num;
    if (in >> num && num >= 3) {
        poly.points.resize(num);
        for (Point& p : poly.points) {
            if (!(in >> p)) {
                poly.points.clear();
                break;
            }
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Polygon& poly) {
    koshelev::iofmtguard guard(out);
    out << poly.vertexCount() << ' ';
    for (const Point& p : poly.points) {
        out << p << ' ';
    }
    return out;
}