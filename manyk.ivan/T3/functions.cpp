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
        double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double current_sum, const Polygon& poly) {
                if (poly.points.size() % 2 == 0) {
                    return current_sum + computeArea(poly);
                }
                return current_sum;
            });
        std::cout << std::fixed << std::setprecision(1) << sum << "\n";
    }
    else if (arg == "ODD")
    {
        double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double current_sum, const Polygon& poly) {
                if (poly.points.size() % 2 == 1) {
                    return current_sum + computeArea(poly);
                }
                return current_sum;
            });
        std::cout << std::fixed << std::setprecision(1) << sum << "\n";
    }
    else if (arg == "MEAN")
    {
        if (polygons.empty())
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double current_sum, const Polygon& poly) {
                if (poly.points.size() % 2 == 1) {
                    return current_sum + computeArea(poly);
                }
                return current_sum;
            });
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
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [num](double current_sum, const Polygon& poly) {
                    if (poly.points.size() == num){
                        return current_sum + computeArea(poly);
                    }
                    return current_sum;
            });
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
        auto max_it = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return computeArea(a) < computeArea(b);
            });
        std::cout << std::fixed << std::setprecision(1) << computeArea(*max_it) << "\n";
    }
    else if (arg == "VERTEXES")
    {
        auto max_it = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
            });
        std::cout << max_it->points.size() << "\n";
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
        auto min_it = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return computeArea(a) < computeArea(b);
            });
        std::cout << std::fixed << std::setprecision(1) << computeArea(*min_it) << "\n";
    }
    else if (arg == "VERTEXES")
    {
        auto min_it = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
            });
        std::cout << min_it->points.size() << "\n";
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
    if (num <= 2)
    {
        return;
    }
    count = std::count_if(polygons.begin(), polygons.end(), [num](const Polygon& poly) {
        return static_cast<int>(poly.points.size()) == num;
    });
    std::cout << count << "\n";
}
