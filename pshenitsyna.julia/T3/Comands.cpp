#include "Comands.h"
#include <numeric>
#include <iomanip>
#include <tuple>
#include <limits>
#include <algorithm>

namespace wheatman
{
    double calculateArea(const Polygon& polygon)
    {
        std::vector<Point> points = polygon.points;
        size_t n = points.size();
        return std::abs(std::accumulate(points.begin(),points.end(),0,
                                        [n, &points, i = 0](double sum, const Point& p) mutable
                                        {
                                            size_t j = (i + 1) % n; // следующая точка
                                            sum += p.x * points[j].y - points[j].x * p.y; // добавляем к сумме по ф-ле Гаусса
                                            ++i;
                                            return sum;
                                        }
        )) / 2.0; // деление на 2 так как по ф-ле Гаусса получаем удвоенную площадь
    }
    void area (std::vector<Polygon>& polygon, std::string& parameter)
    {
        double area {0.0};
        if (parameter == "EVEN")
        {
            area = std::accumulate(polygon.begin(), polygon.end(), 0.0,
                            [](double sum, const Polygon& p)
                            {
                                if (p.points.size() % 2)
                                {
                                    return sum + calculateArea(p);
                                }
                                return sum;
                            });
            std::cout << std::fixed << std::setprecision(1) << area << std::endl;
        }
        else if (parameter == "ODD")
        {
           area = std::accumulate(polygon.begin(), polygon.end(), 0.0,
                            [](double sum, const Polygon& p)
                            {
                                if (!(p.points.size() % 2))
                                {
                                    return sum + calculateArea(p);
                                }
                                return sum;
                            });
            std::cout << std::fixed << std::setprecision(1) << area << std::endl;
        }
        else if (parameter == "MEAN")
        {
            if(polygon.empty()) std::cout << "<INVALID COMMAND>" << std::endl;
            area = std::accumulate(polygon.begin(), polygon.end(), 0.0,
                            [](double sum, Polygon& p)
                            {
                                return sum + calculateArea(p);
                            }
            );
            double midArea = area/(polygon.size());
            std::cout << std::fixed << std::setprecision(1) << midArea << std::endl;
        }
        else
        {
            try
            {
                size_t number_of_vertexes = std::stoul(parameter);
                if (number_of_vertexes < 3)
                {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    return;
                }
                area = std::accumulate(polygon.begin(), polygon.end(), 0.0,
                                [&number_of_vertexes](double sum, const Polygon& p)
                                {
                                    if (!(p.points.size() == number_of_vertexes))
                                    {
                                        return sum + calculateArea(p);
                                    }
                                    return sum;
                                });
                std::cout << std::fixed << std::setprecision(1) << area << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }

    }
    void max (std::vector<Polygon>& polygon, std::string& parameter)
    {
        if (polygon.empty())
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        if (parameter == "AREA")
        {
            auto maxAreaIt = std::max_element(polygon.begin(), polygon.end(),
                                              [](Polygon& p1, Polygon& p2)
                                              {
                                                  return calculateArea(p1) < calculateArea(p2);
                                              });
            double maxArea = calculateArea(*maxAreaIt);
            std::cout << std::fixed << std::setprecision(1) << maxArea << std::endl;
        }
        if (parameter == "VERTEXES")
        {
            auto nVertexes = std::max_element(polygon.begin(), polygon.end(),
                                              [](Polygon& p1, Polygon& p2)
                                              {
                                                  return p1.points.size() > p2.points.size();
                                              });
            double maxVertex = nVertexes->points.size();
            std::cout << maxVertex << std::endl;
        }
    }
    void min (std::vector<Polygon>& polygon, std::string& parameter)
    {
        if (polygon.empty())
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        if (parameter == "AREA")
        {
            auto minAreaIt = std::min_element(polygon.begin(), polygon.end(),
                                              [](Polygon& p1, Polygon& p2)
                                              {
                                                  return calculateArea(p1) > calculateArea(p2);
                                              });
            double minArea = calculateArea(*minAreaIt);
            std::cout << std::fixed << std::setprecision(1) << minArea << std::endl;
        }
        if (parameter == "VERTEXES")
        {
            auto nVertexes = std::min_element(polygon.begin(), polygon.end(),
                                              [](Polygon& p1, Polygon& p2)
                                              {
                                                  return p1.points.size() < p2.points.size();
                                              });
            double minVertex = nVertexes->points.size();
            std::cout << minVertex << std::endl;
        }
    }
    void count (std::vector<Polygon>& polygon, std::string& parameter)
    {
        size_t nFigures {0};
        if (parameter == "EVEN")
        {
            nFigures = std::count_if(polygon.begin(), polygon.end(),
                                     [](const Polygon& p)
                                     {return p.points.size()%2 == 0;});
            std::cout << nFigures << std::endl;
        }
        else if (parameter == "ODD")
        {
            nFigures = std::count_if(polygon.begin(), polygon.end(),
                                     [](const Polygon& p)
                                     {return p.points.size()%2 != 0;});
            std::cout << nFigures << std::endl;
        }
        else
        {
            try
            {
                size_t nVertex = std::stoul(parameter);
                if (nVertex < 3) {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    return;
                }
                nFigures = std::count_if(polygon.begin(), polygon.end(),
                                         [&nVertex](const Polygon& p)
                                         {return p.points.size() == nVertex;});
                std::cout << nFigures << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
    }
    size_t echo (std::vector<Polygon>& polygon, const Polygon& figure)
    {
        if (figure.points.empty()) return 0;
        auto isEqual = [](const Polygon& p1, const Polygon& p2)
        {
            if (p1.points.size() != p2.points.size()) return false;
            return  std::equal(p1.points.begin(), p1.points.end(),
                               p2.points.begin(), p2.points.end(),
                               [](const Point& a, const Point& b)
                               {return a.x == b.x && a.y == b.y;}
            );
        };
        size_t countFigure = 0;
        auto it = polygon.begin();

        while (it != polygon.end())
        {
            it = std::find_if(it, polygon.end(),
                               [&figure, &isEqual](const Polygon& p)
                               {
                                   return isEqual(p, figure);
                               });
            if (it != polygon.end())
            {
                it = polygon.insert(it + 1, *it);
                countFigure++;
                it += 2; // чтобы пропустить копию
            }
        }
        std::cout << countFigure << "\n";
        return countFigure;
    }
    bool inframe (std::vector<Polygon>& polygon, const Polygon& figure)
    {
        if (polygon.empty() || figure.points.empty())
        {
            std::cout << "INVALID COMMAND\n";
            return false;
        }

        int minX = std::numeric_limits<int>::max();
        int maxX = std::numeric_limits<int>::min();
        int minY = std::numeric_limits<int>::max();
        int maxY = std::numeric_limits<int>::min();

        for (const auto& poly : polygon) {
            for (const auto& point : poly.points) {
                minX = std::min(minX, point.x);
                maxX = std::max(maxX, point.x);
                minY = std::min(minY, point.y);
                maxY = std::max(maxY, point.y);
            }
        }
        for (const auto& point : figure.points) {
            if (point.x < minX || point.x > maxX ||
                point.y < minY || point.y > maxY) {
                std::cout << "<FALSE>\n";
                return false;
            }
        }
        std::cout << "<TRUE>\n";
        return true;
    }
}
