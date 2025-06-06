#include "Comands.h"
#include <numeric>
#include <iomanip>

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
    void area (std::vector<Polygon> polygon, std::string& parameter)
    {
        double area {0.0};
        if (parameter == "EVEN")
        {
            std::accumulate(polygon.begin(), polygon.end(), area,
                            [](const double sum, const Polygon& p)
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
            std::accumulate(polygon.begin(), polygon.end(), area,
                            [](const double sum, const Polygon& p)
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
            std::accumulate(polygon.begin(), polygon.end(), area,
                            [](const double sum, Polygon& p)
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
                size_t number_of_vertexes = std::stol(parameter);
                if (number_of_vertexes < 3)
                {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    return;
                }
                std::accumulate(polygon.begin(), polygon.end(), area,
                                [&number_of_vertexes](const double sum, const Polygon& p)
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
    void max (std::vector<Polygon> polygon, std::string& parameter)
    {
        if (parameter == "AREA")
        {
            auto maxAreaIt = std::max_element(polygon.begin(), polygon.end(),
                                              [](Polygon& p1, Polygon& p2)
                                              {
                                                  return calculateArea(p1) > calculateArea(p2);
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
    void min (std::vector<Polygon> polygon, std::string& parameter)
    {
        if (parameter == "AREA")
        {
            auto minAreaIt = std::min_element(polygon.begin(), polygon.end(),
                                              [](Polygon& p1, Polygon& p2)
                                              {
                                                  return calculateArea(p1) < calculateArea(p2);
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
    void count (std::vector<Polygon> polygon, std::string& parameter)
    {
        size_t nFigures;
        if (parameter == "EVEN")
        {
            std::accumulate(polygon.begin(), polygon.end(), nFigures,
                            [](size_t sum, const Polygon& p)
                            {
                                if (p.points.size() % 2)
                                {
                                    return ++ sum;
                                }
                                return sum;
                            });
            std::cout << std::fixed << std::setprecision(1) << nFigures << std::endl;
        }
        else if (parameter == "ODD")
        {
            std::accumulate(polygon.begin(), polygon.end(), nFigures,
                            [](size_t sum, const Polygon& p)
                            {
                                if (!(p.points.size() % 2))
                                {
                                    return ++ sum;
                                }
                                return sum;
                            });
            std::cout << std::fixed << std::setprecision(1) << nFigures << std::endl;
        }
        else
        {
            size_t nVertex = std::stol(parameter);
            std::accumulate(polygon.begin(), polygon.end(), nFigures,
                            [nVertex](size_t sum, const Polygon& p)
                            {
                                if (p.points.size() == nVertex)
                                {
                                    return ++ sum;
                                }
                                return sum;
                            });
            std::cout << std::fixed << std::setprecision(1) << nFigures << std::endl;
        }
    }
    size_t echo (std::vector<Polygon>& polygon, const Polygon& figure)
    {
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

        while ((it = std::find_if(it, polygon.end(),
                                  [&figure, &isEqual](const Polygon& p)
                                  {
                                      return isEqual(p, figure);
                                  }
        )) != polygon.end())
        {
            it = polygon.insert(it + 1, *it);
            countFigure++;
            it += 2; // чтобы пропустить копию
        }
        return countFigure;
    }
    bool inframe (std::vector<Polygon>& polygon, const Polygon& figure)
    {
        if (polygon.empty() || figure.points.empty()) return false;

        auto [minX, maxX, minY, maxY] = std::accumulate(polygon.begin(), polygon.end(),
                                                        std::make_tuple(
                                                                std::numeric_limits<int>::max(),
                                                                std::numeric_limits<int>::min(),
                                                                std::numeric_limits<int>::max(),
                                                                std::numeric_limits<int>::min()
                                                        ),
                                                        [](auto acc, const Polygon& poly) {
                                                            auto [currentMinX, currentMaxX, currentMinY, currentMaxY] = acc;

                                                            for (const auto& point : poly.points) {
                                                                currentMinX = std::min(currentMinX, point.x);
                                                                currentMaxX = std::max(currentMaxX, point.x);
                                                                currentMinY = std::min(currentMinY, point.y);
                                                                currentMaxY = std::max(currentMaxY, point.y);
                                                            }

                                                            return std::make_tuple(currentMinX, currentMaxX, currentMinY, currentMaxY);
                                                        }
        );

        return std::all_of(figure.points.begin(), figure.points.end(),
                           [minX, maxX, minY, maxY](const Point& p) {
                               return p.x >= minX && p.x <= maxX &&
                                      p.y >= minY && p.y <= maxY;
                           }
        );
    }
}


