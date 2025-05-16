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
            if (polygons.empty()) throw std::invalid_argument("");
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double s, const nspace::Polygon& p) { return s + p.area(); });
            std::cout << sum / polygons.size() << '\n';
        }
        else
        {
            size_t num = std::stoul(param);
            auto pred = [num](const nspace::Polygon& p) { return p.points.size() == num; };
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, makeAreaAccumulator(pred));
            std::cout << sum << '\n';
        }
    }

    void max(const std::vector<Polygon>& polygons, const std::string& param)
    {
        if (polygons.empty()) throw std::invalid_argument("");

        if (param == "AREA")
        {
            auto it = std::max_element(polygons.begin(), polygons.end(), AreaComparator{});
            std::cout << it->area() << '\n';
        }
        else if (param == "VERTEXES")
        {
            auto it = std::max_element(polygons.begin(), polygons.end(), VertexCountComparator{});
            std::cout << it->points.size() << '\n';
        }
        else
        {
            throw std::invalid_argument("");
        }
    }

    void min(const std::vector<Polygon>& polygons, const std::string& param)
    {
        if (polygons.empty()) throw std::invalid_argument("");

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
            throw std::invalid_argument("");
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
                auto pred = [num](const Polygon& p)
                {
                    return p.points.size() == num;
                };
                size_t cnt = std::count_if(polygons.begin(), polygons.end(), pred);
                std::cout << cnt << '\n';
            }
            catch(...)
            {
                throw std::invalid_argument("");
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
        if (polygons.empty())
        {
            std::cout << "0\n";
            return;
        }

        std::vector<bool> matches;
        std::transform(polygons.begin(), polygons.end(), std::back_inserter(matches),
                        [&target](const Polygon& p) {return p == target;});
        size_t max_count = 0;
        auto it = matches.begin();
        while (it != matches.end())
        {
            it = std::find(it, matches.end(), true);
            if (it == matches.end()) break;
            auto end_it = std::find(it, matches.end(), false);
            max_count = std::max(max_count, static_cast<size_t>(std::distance(it, end_it)));
            it = end_it;
        }
        std::cout << max_count << '\n';
    }
}
