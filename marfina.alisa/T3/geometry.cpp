#include "geometry.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <limits>
#include <stdexcept>

bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Point& lhs, const Point& rhs)
{
    return !(lhs == rhs);
}

bool isPolygonValid(const Polygon& poly)
{
    return poly.points.size() >= 3;
}

double calculateArea(const Polygon& polygon)
{
    if (!isPolygonValid(polygon))
    {
        return 0.0;
    }
    double area = 0.0;
    size_t n = polygon.points.size();
    for (size_t i = 0; i < n; ++i)
    {
        size_t j = (i + 1) % n;
        area += (polygon.points[i].x * polygon.points[j].y) -
                (polygon.points[j].x * polygon.points[i].y);
    }
    return std::abs(area) / 2.0;
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
    if (!file)
    {
        throw std::runtime_error("Cannot open file");
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        size_t vertexCount;
        if (iss >> vertexCount)
        {
            Polygon poly;
            Point p;
            char discard;
            while (iss >> discard && discard == '(' &&
                   iss >> p.x &&
                   iss >> discard && discard == ';' &&
                   iss >> p.y &&
                   iss >> discard && discard == ')')
            {
                poly.points.push_back(p);
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

    if (arg == "EVEN")
    {
        double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double s, const Polygon& p)
            {
                return p.points.size() % 2 == 0 ? s + calculateArea(p) : s;
            });
        std::cout << sum << '\n';
    }
    else if (arg == "ODD")
    {
        double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double s, const Polygon& p)
            {
                return p.points.size() % 2 != 0 ? s + calculateArea(p) : s;
            });
        std::cout << sum << '\n';
    }
    else if (arg == "MEAN")
    {
        if (polygons.empty())
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        double total = calculateArea(polygons);
        std::cout << total / polygons.size() << '\n';
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
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [num](double s, const Polygon& p) {
                    return p.points.size() == num ? s + calculateArea(p) : s;
                });
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
            [](const Polygon& a, const Polygon& b)
            {
                return calculateArea(a) < calculateArea(b);
            });
        std::cout << calculateArea(*minIt) << '\n';
    }
    else if (arg == "VERTEXES")
    {
        auto minIt = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
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
    if (arg == "EVEN")
    {
        size_t count = std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) { return p.points.size() % 2 == 0; });
        std::cout << count << '\n';
    }
    else if (arg == "ODD")
    {
        size_t count = std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) { return p.points.size() % 2 != 0; });
        std::cout << count << '\n';
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
            size_t count = std::count_if(polygons.begin(), polygons.end(),
                [num](const Polygon& p) { return p.points.size() == num; });
            std::cout << count << '\n';
        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

