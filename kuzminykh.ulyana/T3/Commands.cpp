#include "Commands.h"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>


namespace kuzminykh
{
    double calculateArea(const Polygon& polygon)
    {
        const auto& points = polygon.points;
        size_t n = points.size();
        return std::abs(std::accumulate(points.begin(), points.end(), 0.0,
            [n, &points, i = 0](double sum, const Point& p) mutable
            {
                size_t j = (i + 1) % n;
                sum += p.x * points[j].y - points[j].x * p.y;
                ++i;
                return sum;
            })) / 2.0;
    }

    void area(const std::vector<Polygon>& polygons, const std::string& subcmd)
    {
        if (subcmd == "EVEN" || subcmd == "ODD")
        {
            bool even = (subcmd == "EVEN");
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [even](double acc, const Polygon& p)
                {
                    return (p.points.size() % 2 == 0) == even ? acc + calculateArea(p) : acc;
                });
            std::cout << std::fixed << std::setprecision(1) << sum << std::endl;
        }
        else if (subcmd == "MEAN")
        {
            if (polygons.empty())
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }
            double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double acc, const Polygon& p) { return acc + calculateArea(p); });
            std::cout << std::fixed << std::setprecision(1) << total / polygons.size() << std::endl;
        }
        else
        {
            try
            {
                size_t n = std::stoul(subcmd);
                if (n < 3)
                    throw std::exception();

                double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                    [n](double acc, const Polygon& p)
                    {
                        return p.points.size() == n ? acc + calculateArea(p) : acc;
                    });
                std::cout << std::fixed << std::setprecision(1) << sum << std::endl;
            }
            catch (...)
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
    }

    void max(const std::vector<Polygon>& polygons, const std::string& subcmd)
    {
        if (polygons.empty())
        {
            std::cout << "<INVALID COMMAND>" << std::endl;
            return;
        }

        if (subcmd == "AREA")
        {
            auto it = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b)
                {
                    return calculateArea(a) < calculateArea(b);
                });
            std::cout << std::fixed << std::setprecision(1) << calculateArea(*it) << std::endl;
        }
        else if (subcmd == "VERTEXES")
        {
            auto it = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b)
                {
                    return a.points.size() < b.points.size();
                });
            std::cout << it->points.size() << std::endl;
        }
        else
        {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }

    void min(const std::vector<Polygon>& polygons, const std::string& subcmd)
    {
        if (polygons.empty())
        {
            std::cout << "<INVALID COMMAND>" << std::endl;
            return;
        }

        if (subcmd == "AREA")
        {
            auto it = std::min_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b)
                {
                    return calculateArea(a) < calculateArea(b);
                });
            std::cout << std::fixed << std::setprecision(1) << calculateArea(*it) << std::endl;
        }
        else if (subcmd == "VERTEXES")
        {
            auto it = std::min_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b)
                {
                    return a.points.size() < b.points.size();
                });
            std::cout << it->points.size() << std::endl;
        }
        else
        {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }

    void count(const std::vector<Polygon>& polygons, const std::string& subcmd)
    {
        if (subcmd == "EVEN" || subcmd == "ODD")
        {
            bool even = (subcmd == "EVEN");
            size_t cnt = std::count_if(polygons.begin(), polygons.end(),
                [even](const Polygon& p)
                {
                    return (p.points.size() % 2 == 0) == even;
                });
            std::cout << cnt << std::endl;
        }
        else
        {
            try
            {
                size_t n = std::stoul(subcmd);
                if (n < 3)
                    throw std::exception();

                size_t cnt = std::count_if(polygons.begin(), polygons.end(),
                    [n](const Polygon& p) { return p.points.size() == n; });
                std::cout << cnt << std::endl;
            }
            catch (...)
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
    }

    bool isPerm(const Polygon& p1, const Polygon& p2)
    {
        if (p1.points.size() != p2.points.size())
            return false;

        std::vector<Point> points1 = p1.points;
        std::vector<Point> points2 = p2.points;
        std::sort(points1.begin(), points1.end());
        std::sort(points2.begin(), points2.end());
        return points1 == points2;
    }

    void perms(const std::vector<Polygon>& polygons, std::stringstream& params)
    {
        std::string line;
        std::getline(params, line);
        line.erase(0, line.find_first_not_of(" \t"));

        try
        {
            Polygon p = parsePolygon(line);
            size_t cnt = std::count_if(polygons.begin(), polygons.end(),
                [&p](const Polygon& poly) { return isPerm(poly, p); });
            std::cout << cnt << std::endl;
        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }

    void inFrame(const std::vector<Polygon>& polygons, std::stringstream& params)
    {
        if (polygons.empty())
        {
            std::cout << "<FALSE>" << std::endl;
            return;
        }

        std::string line;
        std::getline(params, line);
        line.erase(0, line.find_first_not_of(" \t"));

        try
        {
            Polygon p = parsePolygon(line);

            int minX = polygons[0].points[0].x;
            int maxX = minX;
            int minY = polygons[0].points[0].y;
            int maxY = minY;

            for (const auto& poly : polygons)
            {
                for (const auto& point : poly.points)
                {
                    minX = std::min(minX, point.x);
                    maxX = std::max(maxX, point.x);
                    minY = std::min(minY, point.y);
                    maxY = std::max(maxY, point.y);
                }
            }

            bool inside = true;
            for (const auto& point : p.points)
            {
                if (point.x < minX || point.x > maxX ||
                    point.y < minY || point.y > maxY)
                {
                    inside = false;
                    break;
                }
            }

            std::cout << (inside ? "<TRUE>" : "<FALSE>") << std::endl;
        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }

    void handleAreaCommand(const std::vector<Polygon>& polygons, std::stringstream& ss)
    {
        std::string subcmd;
        ss >> subcmd;
        area(polygons, subcmd);
    }

    void handleMaxCommand(const std::vector<Polygon>& polygons, std::stringstream& ss)
    {
        std::string subcmd;
        ss >> subcmd;
        max(polygons, subcmd);
    }

    void handleMinCommand(const std::vector<Polygon>& polygons, std::stringstream& ss)
    {
        std::string subcmd;
        ss >> subcmd;
        min(polygons, subcmd);
    }

    void handleCountCommand(const std::vector<Polygon>& polygons, std::stringstream& ss)
    {
        std::string subcmd;
        ss >> subcmd;
        count(polygons, subcmd);
    }

    void handlePermsCommand(const std::vector<Polygon>& polygons, std::stringstream& ss)
    {
        perms(polygons, ss);
    }

    void handleInFrameCommand(const std::vector<Polygon>& polygons, std::stringstream& ss)
    {
        inFrame(polygons, ss);
    }

    std::map<std::string, std::function<void(const std::vector<Polygon>&, std::stringstream&)>> createCommandMap()
    {
        return {
            {"AREA", handleAreaCommand},
            {"MAX", handleMaxCommand},
            {"MIN", handleMinCommand},
            {"COUNT", handleCountCommand},
            {"PERMS", handlePermsCommand},
            {"INFRAME", handleInFrameCommand}
        };
    }
}
