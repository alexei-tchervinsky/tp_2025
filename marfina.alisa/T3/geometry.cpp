#include "geometry.hpp"
#include "iofmtguard.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <iostream>
#include <functional>
using namespace std::placeholders;

bool AreaComparator::operator()(const Polygon& a, const Polygon& b) const
{
    return calculateArea(a) < calculateArea(b);
}

bool VertexCountComparator::operator()(const Polygon& a, const Polygon& b) const
{
    return a.points.size() < b.points.size();
}

double calculateArea(const Polygon& polygon)
{
    auto areaAccumulator = [](double sum, const Point& a, const Point& b)
    {
        return sum + (a.x * b.y - b.x * a.y);
    };

    double area = 0.0;
    size_t n = polygon.points.size();
    for (size_t i = 0; i < n; ++i)
    {
        size_t j = (i + 1) % n;
        area = areaAccumulator(area, polygon.points[i], polygon.points[j]);
    }
    return std::abs(area) / 2.0;
}

BoundingBox calculateBoundingBox(const std::vector<Polygon>& polygons)
{
    if (polygons.empty()) return {{0, 0}, {0, 0}};

    auto extractMinX = [](const Polygon& p)
    {
        return std::min_element(p.points.begin(), p.points.end(),
            [](const Point& a, const Point& b) { return a.x < b.x; })->x;
    };

    auto extractMaxX = [](const Polygon& p)
    {
        return std::max_element(p.points.begin(), p.points.end(),
            [](const Point& a, const Point& b) { return a.x < b.x; })->x;
    };

    auto extractMinY = [](const Polygon& p)
    {
        return std::min_element(p.points.begin(), p.points.end(),
            [](const Point& a, const Point& b) { return a.y < b.y; })->y;
    };

    auto extractMaxY = [](const Polygon& p)
    {
        return std::max_element(p.points.begin(), p.points.end(),
            [](const Point& a, const Point& b) { return a.y < b.y; })->y;
    };

    auto minX = *std::min_element(polygons.begin(), polygons.end(),
        [&](const Polygon& a, const Polygon& b) {
            return extractMinX(a) < extractMinX(b);
        });
    auto maxX = *std::max_element(polygons.begin(), polygons.end(),
        [&](const Polygon& a, const Polygon& b) {
            return extractMaxX(a) < extractMaxX(b);
        });
    auto minY = *std::min_element(polygons.begin(), polygons.end(),
        [&](const Polygon& a, const Polygon& b) {
            return extractMinY(a) < extractMinY(b);
        });
    auto maxY = *std::max_element(polygons.begin(), polygons.end(),
        [&](const Polygon& a, const Polygon& b) {
            return extractMaxY(a) < extractMaxY(b);
        });

    return
    {
        {extractMinX(minX), extractMinY(minY)},
        {extractMaxX(maxX), extractMaxY(maxY)}
    };
}

void areaCommand(const std::vector<Polygon>& polygons, const std::string& arg)
{
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);
    using AreaFilter = std::function<bool(const Polygon&)>;
    AreaFilter filter;
    if (arg == "EVEN")
    {
        filter = [](const Polygon& p) { return p.points.size() % 2 == 0; };
    }
    else if (arg == "ODD")
    {
        filter = [](const Polygon& p) { return p.points.size() % 2 != 0; };
    }
    else if (arg == "MEAN")
    {
        if (polygons.empty())
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, const Polygon& p) { return sum + calculateArea(p); });
        std::cout << total / polygons.size() << '\n';
        return;
    }
    else
    {
        try
        {
            size_t num = std::stoul(arg);
            if (num < 3)
            {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            filter = std::bind(
                [](size_t n, const Polygon& p) { return p.points.size() == n; },
                num, _1
            );
        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
    }

    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
        [&filter](double sum, const Polygon& p) {
            return filter(p) ? sum + calculateArea(p) : sum;
        });
    std::cout << sum << '\n';
}

