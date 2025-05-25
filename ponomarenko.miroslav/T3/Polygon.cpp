#include "Polygon.hpp"
#include <cmath>
#include <algorithm>
#include <iterator>
#include <numeric>

namespace ponomarenko {

    bool Point::operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool Point::operator<(const Point& other) const {
        if (x != other.x) {
            return x < other.x;
        }

        return y < other.y;
    }

    std::istream& operator>>(std::istream& in, Point& point) {
        std::istream::sentry guard(in);
        if (!guard) {
            return in;
        }

        char open = 0, sep = 0, close = 0;
        int x = 0, y = 0;
        in >> open >> x >> sep >> y >> close;

        if (!in || open != '(' || sep != ';' || close != ')') {
            in.setstate(std::ios::failbit);
            return in;
        }

        point = Point{x, y};
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const Point& point) {
        std::ostream::sentry guard(out);
        if (!guard) {
            return out;
        }

        out << "(" << point.x << ";" << point.y << ")";
        return out;
    }

    std::istream& operator>>(std::istream& in, Polygon& polygon) {
        std::istream::sentry guard(in);
        if (!guard) {
            return in;
        }
        size_t count = 0;
        in >> count;
        if (!in || count < 3) {
            in.setstate(std::ios::failbit);
            return in;
        }

        std::vector<Point> temp;
        std::copy_n(std::istream_iterator<Point>(in), count, std::back_inserter(temp));

        if (temp.size() != count || !in) {
            in.setstate(std::ios::failbit);
            return in;
        }

        polygon.points = std::move(temp);
        return in;
    }

    bool Polygon::operator==(const Polygon& other) const {
        return points == other.points;
    }

    double getArea(const Polygon& polygon) {
        const std::vector<Point>& pts = polygon.points;
        const size_t n = pts.size();
        if (n < 3) {
            return 0.0;
        }

        std::pair<double, size_t> result = std::accumulate(
            pts.begin(), pts.end(), std::pair<double, size_t>{0.0, 0},
                [&pts](std::pair<double, size_t> acc, const Point& p1) {
                    const Point& p2 = pts[(acc.second + 1) % pts.size()];
                    acc.first += static_cast<double>(p1.x * p2.y - p2.x * p1.y);
                    ++acc.second;
                    return acc;
                }
        );
        return std::abs(result.first) / 2.0;
    }

    bool hasRightAngle(const Polygon& polygon) {
        const std::vector<Point>& pts = polygon.points;
        const size_t n = pts.size();
        if (n < 3) {
            return false;
        }
        struct Triple {
            Point a, b;
            bool found;
        };

        auto result = std::accumulate(
            pts.begin(), pts.end(), Triple{pts[n - 2], pts[n - 1], false},
            [](Triple acc, const Point& c) -> Triple {
                if (acc.found) return acc;
                const Point& a = acc.a;
                const Point& b = acc.b;
                int abx = b.x - a.x;
                int aby = b.y - a.y;
                int cbx = b.x - c.x;
                int cby = b.y - c.y;
                bool isRight = (abx * cbx + aby * cby == 0);
                return Triple{b, c, acc.found || isRight};
            }
        );
        return result.found;
    }
}