void echoCommand(std::vector<Polygon>& polygons, const std::string& arg)
{
    try
    {
        size_t vertexCount = std::stoul(arg);
        if (vertexCount < 3)
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        Polygon poly;
        Point p;
        char discard;
        std::cin >> discard;
        if (discard != '(')
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        for (size_t i = 0; i < vertexCount; ++i)
        {
            if (!(std::cin >> p.x >> discard >> p.y >> discard) || discard != ')')
            {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            poly.points.push_back(p);
            if (i != vertexCount - 1)
            {
                std::cin >> discard;
                if (discard != '(')
                {
                    std::cout << "<INVALID COMMAND>\n";
                    return;
                }
            }
        }

        if (poly.points.size() == vertexCount && isPolygonValid(poly))
        {
            polygons.push_back(poly);
            std::cout << vertexCount << '\n';
        }
        else
        {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
    catch (...)
    {
        std::cout << "<INVALID COMMAND>\n";
    }
}

bool isPointInFrame(const Point& p, const Polygon& frame)
{
    if (frame.points.size() < 3) return false;
    int minX = frame.points[0].x;
    int maxX = frame.points[0].x;
    int minY = frame.points[0].y;
    int maxY = frame.points[0].y;
    for (const auto& point : frame.points)
    {
        minX = std::min(minX, point.x);
        maxX = std::max(maxX, point.x);
        minY = std::min(minY, point.y);
        maxY = std::max(maxY, point.y);
    }
    return p.x >= minX && p.x <= maxX && p.y >= minY && p.y <= maxY;
}

void inframeCommand(const std::vector<Polygon>& polygons, const std::string& arg)
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
        Point p;
        char discard;
        std::cin >> discard;
        if (discard != '(')
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        for (size_t i = 0; i < vertexCount; ++i)
        {
            if (!(std::cin >> p.x >> discard >> p.y >> discard) || discard != ')')
            {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            poly.points.push_back(p);
            if (i != vertexCount - 1)
            {
                std::cin >> discard;
                if (discard != '(')
                {
                    std::cout << "<INVALID COMMAND>\n";
                    return;
                }
            }
        }
        if (poly.points.size() != vertexCount || !isPolygonValid(poly))
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        if (polygons.empty())
        {
            std::cout << "<FALSE>\n";
            return;
        }
        int minX = polygons[0].points[0].x;
        int maxX = polygons[0].points[0].x;
        int minY = polygons[0].points[0].y;
        int maxY = polygons[0].points[0].y;
        for (const auto& polygon : polygons)
        {
            for (const auto& point : polygon.points)
            {
                minX = std::min(minX, point.x);
                maxX = std::max(maxX, point.x);
                minY = std::min(minY, point.y);
                maxY = std::max(maxY, point.y);
            }
        }
        bool allInside = true;
        for (const auto& point : poly.points)
        {
            if (point.x < minX || point.x > maxX || point.y < minY || point.y > maxY)
            {
                allInside = false;
                break;
            }
        }
        std::cout << (allInside ? "<TRUE>" : "<FALSE>") << '\n';
    }
    catch (...)
    {
        std::cout << "<INVALID COMMAND>\n";
    }
}

bool doPolygonsIntersect(const Polygon& a, const Polygon& b)
{
    auto getBounds = [](const Polygon& p)
    {
        int minX = p.points[0].x, maxX = p.points[0].x;
        int minY = p.points[0].y, maxY = p.points[0].y;
        for (const auto& point : p.points)
        {
            minX = std::min(minX, point.x);
            maxX = std::max(maxX, point.x);
            minY = std::min(minY, point.y);
            maxY = std::max(maxY, point.y);
        }
        return std::make_tuple(minX, maxX, minY, maxY);
    };
    auto [aMinX, aMaxX, aMinY, aMaxY] = getBounds(a);
    auto [bMinX, bMaxX, bMinY, bMaxY] = getBounds(b);
    return !(aMaxX < bMinX || aMinX > bMaxX || aMaxY < bMinY || aMinY > bMaxY);
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
        Point p;
        char discard;
        std::cin >> discard;
        if (discard != '(')
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        for (size_t i = 0; i < vertexCount; ++i)
        {
            if (!(std::cin >> p.x >> discard >> p.y >> discard) || discard != ')')
            {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            poly.points.push_back(p);
            if (i != vertexCount - 1)
            {
                std::cin >> discard;
                if (discard != '(')
                {
                    std::cout << "<INVALID COMMAND>\n";
                    return;
                }
            }
        }

        if (poly.points.size() != vertexCount || !isPolygonValid(poly))
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        size_t count = std::count_if(polygons.begin(), polygons.end(),
            [&poly](const Polygon& p) { return doPolygonsIntersect(poly, p); });
        std::cout << count << '\n';
    }
    catch (...)
    {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void maxseqCommand(const std::vector<Polygon>& polygons, const std::string& arg)
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
        Point p;
        char discard;
        std::cin >> discard;
        if (discard != '(')
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        for (size_t i = 0; i < vertexCount; ++i)
        {
            if (!(std::cin >> p.x >> discard >> p.y >> discard) || discard != ')')
            {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            poly.points.push_back(p);
            if (i != vertexCount - 1)
            {
                std::cin >> discard;
                if (discard != '(')
                {
                    std::cout << "<INVALID COMMAND>\n";
                    return;
                }
            }
        }
        if (poly.points.size() != vertexCount || !isPolygonValid(poly))
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        size_t maxSeq = 0;
        size_t currentSeq = 0;
        for (const auto& polygon : polygons)
        {
            if (arePolygonsSame(polygon, poly))
            {
                currentSeq++;
                maxSeq = std::max(maxSeq, currentSeq);
            }
            else
            {
                currentSeq = 0;
            }
        }
        std::cout << maxSeq << '\n';
    }
    catch (...)
    {
        std::cout << "<INVALID COMMAND>\n";
    }
}

bool arePolygonsSame(const Polygon& a, const Polygon& b)
{
    if (a.points.size() != b.points.size()) return false;
    for (size_t i = 0; i < a.points.size(); ++i)
    {
        if (a.points[i] != b.points[i])
        {
            return false;
        }
    }
    return true;
}

void permsCommand(const std::vector<Polygon>& polygons, const std::string& arg)
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
        Point p;
        char discard;
        std::cin >> discard;
        if (discard != '(')
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        for (size_t i = 0; i < vertexCount; ++i) {
            if (!(std::cin >> p.x >> discard >> p.y >> discard) || discard != ')')
            {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            poly.points.push_back(p);
            if (i != vertexCount - 1)
            {
                std::cin >> discard;
                if (discard != '(')
                {
                    std::cout << "<INVALID COMMAND>\n";
                    return;
                }
            }
        }
        if (poly.points.size() != vertexCount || !isPolygonValid(poly))
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        size_t count = std::count_if(polygons.begin(), polygons.end(),
            [&poly](const Polygon& p) { return arePolygonsSame(p, poly); });
        std::cout << count << '\n';
    }
    catch (...)
    {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void rmechoCommand(std::vector<Polygon>& polygons, const std::string& arg)
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
        Point p;
        char discard;
        std::cin >> discard;
        if (discard != '(')
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        for (size_t i = 0; i < vertexCount; ++i)
        {
            if (!(std::cin >> p.x >> discard >> p.y >> discard) || discard != ')')
            {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            poly.points.push_back(p);
            if (i != vertexCount - 1)
            {
                std::cin >> discard;
                if (discard != '(')
                {
                    std::cout << "<INVALID COMMAND>\n";
                    return;
                }
            }
        }
        if (poly.points.size() != vertexCount || !isPolygonValid(poly))
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        auto it = std::remove_if(polygons.begin(), polygons.end(),
            [&poly](const Polygon& p) { return arePolygonsSame(p, poly); });
        size_t removed = std::distance(it, polygons.end());
        polygons.erase(it, polygons.end());
        std::cout << removed << '\n';
    }
    catch (...)
    {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void sameCommand(const std::vector<Polygon>& polygons, const std::string& arg)
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
        Point p;
        char discard;
        std::cin >> discard;
        if (discard != '(')
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        for (size_t i = 0; i < vertexCount; ++i)
        {
            if (!(std::cin >> p.x >> discard >> p.y >> discard) || discard != ')')
            {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            poly.points.push_back(p);
            if (i != vertexCount - 1)
            {
                std::cin >> discard;
                if (discard != '(')
                {
                    std::cout << "<INVALID COMMAND>\n";
                    return;
                }
            }
        }
        if (poly.points.size() != vertexCount || !isPolygonValid(poly))
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        size_t count = std::count_if(polygons.begin(), polygons.end(),
            [&poly](const Polygon& p)
            {
                if (p.points.size() != poly.points.size()) return false;
                return std::is_permutation(p.points.begin(), p.points.end(), poly.points.begin());
            });

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
            else if (command == "ECHO")
            {
                std::string arg;
                std::cin >> arg;
                echoCommand(polygons, arg);
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
            else if (command == "MAXSEQ")
            {
                std::string arg;
                std::cin >> arg;
                maxseqCommand(polygons, arg);
            }
            else if (command == "PERMS")
            {
                std::string arg;
                std::cin >> arg;
                permsCommand(polygons, arg);
            }
            else if (command == "RMECHO")
            {
                std::string arg;
                std::cin >> arg;
                rmechoCommand(polygons, arg);
            }
            else if (command == "SAME")
            {
                std::string arg;
                std::cin >> arg;
                sameCommand(polygons, arg);
            }
            else
            {
                std::cout << "<INVALID COMMAND>\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "<INVALID COMMAND>\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
