#include "geometry.hpp"

bool isRectangle(const Polygon& polygon)
{
    if (polygon.points.size() != 3)
        return false;
    return true;
}

void Rects(const std::vector<Polygon>& polygons)
{
    std::size_t count = std::count_if(polygons.begin(), polygons.end(), isRectangle);
    std::cout << count << "\n";
}

#include "geometry.hpp"
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>

double computeArea(const Polygon& poly) {
    double area = 0.0;
    const auto& points = poly.points;
    size_t n = points.size();
    for (size_t i = 0; i < n; ++i)
    {
        size_t j = (i + 1) % n;
        area += static_cast<double>(points[i].x) * points[j].y -
                static_cast<double>(points[j].x) * points[i].y;
    }
    return std::abs(area) / 2.0;
}

void areaCommand(const std::vector<Polygon>& polygons, const std::string& arg)
{
    if (arg == "EVEN")
    {
        double sum = 0.0;
        for (const auto& poly : polygons)
        {
            if (poly.points.size() % 2 == 0)
            {
                sum += computeArea(poly);
            }
        }
        std::cout << std::fixed << std::setprecision(1) << sum << "\n";
    }
    else if (arg == "ODD")
    {
        double sum = 0.0;
        for (const auto& poly : polygons) {
            if (poly.points.size() % 2 == 1)
            {
                sum += computeArea(poly);
            }
        }
        std::cout << std::fixed << std::setprecision(1) << sum << "\n";
    }
    else if (arg == "MEAN")
    {
        if (polygons.empty())
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        double total = 0.0;
        for (const auto& poly : polygons)
        {
            total += computeArea(poly);
        }
        std::cout << std::fixed << std::setprecision(1) << total / polygons.size() << "\n";
    }
    else {
        try
        {
            size_t num = std::stoul(arg);
            if (num <= 2)
            {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            double sum = 0.0;
            for (const auto& poly : polygons)
            {
                if (poly.points.size() == num)
                {
                    sum += computeArea(poly);
                }
            }
            std::cout << std::fixed << std::setprecision(1) << sum << "\n";
        } catch (...) {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

void maxCommand(const std::vector<Polygon>& polygons, const std::string& arg)
{
    if (polygons.empty())
    {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    if (arg == "AREA")
    {
        double maxArea = computeArea(polygons[0]);
        for (const auto& poly : polygons) {
            double area = computeArea(poly);
            if (area > maxArea) maxArea = area;
        }
        std::cout << std::fixed << std::setprecision(1) << maxArea << "\n";
    }
    else if (arg == "VERTEXES")
    {
        size_t maxVert = polygons[0].points.size();
        for (const auto& poly : polygons) {
            size_t numVert = poly.points.size();
            if (numVert > maxVert) maxVert = numVert;
        }
        std::cout << maxVert << "\n";
    }
    else
    {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void minCommand(const std::vector<Polygon>& polygons, const std::string& arg)
{
    if (polygons.empty())
    {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    if (arg == "AREA")
    {
        double minArea = computeArea(polygons[0]);
        for (const auto& poly : polygons)
        {
            double area = computeArea(poly);
            if (area < minArea) minArea = area;
        }
        std::cout << std::fixed << std::setprecision(1) << minArea << "\n";
    }
    else if (arg == "VERTEXES")
    {
        size_t minVert = polygons[0].points.size();
        for (const auto& poly : polygons)
        {
            size_t numVert = poly.points.size();
            if (numVert < minVert) minVert = numVert;
        }
        std::cout << minVert << "\n";
    }
    else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void countOdd(const std::vector<Polygon>& polygons) {
    size_t count = 0;
    for (const auto& poly : polygons) {
        if (poly.points.size() % 2 == 1) {
            count++;
        }
    }
    std::cout << count << "\n";
}

void countEven(const std::vector<Polygon>& polygons) {
    size_t count = 0;
    for (const auto& poly : polygons) {
        if (poly.points.size() % 2 == 0) {
            count++;
        }
    }
    std::cout << count << "\n";
}

void countNum(const std::vector<Polygon>& polygons, int num) {
    size_t count = 0;
    for (const auto& poly : polygons) {
        if (static_cast<int>(poly.points.size()) == num) {
            count++;
        }
    }
    std::cout << count << "\n";
}
