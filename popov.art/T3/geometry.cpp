#include "geometry.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
namespace popov {
bool doPolygonsIntersect(const Polygon& poly1, const Polygon& poly2) {
    auto getProjections = [](const Polygon& poly, double nx, double ny) {
        double minProj = std::numeric_limits<double>::max();
        double maxProj = -std::numeric_limits<double>::max();
        for (const auto& p : poly.points) {
            double proj = p.x * nx + p.y * ny;
            minProj = std::min(minProj, proj);
            maxProj = std::max(maxProj, proj);
        }
        return std::make_pair(minProj, maxProj);
    };
    auto check_edges = [&](const Polygon& poly, const Polygon& other_poly) {
        return std::all_of(poly.points.begin(), poly.points.end(),
            [&](const Point& p1) {
                size_t next = (&p1 - &poly.points[0] + 1) % poly.points.size();
                const Point& p2 = poly.points[next];
                double nx = -(p2.y - p1.y);
                double ny = p2.x - p1.x;
                auto proj1 = getProjections(poly, nx, ny);
                auto proj2 = getProjections(other_poly, nx, ny);
                return !(proj1.second < proj2.first || proj2.second < proj1.first);
            });
    };
    return check_edges(poly1, poly2) && check_edges(poly2, poly1);
}
std::istream& operator>>(std::istream& in, DelimiterChar&& exp) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    char c = 0;
    in >> c;
    c = std::tolower(c);
    if (c != exp.expected) in.setstate(std::ios::failbit);
    return in;
}
std::istream& operator>>(std::istream& in, DelimiterString&& exp) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    size_t i = 0;
    while (exp.expected[i] != '\0') {
        in >> DelimiterChar{exp.expected[i]};
        ++i;
    }
    return in;
}
std::istream& operator>>(std::istream& in, Point& point) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    Point temp = {0, 0};
    in >> DelimiterChar{'('} >> temp.x >> DelimiterChar{';'} >> temp.y >> DelimiterChar{')'};
    if (in) point = temp;
    return in;
}
bool operator==(const Point& lhs, const Point& rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}
bool operator==(const Polygon& lhs, const Polygon& rhs) {
    if (lhs.points.size() != rhs.points.size()) return false;
    return std::equal(lhs.points.cbegin(), lhs.points.cend(), rhs.points.cbegin());
}
bool operator<=(const Polygon& lhs, const Polygon& rhs) {
    int innerMinX = findMinX(lhs);
    int innerMinY = findMinY(lhs);
    int innerMaxX = findMaxX(lhs);
    int innerMaxY = findMaxY(lhs);
    int outerMinX = findMinX(rhs);
    int outerMinY = findMinY(rhs);
    int outerMaxX = findMaxX(rhs);
    int outerMaxY = findMaxY(rhs);
    return (innerMinX >= outerMinX) && (innerMaxX <= outerMaxX) &&
           (innerMinY >= outerMinY) && (innerMaxY <= outerMaxY);
}
std::istream& operator>>(std::istream& in, Polygon& polygon) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    size_t countPoints = 0;
    in >> countPoints;
    if (countPoints < 3) {
        in.setstate(std::ios::failbit);
        return in;
    }
    std::vector<Point> temp;
    std::istream_iterator<Point> input_it(in);
    std::copy_n(input_it, countPoints, std::back_inserter(temp));
    if (in && temp.size() == countPoints) {
        polygon.points = temp;
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}
double AreaPolygon::operator()(double area, const Point& p2, const Point& p3) {
    area += 0.5 * std::abs((p3.y - p1.y) * (p2.x - p1.x) - (p3.x - p1.x) * (p2.y - p1.y));
    p1 = p2;
    return area;
}
double getPolygonArea(const Polygon& polygon) {
    using namespace std::placeholders;
    auto accumulateArea = std::bind(AreaPolygon{polygon.points[1]}, _1, _2, polygon.points[0]);
    return std::accumulate(polygon.points.cbegin(), polygon.points.cend(), 0.0, accumulateArea);
}
bool isRightAngle(const Polygon& polygon) {
    auto countAngle = accumulateRightAngle{
        polygon.points[polygon.points.size() - 2],
        polygon.points[polygon.points.size() - 1]
    };
    return std::find_if(polygon.points.cbegin(), polygon.points.cend(), countAngle) != polygon.points.cend();
}
bool accumulateRightAngle::operator()(const Point& p3) {
    Point vec1{p2.x - p1.x, p2.y - p1.y};
    Point vec2{p2.x - p3.x, p2.y - p3.y};
    p1 = p2;
    p2 = p3;
    return (vec1.x * vec2.x + vec1.y * vec2.y) == 0;
}
namespace {
    bool compareByX(const Point& lhs, const Point& rhs) { return lhs.x < rhs.x; }
    bool compareByY(const Point& lhs, const Point& rhs) { return lhs.y < rhs.y; }
    bool comparePolygonsByMaxX(const Polygon& lhs, const Polygon& rhs) { return findMaxX(lhs) < findMaxX(rhs); }
    bool comparePolygonsByMaxY(const Polygon& lhs, const Polygon& rhs) { return findMaxY(lhs) < findMaxY(rhs); }
    bool comparePolygonsByMinX(const Polygon& lhs, const Polygon& rhs) { return findMinX(lhs) < findMinX(rhs); }
    bool comparePolygonsByMinY(const Polygon& lhs, const Polygon& rhs) { return findMinY(lhs) < findMinY(rhs); }
}
int findMaxX(const Polygon& polygon) {
    return std::max_element(polygon.points.cbegin(), polygon.points.cend(), compareByX)->x;
}
int findMaxY(const Polygon& polygon) {
    return std::max_element(polygon.points.cbegin(), polygon.points.cend(), compareByY)->y;
}
int findMinX(const Polygon& polygon) {
    return std::min_element(polygon.points.cbegin(), polygon.points.cend(), compareByX)->x;
}
int findMinY(const Polygon& polygon) {
    return std::min_element(polygon.points.cbegin(), polygon.points.cend(), compareByY)->y;
}
Polygon getBoundingBox(const std::vector<Polygon>& polygons) {
    int pointMaxX = findMaxX(*std::max_element(polygons.cbegin(), polygons.cend(), comparePolygonsByMaxX));
    int pointMaxY = findMaxY(*std::max_element(polygons.cbegin(), polygons.cend(), comparePolygonsByMaxY));
    int pointMinX = findMinX(*std::min_element(polygons.cbegin(), polygons.cend(), comparePolygonsByMinX));
    int pointMinY = findMinY(*std::min_element(polygons.cbegin(), polygons.cend(), comparePolygonsByMinY));
    std::vector<Point> res{{pointMinX, pointMinY}, {pointMinX, pointMaxY},
                          {pointMaxX, pointMaxY}, {pointMaxX, pointMinY}};
    return Polygon{res};
}
} // namespace popov
