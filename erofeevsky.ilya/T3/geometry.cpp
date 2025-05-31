#include "geometry.hpp"
#include "iofmtguard.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <limits>
#include <iomanip>
#include <functional>

namespace ilyaerofick {

double getArea(const Polygon& polygon) {
    double area = 0.0;
    for (size_t i = 0; i < polygon.points.size(); ++i) {
        const Point& p1 = polygon.points[i];
        const Point& p2 = polygon.points[(i + 1) % polygon.points.size()];
        area += (p1.x * p2.y) - (p2.x * p1.y);
    }
    return std::abs(area) / 2.0;
}

Polygon getFrame(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) return Polygon{};

    auto compareX = [](const Point& a, const Point& b) { return a.x < b.x; };
    auto compareY = [](const Point& a, const Point& b) { return a.y < b.y; };

    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int minY = std::numeric_limits<int>::max();
    int maxY = std::numeric_limits<int>::min();

    for (const auto& poly : polygons) {
        const auto [minXIt, maxXIt] = std::minmax_element(
            poly.points.begin(), poly.points.end(), compareX);
        const auto [minYIt, maxYIt] = std::minmax_element(
            poly.points.begin(), poly.points.end(), compareY);

        minX = std::min(minX, minXIt->x);
        maxX = std::max(maxX, maxXIt->x);
        minY = std::min(minY, minYIt->y);
        maxY = std::max(maxY, maxYIt->y);
    }

    Polygon frame;
    frame.points.push_back({minX, minY});
    frame.points.push_back({minX, maxY});
    frame.points.push_back({maxX, maxY});
    frame.points.push_back({maxX, minY});
    return frame;
}

bool isInside(const Polygon& poly, const Polygon& frame) {
    if (frame.points.size() != 4) return false;

    const int minX = frame.points[0].x;
    const int minY = frame.points[0].y;
    const int maxX = frame.points[2].x;
    const int maxY = frame.points[2].y;

    return std::all_of(poly.points.begin(), poly.points.end(),
        [minX, maxX, minY, maxY](const Point& p) {
            return p.x >= minX && p.x <= maxX && p.y >= minY && p.y <= maxY;
        });
}

bool hasRightAngle(const Polygon& poly) {
    if (poly.points.size() < 3) return false;

    for (size_t i = 0; i < poly.points.size(); ++i) {
        const Point& a = poly.points[i];
        const Point& b = poly.points[(i + 1) % poly.points.size()];
        const Point& c = poly.points[(i + 2) % poly.points.size()];

        int dx1 = b.x - a.x;
        int dy1 = b.y - a.y;
        int dx2 = c.x - b.x;
        int dy2 = c.y - b.y;

        if (dx1 * dx2 + dy1 * dy2 == 0) return true;
    }
    return false;
}

std::istream& operator>>(std::istream& in, Point& point) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    Point temp{0, 0};
    char ch;
    in >> ch >> temp.x >> ch >> temp.y >> ch;
    if (ch == ')' && in) point = temp;
    else in.setstate(std::ios::failbit);
    return in;
}

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::istream& operator>>(std::istream& in, Polygon& polygon) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    size_t count = 0;
    in >> count;
    if (count < 3) {
        in.setstate(std::ios::failbit);
        return in;
    }
    std::vector<Point> temp;
    temp.reserve(count);
    for (size_t i = 0; i < count; ++i) {
        Point p;
        in >> p;
        if (!in) return in;
        temp.push_back(p);
    }
    polygon.points = temp;
    return in;
}

bool operator==(const Polygon& lhs, const Polygon& rhs) {
    if (lhs.points.size() != rhs.points.size()) return false;
    return std::equal(lhs.points.begin(), lhs.points.end(), rhs.points.begin());
}

