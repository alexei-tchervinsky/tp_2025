#include "polygon.h"
#include "iofmtguard.h"
#include <algorithm>
#include <numeric>
#include <cmath>

double Polygon::area() const {
    if (points.size() < 3) return 0.0;
    double sum = 0.0;
    for (size_t i = 0; i < points.size(); ++i) {
        const Point& a = points[i];
        const Point& b = points[(i + 1) % points.size()];
        sum += a.x * b.y - b.x * a.y;
    }
    return std::abs(sum) / 2.0;
}

bool Polygon::hasRightAngle() const {
    if (points.size() < 3) return false;
    for (size_t i = 0; i < points.size(); ++i) {
        const Point& A = points[i];
        const Point& B = points[(i + 1) % points.size()];
        const Point& C = points[(i + 2) % points.size()];
        int dx1 = B.x - A.x, dy1 = B.y - A.y;
        int dx2 = C.x - B.x, dy2 = C.y - B.y;
        if (dx1 * dx2 + dy1 * dy2 == 0) return true;
    }
    return false;
}

bool Polygon::isPermutation(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    auto A = points;
    auto B = other.points;
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    return A == B;
}

size_t Polygon::vertexCount() const {
    return points.size();
}

std::istream& operator>>(std::istream& in, Polygon& poly) {
    koshelev::iofmtguard guard(in);
    size_t n;
    if (!(in >> n) || n < 3) {
        in.setstate(std::ios::failbit);
        return in;
    }
    std::vector<Point> tmp;
    tmp.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        Point p;
        if (!(in >> p)) {
            in.setstate(std::ios::failbit);
            return in;
        }
        tmp.push_back(p);
    }
    poly.points = std::move(tmp);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Polygon& poly) {
    koshelev::iofmtguard guard(out);
    out << poly.vertexCount();
    for (auto& p : poly.points) {
        out << ' ' << p;
    }
    return out;
}
