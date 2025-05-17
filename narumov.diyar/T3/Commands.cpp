#include <numeric>
#include <algorithm>
#include <iomanip>
#include <limits>

#include "Commands.hpp"
#include "iofmtguard.hpp"

namespace narumov {
    using namespace std::placeholders;
    std::map<std::string, std::function<void(const std::vector<Polygon>&, std::istream&, std::ostream&)>> commandsList = {
        { "AREA", std::bind(calcAreaSum, _1, _2, _3) },
        { "COUNT", std::bind(countPolygons, _1, _2, _3) },
        { "MIN", std::bind(findMinimum, _1, _2, _3) },
        { "MAX", std::bind(findMaximum, _1, _2, _3) },
        { "MAXSEQ", std::bind(findMaxSequence, _1, _2, _3) },
        { "INFRAME", std::bind(checkInsideFrame, _1, _2, _3) }
    };

    void executeCommand(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os) {
        std::istream::sentry sentry(is);
        if(!sentry) {
            return;
        }
        iofmtguard fmt(os);
        os << std::fixed << std::setprecision(1);
        std::string commandName;
        is >> commandName;
        auto it = commandsList.find(commandName);
        if (it == commandsList.end()) {
            is.setstate(std::ios::failbit);
            return;
        }
        it->second(polygons, is, os);
    }

    void calcAreaSum(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os) {
        std::string mode;
        is >> mode;
        double result = 0.0;
        if (mode == "EVEN" || mode == "ODD") {
            bool isEven = (mode == "EVEN");
            result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [=](double sum, const Polygon& poly) {
                    return (poly.points.size() % 2 == 0) == isEven ? sum + poly.getArea() : sum;
                }
            );
        } else if (mode == "MEAN") {
            if (!polygons.empty()) {
                double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                    [](double sum, const Polygon& poly) {
                        return sum + poly.getArea();
                    }
                );
                result = total / polygons.size();
            } else {
                is.setstate(std::ios::failbit);
                return;
            }
        } else {
            try {
                std::size_t n = std::stoul(mode);
                if(n < 3) {
                    is.setstate(std::ios::failbit);
                    return;
                }
                result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                    [=](double sum, const Polygon& poly) {
                        return poly.points.size() == n ? sum + poly.getArea() : sum;
                    }
                );
            } catch (...) {
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
        if (mode == "EVEN" || mode == "ODD") {
            bool isEven = (mode == "EVEN");
            count = std::count_if(polygons.begin(), polygons.end(),
                [=](const Polygon& poly) {
                    return (poly.points.size() % 2 == 0) == isEven;
                }
            );
        } else {
            try {
                std::size_t n = std::stoul(mode);
                if(n < 3) {
                    is.setstate(std::ios::failbit);
                    return;
                }
                count = std::count_if(polygons.begin(), polygons.end(),
                    [=](const Polygon& poly) {
                        return poly.points.size() == n;
                    }
                );
            } catch (...) {
                is.setstate(std::ios::failbit);
                return;
            }
        }
        os << count;
    }

    void findMinimum(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os) {
        std::string field;
        is >> field;
        if (polygons.empty()) {
            is.setstate(std::ios::failbit);
            return;
        }
        if (field == "AREA") {
            double minArea = std::min_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.getArea() < b.getArea();
                }
            )->getArea();
            os << minArea;
        } else if (field == "VERTEXES") {
            std::size_t minVertices = std::min_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
                }
            )->points.size();
            os << minVertices;
        } else {
            is.setstate(std::ios::failbit);
        }
    }

    void findMaximum(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os) {
        std::string field;
        is >> field;
        if (polygons.empty()) {
            is.setstate(std::ios::failbit);
            return;
        }
        if (field == "AREA") {
            double maxArea = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.getArea() < b.getArea();
                }
            )->getArea();
            os << maxArea;
        } else if (field == "VERTEXES") {
            std::size_t maxVertices = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
                }
            )->points.size();
            os << maxVertices;
        } else {
            is.setstate(std::ios::failbit);
        }
    }

    void findMaxSequence(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os) {
        Polygon target;
        is >> target;
        if(!is) {
            return;
        }
        using State = std::pair<std::size_t, std::size_t>;
        std::size_t maxSeq = std::accumulate(polygons.begin(), polygons.end(), State(0, 0),
            [=](State state, const Polygon& poly) {
                std::size_t current = (poly == target ? state.first + 1 : 0);
                return State(current, std::max(state.second, current));
            }
        ).second;
        os << maxSeq;
    }

    void checkInsideFrame(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os) {
        Polygon target;
        is >> target;
        if(!is) {
            return;
        }
        using Rect = std::pair<Point, Point>;
        Rect boundingBox = std::accumulate(polygons.begin(), polygons.end(),
            Rect(
                Point{ std::numeric_limits<int>::max(), std::numeric_limits<int>::max() },
                Point{ std::numeric_limits<int>::min(), std::numeric_limits<int>::min() }
            ),
            [](Rect acc, const Polygon& poly) {
                Point bottomLeft = std::accumulate(poly.points.begin(), poly.points.end(),
                    Point{ std::numeric_limits<int>::max(), std::numeric_limits<int>::max() },
                    [](Point p, const Point& q) {
                        return Point{ std::min(p.x, q.x), std::min(p.y, q.y) };
                    }
                );
                Point topRight = std::accumulate(poly.points.begin(), poly.points.end(),
                    Point{ std::numeric_limits<int>::min(), std::numeric_limits<int>::min() },
                    [](Point p, const Point& q) {
                        return Point{ std::max(p.x, q.x), std::max(p.y, q.y) };
                    }
                );
                return Rect{
                    Point{ std::min(acc.first.x, bottomLeft.x), std::min(acc.first.y, bottomLeft.y) },
                    Point{ std::max(acc.second.x, topRight.x), std::max(acc.second.y, topRight.y) }
                };
            }
        );
        os << (target.isInsideFrame(boundingBox.first, boundingBox.second) ? "<TRUE>" : "<FALSE>");
    }
}
