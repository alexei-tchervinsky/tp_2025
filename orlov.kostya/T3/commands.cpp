#include <numeric>
#include <algorithm>
#include <iomanip>
#include <limits>

#include "commands.hpp"
#include "iofmtguard.hpp"

namespace orlov
{
    using namespace std::placeholders;

    std::map<std::string, std::function<void(const std::vector<Polygon>&, std::istream&, std::ostream&)>> commandsList =
    {
        { "AREA", std::bind(calcAreaSum, _1, _2, _3) },
        { "COUNT", std::bind(countPolygons, _1, _2, _3) },
        { "MIN", std::bind(findMinimum, _1, _2, _3) },
        { "MAX", std::bind(findMaximum, _1, _2, _3) },
        { "INTERSECTIONS", std::bind(intersectPolygons, _1, _2, _3) },
        { "INFRAME", std::bind(checkInsideFrame, _1, _2, _3) }
    };

    void executeCommand(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os)
    {
        std::istream::sentry sentry(is);
        if (!sentry) return;

        iofmtguard fmt(os);
        os << std::fixed << std::setprecision(1);

        std::string commandName;
        is >> commandName;
        auto it = commandsList.find(commandName);

        if (it == commandsList.end())
        {
            is.setstate(std::ios::failbit);
            return;
        }

        it->second(polygons, is, os);
    }

