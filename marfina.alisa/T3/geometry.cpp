#include "geometry.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <functional>
#include <cmath>
#include <limits>
#include <optional>

using namespace std::placeholders;

bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Point& lhs, const Point& rhs)
{
    return !(lhs == rhs);
}

bool Polygon::hasRightAngle() const
{
    auto dotProduct = [](const Point& a, const Point& b, const Point& c)
    {
        int abx = b.x - a.x;
        int aby = b.y - a.y;
        int bcx = c.x - b.x;
        int bcy = c.y - b.y;
        return abx * bcx + aby * bcy;
    };
    return std::any_of(points.begin(), points.end(),
        [this, &dotProduct, i = 0](const Point& p) mutable {
            const Point& prev = points[(i + points.size() - 1) % points.size()];
            const Point& next = points[(i + 1) % points.size()];
            i++;
            return dotProduct(prev, p, next) == 0;
        });
}

bool isPolygonValid(const Polygon& poly) {
    return poly.points.size() >= 3;
}

double calculateArea(const Polygon& polygon)
{
    if (!isPolygonValid(polygon)) return 0.0;
    auto areaAccumulator = [](double sum, const Point& a, const Point& b)
    {
        return sum + (a.x * b.y - b.x * a.y);
    };
    double sum = std::inner_product(
        polygon.points.begin(), polygon.points.end() - 1,
        polygon.points.begin() + 1,
        0.0,
        std::plus<>(),
        areaAccumulator
    );
    sum += areaAccumulator(0.0, polygon.points.back(), polygon.points.front());
    return std::abs(sum) / 2.0;
}

double calculateArea(const std::vector<Polygon>& polygons)
{
    return std::accumulate(polygons.begin(), polygons.end(), 0.0,
        [](double sum, const Polygon& p) { return sum + calculateArea(p); });
}

std::vector<Polygon> readPolygonsFromFile(const std::string& filename)
{
    std::vector<Polygon> polygons;
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Cannot open file");
    auto parsePoint = [](std::istringstream& iss) -> std::optional<Point>
    {
        char discard;
        Point p;
        if (iss >> discard && discard == '(' &&
            iss >> p.x &&
            iss >> discard && discard == ';' &&
            iss >> p.y &&
            iss >> discard && discard == ')')
        {
            return p;
        }
        return std::nullopt;
    };

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        size_t vertexCount;
        if (iss >> vertexCount)
        {
            Polygon poly;
            while (auto point = parsePoint(iss))
            {
                poly.points.push_back(*point);
            }
            if (poly.points.size() == vertexCount && isPolygonValid(poly))
            {
                polygons.push_back(poly);
            }
        }
    }
    return polygons;
}

