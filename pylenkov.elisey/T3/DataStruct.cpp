#include "DataStruct.hpp"
#include <iostream>
#include <numeric>

namespace nspace
{
    bool Point::operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }

    bool Polygon::operator==(const Polygon &other) const
    {
        return points == other.points;
    }

    double Polygon::area() const
    {
        if (points.size() < 3) return 0.0;
        double area = 0.0;
        double sum = std::accumulate(
            points.begin(),
            points.end(),
            0.0,
            [this](double acc, const Point& p1)
            {
                const Point& p2 = points[(&p1 - &points[0] + 1) % points.size()];
                return acc + (p1.x * p2.y) - (p1.y * p2.x);
            }
        );
        return std::abs(sum) / 2;
    }

    std::istream& operator>>(std::istream& in, Point& point)
    {
        char ignore;
        return in >> ignore >> point.x >> ignore >> point.y >> ignore;
    }

    std::istream& operator>>(std::istream& in, Polygon& poly)
    {
        size_t numPoints;
        if (!(in >> numPoints)) return in;

        poly.points.resize(numPoints);
        std::generate(poly.points.begin(), poly.points.end(), [&in]()
        {
            Point p;
            in >> p;
            return p;
        });
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const Point& point)
    {
        return out << "(" << point.x << "," << point.y << ")";
    }

    std::ostream& operator<<(std::ostream& out, const Polygon& poly)
    {
        out << poly.points.size() << " ";
        std::copy(poly.points.begin(), poly.points.end(),
                  std::ostream_iterator<Point>(out, " "));
        return out;
    }

    bool AreaComparator::operator()(const Polygon& a, const Polygon& b) const
    {
        return a.area() < b.area();
    }

    bool VertexCountComparator::operator()(const Polygon& a, const Polygon& b) const
    {
        return a.points.size() < b.points.size();
    }
}
