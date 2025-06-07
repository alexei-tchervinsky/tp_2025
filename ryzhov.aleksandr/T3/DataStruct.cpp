//
// Created by jdh99 on 01.05.2025.
//

#include "DataStruct.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>


namespace ryzhov {
    bool Point::operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    bool Polygon::operator==(const Polygon &other) const {
        return points == other.points;
    }

    double Polygon::area() const {
        if (points.size() < 3) {
            return 0.0;
        }

        double sum = std::accumulate(
            points.begin(),
            points.end(),
            0.0,
            [this](double acc, const Point& p1) {
                const Point& p2 = points[(&p1 - &points[0] + 1) % points.size()];
                return acc + (p1.x * p2.y) - (p1.y * p2.x);
            }
        );

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

    bool Polygon::isInsideFrame(const Point leftBottom, const Point rightTop) const {
        return std::all_of(points.begin(), points.end(), [&](const Point& p) {
            return p.x >= leftBottom.x && p.x <= rightTop.x && p.y >= leftBottom.y && p.y <= rightTop.y;
        });
    }

    bool isSame(const Polygon &poly1, const Polygon &poly2) {
        if (poly1.points.size() != poly2.points.size()) {
            return false;
        }
        if (poly1.points.empty()) {
            return true;
        }

        const auto min_point = [](const Polygon &poly) {
            return std::accumulate(
                poly.points.begin(), poly.points.end(),
                poly.points.front(),
                [](const Point &acc, const Point &p) {
                    return Point(
                        std::min(acc.x, p.x),
                        std::min(acc.y, p.y)
                    );
                }
            );
        };

        const Point min1 = min_point(poly1);
        const Point min2 = min_point(poly2);

        return std::inner_product(
            poly1.points.begin(), poly1.points.end(),
            poly2.points.begin(),
            true,
            [](bool acc, bool current) { return acc && current; },
            [&](const Point &p1, const Point &p2) {
                return (p1.x - min1.x) == (p2.x - min2.x) &&
                       (p1.y - min1.y) == (p2.y - min2.y);
            }
        );
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
        Polygon tmp{};
        size_t numPoints = 0;
        dest.points.clear();

        std::string readNow;
        std::getline(is, readNow);
        std::istringstream iss(readNow);
        iss >> numPoints;
        if (numPoints < 3) {
            return is;
        }

        while (!iss.eof()) {
            Point p;
            if (!(iss >> p)) {
                break;
            }
            tmp.points.push_back(p);
        }
        if (tmp.points.size() != numPoints) {
            tmp.points.clear();
            return is;
        }
        dest = std::move(tmp);
        return is;
    }
}