    void calcAreaSum(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os)
    {
        std::string mode;
        is >> mode;

        double result = 0.0;

        if (mode == "EVEN" || mode == "ODD")
        {
            bool isEven = (mode == "EVEN");

            result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [=](double sum, const Polygon& poly)
                {
                    return (poly.points.size() % 2 == 0) == isEven ? sum + poly.getArea() : sum;
                }
            );
        }
        else if (mode == "MEAN")
        {
            if (!polygons.empty())
            {
                double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                    [](double sum, const Polygon& poly)
                    {
                        return sum + poly.getArea();
                    }
                );

                result = total / polygons.size();
            }
            else
            {
                is.setstate(std::ios::failbit);
                return;
            }
        }
        else
        {
            try
            {
                std::size_t n = std::stoul(mode);

                if (n < 3)
                {
                    is.setstate(std::ios::failbit);
                    return;
                }

                result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                    [=](double sum, const Polygon& poly)
                    {
                        return poly.points.size() == n ? sum + poly.getArea() : sum;
                    }
                );
            }
            catch (...)
            {
                is.setstate(std::ios::failbit);
                return;
            }
        }

        os << result;
    }

    void countPolygons(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os) {
        std::string mode;
        is >> mode;

        std::size_t count = 0;

        if (mode == "EVEN" || mode == "ODD")
        {
            bool isEven = (mode == "EVEN");

            count = std::count_if(polygons.begin(), polygons.end(),
                [=](const Polygon& poly)
                {
                    return (poly.points.size() % 2 == 0) == isEven;
                }
            );
        }
        else
        {
            try
            {
                std::size_t n = std::stoul(mode);
                if(n < 3)
                {
                    is.setstate(std::ios::failbit);
                    return;
                }
                count = std::count_if(polygons.begin(), polygons.end(),
                    [=](const Polygon& poly)
                    {
                        return poly.points.size() == n;
                    }
                );
            }
            catch (...)
            {
                is.setstate(std::ios::failbit);
                return;
            }
        }

        os << count;
    }

    void findMinimum(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os)
    {
        std::string field;
        is >> field;

        if (polygons.empty())
        {
            is.setstate(std::ios::failbit);
            return;
        }

        if (field == "AREA")
        {
            double minArea = std::min_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b)
                {
                    return a.getArea() < b.getArea();
                }
            )->getArea();
            os << minArea;
        }
        else if (field == "VERTEXES")
        {
            std::size_t minVertices = std::min_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b)
                {
                    return a.points.size() < b.points.size();
                }
            )->points.size();
            os << minVertices;
        }
        else is.setstate(std::ios::failbit);
    }

    void findMaximum(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os)
    {
        std::string field;
        is >> field;

        if (polygons.empty())
        {
            is.setstate(std::ios::failbit);
            return;
        }

        if (field == "AREA")
        {
            double maxArea = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b)
                {
                    return a.getArea() < b.getArea();
                }
            )->getArea();
            os << maxArea;
        }
        else if (field == "VERTEXES")
        {
            std::size_t maxVertices = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b)
                {
                    return a.points.size() < b.points.size();
                }
            )->points.size();
            os << maxVertices;
        }
        else is.setstate(std::ios::failbit);
    }

    int orientation(Point p, Point q, Point r)
    {
        long long val = (long long)(q.y_ - p.y_) * (r.x_ - q.x_) -
                        (long long)(q.x_ - p.x_) * (r.y_ - q.y_);
        if (val == 0) return 0;

        return (val > 0) ? 1 : 2;
    }

    bool onSegment(Point p, Point q, Point r)
    {
        if
        (
            q.x_ <= std::max(p.x_, r.x_) && q.x_ >= std::min(p.x_, r.x_) &&
            q.y_ <= std::max(p.y_, r.y_) && q.y_ >= std::min(p.y_, r.y_)
        )
            return true;

        return false;
    }

    bool checkIntersection(Point p1, Point q1, Point p2, Point q2)
    {
        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);

        if (o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0 && o1 != o2 && o3 != o4)
            return true;

        if (o1 == 0 && onSegment(p1, p2, q1)) return true;
        if (o2 == 0 && onSegment(p1, q2, q1)) return true;
        if (o3 == 0 && onSegment(p2, p1, q2)) return true;
        if (o4 == 0 && onSegment(p2, q1, q2)) return true;

        return false;
    }

    bool doPolygonsIntersect(const Polygon& poly1, const Polygon& poly2)
    {
        if (poly1.points.empty() || poly2.points.empty()) return false;

        for (std::size_t i = 0; i < poly1.points.size(); ++i)
        {
            Point p1 = poly1.points[i];
            Point q1 = poly1.points[(i + 1) % poly1.points.size()];

            for (std::size_t j = 0; j < poly2.points.size(); ++j)
            {
                Point p2 = poly2.points[j];
                Point q2 = poly2.points[(j + 1) % poly2.points.size()];

                if (checkIntersection(p1, q1, p2, q2)) return true;
            }
        }

        return false;
    }

    void intersectPolygons(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os)
    {
        Polygon target;
        is >> target;

        if (!is) return;

        std::size_t intersectionsCount = 0;
        for (const auto& poly : polygons)
        {
            if (doPolygonsIntersect(poly, target))
                intersectionsCount++;
        }
        os << intersectionsCount;
    }

    void checkInsideFrame(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os)
    {
        Polygon target;
        is >> target;

        if(!is) return;

        using Rect = std::pair<Point, Point>;
        Rect boundingBox = std::accumulate(polygons.begin(), polygons.end(),
            Rect
            (
                Point{ std::numeric_limits<int>::max(), std::numeric_limits<int>::max() },
                Point{ std::numeric_limits<int>::min(), std::numeric_limits<int>::min() }
            ),
            [](Rect acc, const Polygon& poly)
            {
                Point bottomLeft = std::accumulate(poly.points.begin(), poly.points.end(),
                    Point{ std::numeric_limits<int>::max(), std::numeric_limits<int>::max() },
                    [](Point p, const Point& q) {
                        return Point{ std::min(p.x_, q.x_), std::min(p.y_, q.y_) };
                    }
                );
                Point topRight = std::accumulate(poly.points.begin(), poly.points.end(),
                    Point{ std::numeric_limits<int>::min(), std::numeric_limits<int>::min() },
                    [](Point p, const Point& q) {
                        return Point{ std::max(p.x_, q.x_), std::max(p.y_, q.y_) };
                    }
                );
                return Rect{
                    Point{ std::min(acc.first.x_, bottomLeft.x_), std::min(acc.first.y_, bottomLeft.y_) },
                    Point{ std::max(acc.second.x_, topRight.x_), std::max(acc.second.y_, topRight.y_) }
                };
            }
        );
        os << (target.isInsideFrame(boundingBox.first, boundingBox.second) ? "<TRUE>" : "<FALSE>");
    }
}

