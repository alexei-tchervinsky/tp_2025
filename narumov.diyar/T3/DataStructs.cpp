#include <cmath>
#include <algorithm>
#include <iterator>

#include "DataStructs.hpp"
#include "IO_Objects.hpp"

namespace narumov {
    bool Point::operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    std::istream& operator>>(std::istream& is, Point& ds) {
        std::istream::sentry sentry(is);
        if(!sentry) {
            return is;
        }
        Point temp;
        is >> LimitingSymbolIO { '(' };
        is >> temp.x >> LimitingSymbolIO { ';' } >> temp.y;
        is >> LimitingSymbolIO { ')' };
        if(is) {
            ds = temp;
        }
        return is;
    }

    double Polygon::getArea() const {
        if(points.size() < 3) {
            return 0.0;
        }
        double area = 0.0;
        for(std::size_t i = 0; i < points.size(); ++i) {
            std::size_t j = (i + 1) % points.size();
            area += (points[i].x * points[j].y - points[j].x * points[i].y);
        }
        return std::abs(area) / 2.0;
    }

    bool Polygon::isInsideFrame(const Point leftBottom, const Point rightTop) const {
        return std::all_of(points.begin(), points.end(), [&](const Point& p) {
            return p.x >= leftBottom.x && p.x <= rightTop.x && p.y >= leftBottom.y && p.y <= rightTop.y;
        });
    }

    bool Polygon::operator==(const Polygon& other) const {
        return points == other.points;
    }

    std::istream& operator>>(std::istream& is, Polygon& ds) {
        std::istream::sentry sentry(is);
        if(!sentry) {
            return is;
        }
        std::size_t count = 0;
        is >> count;
        std::string line;
        std::getline(is, line);
        std::istringstream iss(line);
        Polygon temp;
        std::copy(
            std::istream_iterator<Point>(iss),
            std::istream_iterator<Point>(),
            std::back_inserter(temp.points)
        );
        if(count < 3 || temp.points.size() != count) {
            is.setstate(std::ios::failbit);
            return is;
        }
        if(is) {
            ds = temp;
        }
        return is;
    }
}
