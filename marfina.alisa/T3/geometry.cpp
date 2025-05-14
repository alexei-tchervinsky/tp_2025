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

void areaCommand(const std::vector<Polygon>& polygons, const std::string& arg)
{
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);
    if (arg == "EVEN")
    {
        double sum = 0.0;
        for (const auto& p : polygons)
        {
            if (p.points.size() % 2 == 0)
            {
                sum += calculateArea(p);
            }
        }
        std::cout << sum << '\n';
    }
    else if (arg == "ODD")
    {
        double sum = 0.0;
        for (const auto& p : polygons)
        {
            if (p.points.size() % 2 != 0)
            {
                sum += calculateArea(p);
            }
        }
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
            double sum = 0.0;
            for (const auto& p : polygons)
            {
                if (p.points.size() == num)
                {
                    sum += calculateArea(p);
                }
            }
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
        auto maxIt = polygons.begin();
        double maxArea = calculateArea(*maxIt);
        for (auto it = polygons.begin(); it != polygons.end(); ++it)
        {
            double area = calculateArea(*it);
            if (area > maxArea)
            {
                maxArea = area;
                maxIt = it;
            }
        }
        std::cout << maxArea << '\n';
    }
    else if (arg == "VERTEXES")
    {
        auto maxIt = polygons.begin();
        size_t maxVert = maxIt->points.size();
        for (auto it = polygons.begin(); it != polygons.end(); ++it)
        {
            size_t vert = it->points.size();
            if (vert > maxVert)
            {
                maxVert = vert;
                maxIt = it;
            }
        }
        std::cout << maxVert << '\n';
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
        auto minIt = polygons.begin();
        double minArea = calculateArea(*minIt);
        for (auto it = polygons.begin(); it != polygons.end(); ++it)
        {
            double area = calculateArea(*it);
            if (area < minArea)
            {
                minArea = area;
                minIt = it;
            }
        }
        std::cout << minArea << '\n';
    }
    else if (arg == "VERTEXES")
    {
        auto minIt = polygons.begin();
        size_t minVert = minIt->points.size();
        for (auto it = polygons.begin(); it != polygons.end(); ++it)
        {
            size_t vert = it->points.size();
            if (vert < minVert)
            {
                minVert = vert;
                minIt = it;
            }
        }
        std::cout << minVert << '\n';
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
        size_t count = 0;
        for (const auto& p : polygons)
        {
            if (p.points.size() % 2 == 0)
            {
                ++count;
            }
        }
        std::cout << count << '\n';
    }
    else if (arg == "ODD")
    {
        size_t count = 0;
        for (const auto& p : polygons)
        {
            if (p.points.size() % 2 != 0)
            {
                ++count;
            }
        }
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
            size_t count = 0;
            for (const auto& p : polygons)
            {
                if (p.points.size() == num)
                {
                    ++count;
                }
            }
            std::cout << count << '\n';
        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

void echoCommand(std::vector<Polygon>& polygons, const std::string& arg) {
    try {
        size_t vertexCount = std::stoul(arg);
        if (vertexCount < 3) {
            throw std::invalid_argument("INVALID COMMAND");
        }
        Polygon poly;
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        char discard;
        for (size_t i = 0; i < vertexCount; ++i) {
            if (!(iss >> discard >> poly.points[i].x >> discard >> poly.points[i].y >> discard)) {
                throw std::invalid_argument("INVALID COMMAND");
            }
        }
        if (poly.points.size() != vertexCount || !isPolygonValid(poly)) {
            throw std::invalid_argument("INVALID COMMAND");
        }
        polygons.push_back(poly);
        size_t count = std::count(polygons.begin(), polygons.end(), poly);
        std::cout << count << '\n';
    }
    catch (...) {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void inframeCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    try {
        size_t vertexCount = std::stoul(arg);
        if (vertexCount < 3) {
            throw std::invalid_argument("INVALID COMMAND");
        }
        Polygon poly;
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        char discard;
        for (size_t i = 0; i < vertexCount; ++i) {
            if (!(iss >> discard >> poly.points[i].x >> discard >> poly.points[i].y >> discard)) {
                throw std::invalid_argument("INVALID COMMAND");
            }
        }
        if (poly.points.size() != vertexCount || !isPolygonValid(poly)) {
            throw std::invalid_argument("INVALID COMMAND");
        }
        int minX = polygons[0].points[0].x;
        int maxX = polygons[0].points[0].x;
        int minY = polygons[0].points[0].y;
        int maxY = polygons[0].points[0].y;
        for (const auto& polygon : polygons) {
            for (const auto& point : polygon.points) {
                minX = std::min(minX, point.x);
                maxX = std::max(maxX, point.x);
                minY = std::min(minY, point.y);
                maxY = std::max(maxY, point.y);
            }
        }
        bool allInside = true;
        for (const auto& point : poly.points) {
            if (point.x < minX || point.x > maxX || point.y < minY || point.y > maxY) {
                allInside = false;
                break;
            }
        }
        std::cout << (allInside ? "<TRUE>" : "<FALSE>") << '\n';
    }
    catch (...) {
        std::cout << "<INVALID COMMAND>\n";
    }
}

bool doPolygonsIntersect(const Polygon& a, const Polygon& b) {
    auto getBoundingBox = [](const Polygon& poly) {
        int minX = poly.points[0].x, maxX = poly.points[0].x;
        int minY = poly.points[0].y, maxY = poly.points[0].y;
        for (const auto& p : poly.points) {
            minX = std::min(minX, p.x);
            maxX = std::max(maxX, p.x);
            minY = std::min(minY, p.y);
            maxY = std::max(maxY, p.y);
        }
        return std::make_tuple(minX, maxX, minY, maxY);
    };
    auto [aMinX, aMaxX, aMinY, aMaxY] = getBoundingBox(a);
    auto [bMinX, bMaxX, bMinY, bMaxY] = getBoundingBox(b);
    if (aMaxX < bMinX || aMinX > bMaxX || aMaxY < bMinY || aMinY > bMaxY) {
        return false;
    }
    return true;
}

void intersectionsCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    try {
        size_t vertexCount = std::stoul(arg);
        if (vertexCount < 3) {
            throw std::invalid_argument("INVALID COMMAND");
        }
        Polygon poly;
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        char discard;
        for (size_t i = 0; i < vertexCount; ++i) {
            if (!(iss >> discard >> poly.points[i].x >> discard >> poly.points[i].y >> discard)) {
                throw std::invalid_argument("INVALID COMMAND");
            }
        }
        if (poly.points.size() != vertexCount || !isPolygonValid(poly)) {
            throw std::invalid_argument("INVALID COMMAND");
        }
        size_t count = 0;
        for (const auto& existingPoly : polygons) {
            if (doPolygonsIntersect(poly, existingPoly)) {
                ++count;
            }
        }
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
        catch (...)
        {
            std::cout << "<INVALID COMMAND>\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