void maxMinCommand(const std::vector<Polygon>& polygons, const std::string& type, const std::string& arg) {
    if (polygons.empty())
    {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);
    using Comparator = std::function<bool(const Polygon&, const Polygon&)>;
    using Extractor = std::function<double(const Polygon&)>;
    Comparator comp;
    Extractor extractor;
    if (arg == "AREA")
    {
        comp = AreaComparator();
        extractor = [](const Polygon& p) { return calculateArea(p); };
    }
    else if (arg == "VERTEXES")
    {
        comp = VertexCountComparator();
        extractor = [](const Polygon& p) { return static_cast<double>(p.points.size()); };
    }
    else
    {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    auto resultIt = (type == "MAX")
        ? std::max_element(polygons.begin(), polygons.end(), comp)
        : std::min_element(polygons.begin(), polygons.end(), comp);

    std::cout << extractor(*resultIt) << '\n';
}

std::vector<Polygon> readPolygonsFromFile(const std::string& filename)
{
    std::vector<Polygon> polygons;
    std::ifstream file(filename);
    if (!file)
    {
        throw std::runtime_error("Cannot open file");
    }
    std::string line;
    while (std::getline(file, line))
    {
        Polygon poly;
        if (parsePolygon(line, poly))
        {
            polygons.push_back(std::move(poly));
        }
    }
    return polygons;
}

void processCommands(std::vector<Polygon>& polygons)
{
    std::string command;
    while (std::cin >> command)
    {
        try {
            if (command == "AREA")
            {
                std::string arg;
                std::cin >> arg;
                areaCommand(polygons, arg);
            }
            else if (command == "MAX" || command == "MIN")
            {
                std::string arg;
                std::cin >> arg;
                maxMinCommand(polygons, command, arg);
            }
            else if (command == "COUNT")
            {
                std::string arg;
                std::cin >> arg;
                countCommand(polygons, arg);
            }
            else if (command == "INFRAME")
            {
                std::string arg;
                std::getline(std::cin >> std::ws, arg);
                inframeCommand(polygons, arg);
            }
            else if (command == "INTERSECTIONS")
            {
                std::string arg;
                std::getline(std::cin >> std::ws, arg);
                intersectionsCommand(polygons, arg);
            }
            else if (command == "ECHO")
            {
                std::string arg;
                std::getline(std::cin >> std::ws, arg);
                echoCommand(polygons, arg);
            }
            else
            {
                std::cout << "<INVALID COMMAND>\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void countCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
    using CountPredicate = std::function<bool(const Polygon&)>;
    CountPredicate predicate;

    if (arg == "EVEN") {
        predicate = [](const Polygon& p) { return p.points.size() % 2 == 0; };
    }
    else if (arg == "ODD") {
        predicate = [](const Polygon& p) { return p.points.size() % 2 != 0; };
    }
    else {
        try {
            size_t num = std::stoul(arg);
            if (num < 3) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            predicate = std::bind(
                [](size_t n, const Polygon& p) { return p.points.size() == n; },
                num,
                std::placeholders::_1
            );
        }
        catch (...) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
    }

    size_t count = std::count_if(polygons.begin(), polygons.end(), predicate);
    std::cout << count << '\n';
}

void inframeCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
    if (polygons.empty()) {
        std::cout << "<FALSE>\n";
        return;
    }

    Polygon poly;
    if (!parsePolygon(arg, poly))
    {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    const BoundingBox bbox = calculateBoundingBox(polygons);
    auto isInside = [&bbox](const Point& p)
    {
        return p.x >= bbox.min.x && p.x <= bbox.max.x &&
               p.y >= bbox.min.y && p.y <= bbox.max.y;
    };

    bool allInside = std::all_of(poly.points.begin(), poly.points.end(), isInside);
    std::cout << (allInside ? "<TRUE>" : "<FALSE>") << '\n';
}

struct SegmentIntersector
{
    bool operator()(const Point& a1, const Point& a2,
                   const Point& b1, const Point& b2) const
    {
        int orient1 = orientation(a1, a2, b1);
        int orient2 = orientation(a1, a2, b2);
        int orient3 = orientation(b1, b2, a1);
        int orient4 = orientation(b1, b2, a2);
        if (orient1 != orient2 && orient3 != orient4) return true;
        if (orient1 == 0 && onSegment(a1, b1, a2)) return true;
        if (orient2 == 0 && onSegment(a1, b2, a2)) return true;
        if (orient3 == 0 && onSegment(b1, a1, b2)) return true;
        if (orient4 == 0 && onSegment(b1, a2, b2)) return true;

        return false;
    }

private:
    static int orientation(const Point& p, const Point& q, const Point& r)
    {
        int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (val == 0) return 0;
        return (val > 0) ? 1 : 2;
    }

    static bool onSegment(const Point& p, const Point& q, const Point& r)
    {
        return q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
               q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y);
    }
};

void intersectionsCommand(const std::vector<Polygon>& polygons, const std::string& arg)
{
    Polygon poly;
    if (!parsePolygon(arg, poly))
    {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    SegmentIntersector intersector;
    size_t intersectionCount = 0;
    auto polygonsIntersect = [&intersector](const Polygon& a, const Polygon& b)
    {
        for (size_t i = 0; i < a.points.size(); ++i)
        {
            size_t j = (i + 1) % a.points.size();
            for (size_t k = 0; k < b.points.size(); ++k)
            {
                size_t l = (k + 1) % b.points.size();
                if (intersector(a.points[i], a.points[j], b.points[k], b.points[l]))
                {
                    return true;
                }
            }
        }
        return false;
    };

    auto checkIntersection = std::bind(polygonsIntersect, std::cref(poly), std::placeholders::_1);
    intersectionCount = std::count_if(polygons.begin(), polygons.end(), checkIntersection);
    std::cout << intersectionCount << '\n';
}

void echoCommand(std::vector<Polygon>& polygons, const std::string& arg)
{
    Polygon poly;
    if (!parsePolygon(arg, poly))
    {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    polygons.push_back(poly);
    std::cout << polygons.size() << '\n';
}

bool parsePolygon(const std::string& str, Polygon& out)
{
    std::istringstream iss(str);
    size_t vertexCount;
    iss >> vertexCount;
    if (vertexCount < 3) return false;
    out.points.clear();
    Point p;
    char discard;
    while (iss >> discard && discard == '(' &&
           iss >> p.x &&
           iss >> discard && discard == ';' &&
           iss >> p.y &&
           iss >> discard && discard == ')')
    {
        out.points.push_back(p);
    }

    return out.points.size() == vertexCount;
}
