#include "DataStruct.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>

namespace shubina {

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

    std::string line;
    std::getline(is >> std::ws, line); // Skip leading whitespace
    std::istringstream iss(line);
    iss >> numPoints;

    if (numPoints < 3) {
        is.setstate(std::ios::failbit);
        return is;
    }

    tmp.points.reserve(numPoints);
    for (size_t i = 0; i < numPoints; ++i) {
        Point p;
        if (!(iss >> p)) {
            is.setstate(std::ios::failbit);
            return is;
        }
        tmp.points.push_back(p);
    }


    std::string leftover;
    if (iss >> leftover) {
        is.setstate(std::ios::failbit);
        return is;
    }

    dest = std::move(tmp);
    return is;
}

}