void areaCommand(const std::vector<Polygon>& polygons, const std::string& arg)
{
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);
    auto areaFilter = [](const Polygon& p, const std::function<bool(size_t)>& pred) {
        return pred(p.points.size()) ? calculateArea(p) : 0.0;
    };
    if (arg == "EVEN")
    {
        auto sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            std::bind(areaFilter, _1, [](size_t n) { return n % 2 == 0; }));
        std::cout << sum << '\n';
    }
    else if (arg == "ODD")
    {
        auto sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            std::bind(areaFilter, _1, [](size_t n) { return n % 2 != 0; }));
        std::cout << sum << '\n';
    }
    else if (arg == "MEAN")
    {
        if (polygons.empty())
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        auto sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double acc, const Polygon& p) { return acc + calculateArea(p); });
        std::cout << sum / polygons.size() << '\n';
    }
    else
    {
        try
        {
            size_t num = std::stoul(arg);
            if (num < 3) throw std::invalid_argument("Invalid vertex count");
            auto sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                std::bind(areaFilter, _1, [num](size_t n) { return n == num; }));
            std::cout << sum << '\n';
        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

void maxCommand(const std::vector<Polygon>& polygons, const std::string& arg)
{
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);

    if (polygons.empty())
    {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    if (arg == "AREA")
    {
        auto maxIt = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b)
            {
                return calculateArea(a) < calculateArea(b);
            });
        std::cout << calculateArea(*maxIt) << '\n';
    }
    else if (arg == "VERTEXES")
    {
        auto maxIt = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b)
            {
                return a.points.size() < b.points.size();
            });
        std::cout << maxIt->points.size() << '\n';
    }
    else
    {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void minCommand(const std::vector<Polygon>& polygons, const std::string& arg)
{
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);
    if (polygons.empty())
    {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    if (arg == "AREA")
    {
        auto minIt = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return calculateArea(a) < calculateArea(b);
            });
        std::cout << calculateArea(*minIt) << '\n';
    }
    else if (arg == "VERTEXES")
    {
        auto minIt = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b)
            {
                return a.points.size() < b.points.size();
            });
        std::cout << minIt->points.size() << '\n';
    }
    else
    {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void countCommand(const std::vector<Polygon>& polygons, const std::string& arg)
{
    auto countIf = [&polygons](const std::function<bool(size_t)>& pred)
    {
        return std::count_if(polygons.begin(), polygons.end(),
            [&pred](const Polygon& p) { return pred(p.points.size()); });
    };
    if (arg == "EVEN")
    {
        std::cout << countIf([](size_t n) { return n % 2 == 0; }) << '\n';
    }
    else if (arg == "ODD")
    {
        std::cout << countIf([](size_t n) { return n % 2 != 0; }) << '\n';
    }
    else
    {
        try
        {
            size_t num = std::stoul(arg);
            if (num < 3) throw std::invalid_argument("Invalid vertex count");
            std::cout << countIf([num](size_t n) { return n == num; }) << '\n';
        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

void rightShapesCommand(const std::vector<Polygon>& polygons)
{
    auto count = std::count_if(polygons.begin(), polygons.end(),
        std::bind(&Polygon::hasRightAngle, _1));
    std::cout << count << '\n';
}

bool isPointInFrame(const Point& p, const Polygon& frame)
{
    auto [minX, maxX] = std::minmax_element(frame.points.begin(), frame.points.end(),
        [](const Point& a, const Point& b) { return a.x < b.x; });
    auto [minY, maxY] = std::minmax_element(frame.points.begin(), frame.points.end(),
        [](const Point& a, const Point& b) { return a.y < b.y; });

    return p.x >= minX->x && p.x <= maxX->x && p.y >= minY->y && p.y <= maxY->y;
}

bool doPolygonsIntersect(const Polygon& a, const Polygon& b)
{
    auto getBounds = [](const Polygon& p) {
        auto [minX, maxX] = std::minmax_element(p.points.begin(), p.points.end(),
            [](const Point& a, const Point& b) { return a.x < b.x; });
        auto [minY, maxY] = std::minmax_element(p.points.begin(), p.points.end(),
            [](const Point& a, const Point& b) { return a.y < b.y; });
        return std::make_tuple(minX->x, maxX->x, minY->y, maxY->y);
    };

    auto [aMinX, aMaxX, aMinY, aMaxY] = getBounds(a);
    auto [bMinX, bMaxX, bMinY, bMaxY] = getBounds(b);

    return !(aMaxX < bMinX || aMinX > bMaxX || aMaxY < bMinY || aMinY > bMaxY);
}

void inframeCommand(std::vector<Polygon>& polygons, const std::string& arg)
{
    if (polygons.empty())
    {
        std::cout << "<FALSE>\n";
        return;
    }
    try
    {
        size_t vertexCount = std::stoul(arg);
        if (vertexCount < 3)
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        Polygon poly;
        std::string pointStr;
        std::getline(std::cin >> std::ws, pointStr);
        std::istringstream iss(pointStr);
        auto parsePoint = [](std::istringstream& iss) -> std::optional<Point>
        {
            char discard;
            Point p;
            if (iss >> discard && discard == '(' &&
                iss >> p.x &&
                iss >> discard && discard == ';' &&
                iss >> p.y &&
                iss >> discard && discard == ')')
            {
                return p;
            }
            return std::nullopt;
        };

        while (auto point = parsePoint(iss))
        {
            poly.points.push_back(*point);
        }
        if (poly.points.size() != vertexCount || !isPolygonValid(poly))
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        auto getFrame = [](const std::vector<Polygon>& polys)
        {
            int minX = std::numeric_limits<int>::max();
            int maxX = std::numeric_limits<int>::min();
            int minY = std::numeric_limits<int>::max();
            int maxY = std::numeric_limits<int>::min();

            for (const auto& poly : polys)
            {
                for (const auto& p : poly.points)
                {
                    minX = std::min(minX, p.x);
                    maxX = std::max(maxX, p.x);
                    minY = std::min(minY, p.y);
                    maxY = std::max(maxY, p.y);
                }
            }
            return std::make_tuple(minX, maxX, minY, maxY);
        };
        auto [minX, maxX, minY, maxY] = getFrame(polygons);
        bool allInside = std::all_of(poly.points.begin(), poly.points.end(),
            [=](const Point& p) {
                return p.x >= minX && p.x <= maxX && p.y >= minY && p.y <= maxY;
            });

        std::cout << (allInside ? "<TRUE>" : "<FALSE>") << '\n';
    }
    catch (...)
    {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void intersectionsCommand(const std::vector<Polygon>& polygons, const std::string& arg)
{
    if (polygons.empty())
    {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    try
    {
        size_t vertexCount = std::stoul(arg);
        if (vertexCount < 3)
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        Polygon poly;
        std::string pointStr;
        std::getline(std::cin >> std::ws, pointStr);
        std::istringstream iss(pointStr);
        auto parsePoint = [](std::istringstream& iss) -> std::optional<Point>
        {
            char discard;
            Point p;
            if (iss >> discard && discard == '(' &&
                iss >> p.x &&
                iss >> discard && discard == ';' &&
                iss >> p.y &&
                iss >> discard && discard == ')')
            {
                return p;
            }
            return std::nullopt;
        };
        while (auto point = parsePoint(iss))
        {
            poly.points.push_back(*point);
        }
        if (poly.points.size() != vertexCount || !isPolygonValid(poly))
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        auto count = std::count_if(polygons.begin(), polygons.end(),
            [&poly](const Polygon& p) { return doPolygonsIntersect(poly, p); });

        std::cout << count << '\n';
    }
    catch (...)
    {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void processCommands(std::vector<Polygon>& polygons)
{
    std::string command;
    while (std::cin >> command)
    {
        try
        {
            if (command == "AREA")
            {
                std::string arg;
                std::cin >> arg;
                areaCommand(polygons, arg);
            }
            else if (command == "MAX")
            {
                std::string arg;
                std::cin >> arg;
                maxCommand(polygons, arg);
            }
            else if (command == "MIN")
            {
                std::string arg;
                std::cin >> arg;
                minCommand(polygons, arg);
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
                std::cin >> arg;
                inframeCommand(polygons, arg);
            }
            else if (command == "INTERSECTIONS")
            {
                std::string arg;
                std::cin >> arg;
                intersectionsCommand(polygons, arg);
            }
            else if (command == "RIGHTSHAPES")
            {
                rightShapesCommand(polygons);
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
