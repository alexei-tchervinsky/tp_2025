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
    double total = 0.0;
    for (const auto& poly : polygons)
    {
        total += calculateArea(poly);
    }
    return total;
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

void areaCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);
    if (arg == "EVEN") {
        auto sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double acc, const Polygon& p) {
                return acc + (p.points.size() % 2 == 0 ? calculateArea(p) : 0.0);
            });
        std::cout << sum << '\n';
    }
    else if (arg == "ODD") {
        auto sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double acc, const Polygon& p) {
                return acc + (p.points.size() % 2 != 0 ? calculateArea(p) : 0.0);
            });
        std::cout << sum << '\n';
    }
    else if (arg == "MEAN") {
        if (polygons.empty()) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        auto total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double acc, const Polygon& p) {
                return acc + calculateArea(p);
            });
        std::cout << total / polygons.size() << '\n';
    }
    else {
        try {
            size_t num = std::stoul(arg);
            if (num < 3) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            auto sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [num](double acc, const Polygon& p) {
                    return acc + (p.points.size() == num ? calculateArea(p) : 0.0);
                });
            std::cout << sum << '\n';
        }
        catch (...) {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

void maxCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);
    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    if (arg == "AREA") {
        auto maxIt = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return calculateArea(a) < calculateArea(b);
            });
        std::cout << calculateArea(*maxIt) << '\n';
    }
    else if (arg == "VERTEXES") {
        auto maxIt = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
            });
        std::cout << maxIt->points.size() << '\n';
    }
    else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void minCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);
    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    if (arg == "AREA") {
        auto minIt = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return calculateArea(a) < calculateArea(b);
            });
        std::cout << calculateArea(*minIt) << '\n';
    }
    else if (arg == "VERTEXES") {
        auto minIt = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
            });
        std::cout << minIt->points.size() << '\n';
    }
    else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void countCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
    if (arg == "EVEN") {
        auto count = std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) {
                return p.points.size() % 2 == 0;
            });
        std::cout << count << '\n';
    }
    else if (arg == "ODD") {
        auto count = std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) {
                return p.points.size() % 2 != 0;
            });
        std::cout << count << '\n';
    }
    else {
        try {
            size_t num = std::stoul(arg);
            if (num < 3) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            auto count = std::count_if(polygons.begin(), polygons.end(),
                [num](const Polygon& p) {
                    return p.points.size() == num;
                });
            std::cout << count << '\n';
        }
        catch (...) {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

void echoCommand(std::vector<Polygon>& polygons, const std::string& arg) {
    try {
        size_t vertexCount = std::stoul(arg);
        if (vertexCount < 3) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        Polygon poly;
        std::string pointStr;
        std::getline(std::cin >> std::ws, pointStr);
        std::istringstream pointStream(pointStr);
        Point p;
        char discard;
        bool valid = true;
        for (size_t i = 0; i < vertexCount && valid; ++i) {
            if (!(pointStream >> discard) || discard != '(' ||
                !(pointStream >> p.x) ||
                !(pointStream >> discard) || discard != ';' ||
                !(pointStream >> p.y) ||
                !(pointStream >> discard) || discard != ')') {
                valid = false;
            }
            poly.points.push_back(p);
        }

        if (!valid || poly.points.size() != vertexCount ||
            !isPolygonValid(poly) || pointStream.rdbuf()->in_avail() != 0) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        polygons.push_back(poly);
        std::cout << polygons.size() << '\n';
    }
    catch (...) {
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

void inframeCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
    if (polygons.empty()) {
        std::cout << "<FALSE>\n";
        return;
    }

    try {
        size_t vertexCount = std::stoul(arg);
        if (vertexCount < 3) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        Polygon poly;
        std::string pointStr;
        std::getline(std::cin >> std::ws, pointStr);
        std::istringstream pointStream(pointStr);
        Point p;
        char discard;
        bool valid = true;
        for (size_t i = 0; i < vertexCount && valid; ++i) {
            if (!(pointStream >> discard) || discard != '(' ||
                !(pointStream >> p.x) ||
                !(pointStream >> discard) || discard != ';' ||
                !(pointStream >> p.y) ||
                !(pointStream >> discard) || discard != ')') {
                valid = false;
            }
            poly.points.push_back(p);
        }

        if (!valid || poly.points.size() != vertexCount ||
            !isPolygonValid(poly) || pointStream.rdbuf()->in_avail() != 0) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        // Calculate frame using algorithms
        auto [minX, maxX] = std::minmax_element(
            polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                auto minA = std::min_element(a.points.begin(), a.points.end(),
                    [](const Point& p1, const Point& p2) { return p1.x < p2.x; });
                auto minB = std::min_element(b.points.begin(), b.points.end(),
                    [](const Point& p1, const Point& p2) { return p1.x < p2.x; });
                return minA->x < minB->x;
            });
        auto [minY, maxY] = std::minmax_element(
            polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                auto minA = std::min_element(a.points.begin(), a.points.end(),
                    [](const Point& p1, const Point& p2) { return p1.y < p2.y; });
                auto minB = std::min_element(b.points.begin(), b.points.end(),
                    [](const Point& p1, const Point& p2) { return p1.y < p2.y; });
                return minA->y < minB->y;
            });

        int frameMinX = std::min_element(minX->points.begin(), minX->points.end(),
            [](const Point& p1, const Point& p2) { return p1.x < p2.x; })->x;
        int frameMaxX = std::max_element(maxX->points.begin(), maxX->points.end(),
            [](const Point& p1, const Point& p2) { return p1.x < p2.x; })->x;
        int frameMinY = std::min_element(minY->points.begin(), minY->points.end(),
            [](const Point& p1, const Point& p2) { return p1.y < p2.y; })->y;
        int frameMaxY = std::max_element(maxY->points.begin(), maxY->points.end(),
            [](const Point& p1, const Point& p2) { return p1.y < p2.y; })->y;

        bool allInside = std::all_of(poly.points.begin(), poly.points.end(),
            [=](const Point& point) {
                return point.x >= frameMinX && point.x <= frameMaxX &&
                       point.y >= frameMinY && point.y <= frameMaxY;
            });
        std::cout << (allInside ? "<TRUE>" : "<FALSE>") << '\n';
    }
    catch (...) {
        std::cout << "<INVALID COMMAND>\n";
    }
}

bool doPolygonsIntersect(const Polygon& a, const Polygon& b) {
    int aMinX = a.points[0].x, aMaxX = a.points[0].x;
    int aMinY = a.points[0].y, aMaxY = a.points[0].y;
    for (const auto& point : a.points)
    {
        aMinX = std::min(aMinX, point.x);
        aMaxX = std::max(aMaxX, point.x);
        aMinY = std::min(aMinY, point.y);
        aMaxY = std::max(aMaxY, point.y);
    }
    int bMinX = b.points[0].x, bMaxX = b.points[0].x;
    int bMinY = b.points[0].y, bMaxY = b.points[0].y;
    for (const auto& point : b.points)
    {
        bMinX = std::min(bMinX, point.x);
        bMaxX = std::max(bMaxX, point.x);
        bMinY = std::min(bMinY, point.y);
        bMaxY = std::max(bMaxY, point.y);
    }
    return !(aMaxX < bMinX || aMinX > bMaxX || aMaxY < bMinY || aMinY > bMaxY);
}

void intersectionsCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    try {
        size_t vertexCount = std::stoul(arg);
        if (vertexCount < 3) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        Polygon poly;
        std::string pointStr;
        std::getline(std::cin >> std::ws, pointStr);
        std::istringstream pointStream(pointStr);
        Point p;
        char discard;
        bool valid = true;
        for (size_t i = 0; i < vertexCount && valid; ++i) {
            if (!(pointStream >> discard) || discard != '(' ||
                !(pointStream >> p.x) ||
                !(pointStream >> discard) || discard != ';' ||
                !(pointStream >> p.y) ||
                !(pointStream >> discard) || discard != ')') {
                valid = false;
            }
            poly.points.push_back(p);
        }

        if (!valid || poly.points.size() != vertexCount ||
            !isPolygonValid(poly) || pointStream.rdbuf()->in_avail() != 0) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        auto count = std::count_if(polygons.begin(), polygons.end(),
            [&poly](const Polygon& p) {
                return doPolygonsIntersect(poly, p);
            });
        std::cout << count << '\n';
    }
    catch (...) {
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
