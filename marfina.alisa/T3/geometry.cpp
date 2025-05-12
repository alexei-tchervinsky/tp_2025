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

bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Point& lhs, const Point& rhs)
{
    return !(lhs == rhs);
}

double calculateArea(const Polygon& polygon)
{
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
        [](double sum, const Polygon& poly) { return sum + calculateArea(poly); });
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
            if (poly.points.size() == vertexCount)
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
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [num](double s, const Polygon& p)
                {
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


void maxCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
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
    if (arg == "EVEN")
    {
        size_t count = std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p)
            { return p.points.size() % 2 == 0; });
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

void processCommands(const std::vector<Polygon>& polygons)
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
}