void areaCommand(const std::vector<Polygon>& polygons,
                std::istream& in, std::ostream& out) {
    IOFmtGuard guard(out);
    out << std::fixed << std::setprecision(1);

    std::string arg;
    in >> arg;

    std::function<bool(const Polygon&)> condition;

    if (arg == "EVEN") {
        condition = [](const Polygon& p) { return p.points.size() % 2 == 0; };
    } else if (arg == "ODD") {
        condition = [](const Polygon& p) { return p.points.size() % 2 != 0; };
    } else if (arg == "MEAN") {
        if (polygons.empty()) throw std::invalid_argument("No polygons");
        double total = 0.0;
        for (const auto& p : polygons) {
            total += getArea(p);
        }
        out << total / polygons.size();
        return;
    } else {
        size_t num = std::stoul(arg);
        if (num < 3) throw std::invalid_argument("Invalid vertex count");
        condition = [num](const Polygon& p) { return p.points.size() == num; };
    }

    double total = 0.0;
    for (const auto& p : polygons) {
        if (condition(p)) {
            total += getArea(p);
        }
    }
    out << total;
}

void maxCommand(const std::vector<Polygon>& polygons,
               std::istream& in, std::ostream& out) {
    if (polygons.empty()) throw std::invalid_argument("No polygons");

    std::string arg;
    in >> arg;

    IOFmtGuard guard(out);
    out << std::fixed << std::setprecision(1);

    if (arg == "AREA") {
        double maxArea = getArea(polygons[0]);
        for (const auto& p : polygons) {
            double area = getArea(p);
            if (area > maxArea) maxArea = area;
        }
        out << maxArea;
    } else if (arg == "VERTEXES") {
        size_t maxVerts = polygons[0].points.size();
        for (const auto& p : polygons) {
            if (p.points.size() > maxVerts) maxVerts = p.points.size();
        }
        out << maxVerts;
    } else {
        throw std::invalid_argument("Invalid argument");
    }
}

void minCommand(const std::vector<Polygon>& polygons,
               std::istream& in, std::ostream& out) {
    if (polygons.empty()) throw std::invalid_argument("No polygons");

    std::string arg;
    in >> arg;

    IOFmtGuard guard(out);
    out << std::fixed << std::setprecision(1);

    if (arg == "AREA") {
        double minArea = getArea(polygons[0]);
        for (const auto& p : polygons) {
            double area = getArea(p);
            if (area < minArea) minArea = area;
        }
        out << minArea;
    } else if (arg == "VERTEXES") {
        size_t minVerts = polygons[0].points.size();
        for (const auto& p : polygons) {
            if (p.points.size() < minVerts) minVerts = p.points.size();
        }
        out << minVerts;
    } else {
        throw std::invalid_argument("Invalid argument");
    }
}

void countCommand(const std::vector<Polygon>& polygons,
                 std::istream& in, std::ostream& out) {
    std::string arg;
    in >> arg;

    size_t count = 0;

    if (arg == "EVEN") {
        for (const auto& p : polygons) {
            if (p.points.size() % 2 == 0) ++count;
        }
    } else if (arg == "ODD") {
        for (const auto& p : polygons) {
            if (p.points.size() % 2 != 0) ++count;
        }
    } else {
        size_t num = std::stoul(arg);
        if (num < 3) throw std::invalid_argument("Invalid vertex count");
        for (const auto& p : polygons) {
            if (p.points.size() == num) ++count;
        }
    }
    out << count;
}

void rmEchoCommand(std::vector<Polygon>& polygons,
                  std::istream& in, std::ostream& out) {
    Polygon target;
    in >> target;
    if (!in) throw std::invalid_argument("Invalid polygon");

    size_t removed = 0;
    auto it = polygons.begin();
    while (it != polygons.end()) {
        if (*it == target && it + 1 != polygons.end() && *(it + 1) == target) {
            it = polygons.erase(it + 1);
            ++removed;
        } else {
            ++it;
        }
    }
    out << removed;
}

void inframeCommand(const std::vector<Polygon>& polygons,
                   std::istream& in, std::ostream& out) {
    Polygon target;
    in >> target;
    if (!in) throw std::invalid_argument("Invalid polygon");

    Polygon frame = getFrame(polygons);
    out << (isInside(target, frame) ? "<TRUE>" : "<FALSE>");
}

void rightshapesCommand(const std::vector<Polygon>& polygons,
                       std::ostream& out) {
    size_t count = 0;
    for (const auto& p : polygons) {
        if (hasRightAngle(p)) ++count;
    }
    out << count;
}

}