#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <functional>
#include "commands.h"
#include "polygon.h"
#include "iofmtguard.h"
#include <algorithm>
#include <numeric>
#include <iomanip>

namespace {
    void printArea(double value) {
        koshelev::iofmtguard guard(std::cout);
        std::cout << std::fixed << std::setprecision(1) << value << '\n';
    }

    template <typename Pred>
    double accumulateArea(const std::vector<Polygon>& polygons, Pred pred) {
        return std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [&pred](double acc, const Polygon& p) {
                return acc + (pred(p) ? p.area() : 0.0);
            });
    }

    template <typename Pred>
    size_t countIf(const std::vector<Polygon>& polygons, Pred pred) {
        return std::count_if(polygons.begin(), polygons.end(), pred);
    }

    std::map<std::string, std::function<double(const Polygon&)>> areaFilters = {
        {"EVEN", [](const Polygon& p) { return p.vertexCount() % 2 == 0; }},
        {"ODD", [](const Polygon& p) { return p.vertexCount() % 2 == 1; }},
        {"MEAN", [](const Polygon&) { return true; }}
    };

    std::map<std::string, std::function<bool(const Polygon&, const Polygon&)>> comparisonFuncs = {
        {"AREA", [](const Polygon& a, const Polygon& b) { return a.area() < b.area(); }},
        {"VERTEXES", [](const Polygon& a, const Polygon& b) { return a.vertexCount() < b.vertexCount(); }}
    };

    std::map<std::string, std::function<size_t(const Polygon&)>> countFilters = {
        {"EVEN", [](const Polygon& p) { return p.vertexCount() % 2 == 0; }},
        {"ODD", [](const Polygon& p) { return p.vertexCount() % 2 == 1; }}
    };

    std::map<std::string, std::function<void(const std::vector<Polygon>&)>> commandMap = {
        {"AREA", [](const std::vector<Polygon>& polygons) {
            std::string arg;
            std::cin >> arg;
            printArea(areaFilters.contains(arg)
                ? accumulateArea(polygons, areaFilters.at(arg)) / (arg == "MEAN" ? polygons.size() : 1)
                : accumulateArea(polygons, [num = std::stoul(arg)](const Polygon& p) { return p.vertexCount() == num; }));
        }},
        {"MAX", [](const std::vector<Polygon>& polygons) {
            std::string arg;
            std::cin >> arg;
            auto it = std::max_element(polygons.begin(), polygons.end(), comparisonFuncs.at(arg));
            std::cout << std::fixed << std::setprecision(1) << (arg == "AREA" ? it->area() : it->vertexCount()) << '\n';
        }},
        {"MIN", [](const std::vector<Polygon>& polygons) {
            std::string arg;
            std::cin >> arg;
            auto it = std::min_element(polygons.begin(), polygons.end(), comparisonFuncs.at(arg));
            std::cout << std::fixed << std::setprecision(1) << (arg == "AREA" ? it->area() : it->vertexCount()) << '\n';
        }},
        {"COUNT", [](const std::vector<Polygon>& polygons) {
            std::string arg;
            std::cin >> arg;
            std::cout << (countFilters.contains(arg)
                ? countIf(polygons, countFilters.at(arg))
                : countIf(polygons, [num = std::stoul(arg)](const Polygon& p) { return p.vertexCount() == num; })) << '\n';
        }},
        {"PERMS", [](const std::vector<Polygon>& polygons) {
            Polygon pattern;
            std::cin >> pattern;
            std::cout << countIf(polygons, [&pattern](const Polygon& p) { return p.isPermutation(pattern); }) << '\n';
        }},
        {"RIGHTSHAPES", [](const std::vector<Polygon>& polygons) {
            std::cout << countIf(polygons, [](const Polygon& p) { return p.hasRightAngle(); }) << '\n';
        }}
    };
}

void processCommands(const std::vector<Polygon>& polygons) {
    std::string cmd;
    while (std::cin >> cmd) {
        commandMap.contains(cmd)
            ? commandMap.at(cmd)(polygons)
            : std::cout << "<INVALID COMMAND>\n";
    }
}
