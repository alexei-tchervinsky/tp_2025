//
// Created by jdh99 on 01.05.2025.
//

#include "DataStruct.hpp"
#include <algorithm>

namespace likhodievskii {
    bool Point::operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    bool Polygon::operator==(const Polygon &other) const {
        return points == other.points;
    }

    double Polygon::area() const {
        double sum = 0.0;
        for (size_t i = 0; i < points.size(); ++i) {
            const Point &p1 = points[i];
            const Point &p2 = points[(i + 1) % points.size()];
            sum += (p1.x * p2.y) - (p1.y * p2.x);
        }
        return std::abs(sum) / 2.0;
    }

    bool Polygon::isRectangle() const {
        if (points.size() != 4) return false;

        auto isRightAngle = [](Point a, Point b, Point c) {
            int dx1 = b.x - a.x, dy1 = b.y - a.y;
            int dx2 = b.x - c.x, dy2 = b.y - c.y;
            return (dx1 * dx2 + dy1 * dy2) == 0;
        };

        return isRightAngle(points[0], points[1], points[2]) &&
               isRightAngle(points[1], points[2], points[3]) &&
               isRightAngle(points[2], points[3], points[0]);
    }

    bool isSame(const Polygon &poly1, const Polygon &poly2) {
        if (poly1.points.size() != poly2.points.size()) {
            return false;
        }

        auto sortedPoints1 = poly1.points;
        auto sortedPoints2 = poly2.points;

        auto pointComparator = [](const Point &a, const Point &b) {
            return (a.x < b.x) || (a.x == b.x && a.y < b.y);
        };

        std::sort(sortedPoints1.begin(), sortedPoints1.end(), pointComparator);
        std::sort(sortedPoints2.begin(), sortedPoints2.end(), pointComparator);

        return sortedPoints1 == sortedPoints2;
    }

    std::istream &operator>>(std::istream &is, const Delim &dest) {
        std::istream::sentry sentry(is);
        if (!sentry) {
            return is;
        }
        char c = 0;
        is.get(c);
        if (is && (c != dest.delim)) {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream &operator>>(std::istream &is, Point &dest) {
        std::istream::sentry sentry(is);
        if (!sentry) {
            return is;
        }
        Point tmp{};
        is >> Delim{'('};
        is >> tmp.x;
        is >> Delim{';'};
        is >> tmp.y;
        is >> Delim{')'};
        if (is) {
            dest = tmp;
        }
        return is;
    }

    std::istream &operator>>(std::istream &is, Polygon &dest) {
        std::istream::sentry sentry(is);
        if (!sentry) {
            return is;
        }

        size_t numPoints = 0;
        is >> numPoints;
        if (numPoints < 3) {
            is.setstate(std::ios::failbit);
            return is;
        }

        dest.points.clear();
        dest.points.reserve(numPoints);

        for (size_t i = 0; i < numPoints; ++i) {
            Point p;
            if (!(is >> p)) {
                is.setstate(std::ios::failbit);
                break;
            }
            dest.points.push_back(p);
        }

        return is;
    }
}
