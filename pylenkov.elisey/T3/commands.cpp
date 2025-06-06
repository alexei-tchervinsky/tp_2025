#include "commands.hpp"
#include "DataStruct.hpp"
#include "iofmtguard.hpp"
#include <iomanip>
#include <stdexcept>
#include <numeric>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

namespace nspace
{
    auto makeAreaAccumulator = [](auto predicate)
    {
        return [=](double sum, const Polygon& p)
        {
            return predicate(p) ? sum + p.area() : sum;
        };
    };

    auto makeCounter = [](auto predicate)
    {
        return [=](size_t counter, const Polygon& p)
        {
            return predicate(p) ? counter + 1 : counter;
        };
    };

    void area(const std::vector<nspace::Polygon>& polygons, const std::string& param)
    {
        nspace::iofmtguard fmtguard(std::cout);
        std::cout << std::fixed << std::setprecision(1);

        if (param == "EVEN" || param == "ODD")
        {
            auto pred = (param == "EVEN")
                ? [](const nspace::Polygon& p) { return p.points.size() % 2 == 0; }
                : [](const nspace::Polygon& p) { return p.points.size() % 2 != 0; };

            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, makeAreaAccumulator(pred));
            std::cout << sum << '\n';
        }
        else if (param == "MEAN")
        {
            if (polygons.empty())
            {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double s, const nspace::Polygon& p) { return s + p.area(); });
            std::cout << sum / polygons.size() << '\n';
        }
        else
        {
            size_t num = std::stoul(param);
            auto pred = [num](const nspace::Polygon& p) { return p.points.size() == num; };
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, makeAreaAccumulator(pred));
            if (sum == 0.0)
            {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            std::cout << sum << '\n';
        }
    }

    void max(const std::vector<Polygon>& polygons, const std::string& param)
    {
        if (polygons.empty())
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        if (param == "AREA")
        {
            auto it = std::max_element(polygons.begin(), polygons.end(), AreaComparator{});
            std::cout << std::fixed << std::setprecision(1) << it->area() << '\n';
        }
        else if (param == "VERTEXES")
        {
            auto it = std::max_element(polygons.begin(), polygons.end(), VertexCountComparator{});
            std::cout << it->points.size() << '\n';
        }
        else
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
    }

    void min(const std::vector<Polygon>& polygons, const std::string& param)
    {
        if (polygons.empty())
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        if (param == "AREA")
        {
            auto it = std::min_element(polygons.begin(), polygons.end(), AreaComparator{});
            std::cout << it->points.size() << '\n';
        }
        else if (param == "VERTEXES")
        {
            auto it = std::max_element(polygons.begin(), polygons.end(), VertexCountComparator{});
            std::cout << it->points.size() << '\n';
        }
        else
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
    }

   void count(const std::vector<Polygon>& polygons, const std::string& param)
    {
        if (param == "EVEN")
        {
            auto pred = [](const Polygon& p)
            {
                return p.points.size() % 2 == 0;
            };
            size_t cnt = std::count_if(polygons.begin(), polygons.end(), pred);
            std::cout << cnt << '\n';
        }
        else if (param == "ODD")
        {
            auto pred = [](const Polygon& p)
            {
                return p.points.size() % 2 != 0;
            };
            size_t cnt = std::count_if(polygons.begin(), polygons.end(), pred);
            std::cout << cnt << '\n';
        }
        else
        {
            try
            {
                size_t num = std::stoul(param);
                if (num < 3)
                {
                    std::cout << "<INVALID COMMAND>\n";
                    return;
                }
                auto pred = [num](const Polygon& p)
                {
                    return p.points.size() == num;
                };
                size_t cnt = std::count_if(polygons.begin(), polygons.end(), pred);
                std::cout << cnt << '\n';
            }
            catch(...)
            {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
        }
    }

void echo(std::vector<Polygon>& polygons, const Polygon& target, const std::string& filename)
{
    std::vector<Polygon> temp;
    temp.reserve(polygons.size() * 2);

    std::transform(polygons.begin(), polygons.end(), \
                  std::back_inserter(temp),
                  [&target](const Polygon& poly)
                  {
                      return poly;
                  });

    std::copy_if(polygons.begin(), polygons.end(),
                std::back_inserter(temp),
                [&target](const Polygon& poly)
                {
                    return poly == target;
                });

    size_t count = temp.size() - polygons.size();

    if (count == 0)
    {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    polygons = std::move(temp);

    std::ofstream out(filename);
    if (!out)
    {
        std::cerr << "Error: Cannot open file for writing\n";
        return;
    }

    std::copy(polygons.begin(), polygons.end(),
             std::ostream_iterator<Polygon>(out, "\n"));

    std::cout << count << '\n';
}

    void maxSeq(const std::vector<Polygon>& polygons, const Polygon& target)
    {
        if (polygons.empty() || target.points.size() < 3)
        {
            throw std::invalid_argument("");
        }

        std::vector<bool> matches;
        std::transform(polygons.begin(), polygons.end(), std::back_inserter(matches),
                        [&target](const Polygon& p) { return p == target; });

        size_t max_count = 0;
        auto it_match = matches.begin();

        // Проходим по всем возможным подряд идущим элементам, чтобы найти максимальную длину
        while (it_match != matches.end())
        {
            it_match = std::find(it_match, matches.end(), true);  // Поиск начала последовательности
            if (it_match == matches.end()) break;  // Если не найдено, завершаем цикл

            auto end_it = std::find(it_match, matches.end(), false);  // Поиск конца последовательности
            max_count = std::max(max_count, static_cast<size_t>(std::distance(it_match, end_it)));  // Обновляем максимальную длину последовательности
            it_match = end_it;  // Продолжаем с конца найденной последовательности
        }

        // Если длина последовательности 0, то выводим ошибку
        if (max_count == 0)
        {
            throw std::invalid_argument("");
        }

        std::cout << max_count << '\n';
    }

}
