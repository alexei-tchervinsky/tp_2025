#include "polygon.h"
#include "iofmtguard.h"
#include <algorithm>
#include <numeric>
#include <cmath>

double Polygon::area() const {
    if (points.size() < 3) return 0.0;
    double sum = 0.0;
    for (size_t i = 0; i < points.size(); ++i) {
        const auto& a = points[i];
        const auto& b = points[(i + 1) % points.size()];
        sum += a.x * b.y - b.x * a.y;
    }
    return std::abs(sum) / 2.0;
}

bool Polygon::hasRightAngle() const {
    if (points.size() < 3) return false;
    for (size_t i = 0; i < points.size(); ++i) {
        const auto& a = points[i];
        const auto& b = points[(i + 1) % points.size()];
        const auto& c = points[(i + 2) % points.size()];
        int dx1 = b.x - a.x, dy1 = b.y - a.y;
        int dx2 = c.x - b.x, dy2 = c.y - b.y;
        if (dx1 * dx2 + dy1 * dy2 == 0) return true;
    }
    return false;
}

bool Polygon::isPermutation(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    auto a = points;
    auto b = other.points;
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    return a == b;
}

size_t Polygon::vertexCount() const {
    return points.size();
}

std::istream& operator>>(std::istream& in, Polygon& poly) {
    koshelev::iofmtguard guard(in);
    size_t n;
    if (in >> n && n >= 3) {
        poly.points.resize(n);
        for (auto& p : poly.points) {
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
    out << poly.vertexCount();
    for (auto& p : poly.points) {
        out << ' ' << p;
    }
    return out;
}
