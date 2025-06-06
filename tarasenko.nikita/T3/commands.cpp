#include "commands.hpp"
#include "computations.hpp"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <stdexcept>

void processAreaCommand(const std::vector<Polygon>& polygons, const std::string& param) {
    if (param == "EVEN" || param == "ODD") {
        bool isEven = (param == "EVEN");
        auto count = [isEven](const Polygon& p) {
            return (p.points.size() % 2 == 0) == isEven;
            };

        double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [count](double acc, const Polygon& p) {
                return acc + (count(p) ? computeArea(p) : 0.0);
            });

        std::cout << std::fixed << std::setprecision(1) << sum << "\n";
    }
    else if (param == "MEAN") {
        if (polygons.empty()) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double acc, const Polygon& p) {
                return acc + computeArea(p);
            });

        std::cout << std::fixed << std::setprecision(1) << (sum / polygons.size()) << "\n";
    }
    else {
        try {
            size_t num = std::stoul(param);
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [num](double acc, const Polygon& p) {
                    return acc + (p.points.size() == num ? computeArea(p) : 0.0);
                });

            std::cout << std::fixed << std::setprecision(1) << sum << "\n";
        }
        catch (...) {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

void processMaxMinCommand(const std::vector<Polygon>& polygons, const std::string& cmd, const std::string& param) {
    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    if (param == "AREA") {
        auto compare = [](const Polygon& a, const Polygon& b) {
            return computeArea(a) < computeArea(b);
            };

        auto it = (cmd == "MAX")
            ? std::max_element(polygons.begin(), polygons.end(), compare)
            : std::min_element(polygons.begin(), polygons.end(), compare);

        std::cout << std::fixed << std::setprecision(1) << computeArea(*it) << "\n";
    }
    else if (param == "VERTEXES") {
        auto compare = [](const Polygon& a, const Polygon& b) {
            return a.points.size() < b.points.size();
            };

        auto it = (cmd == "MAX")
            ? std::max_element(polygons.begin(), polygons.end(), compare)
            : std::min_element(polygons.begin(), polygons.end(), compare);

        std::cout << it->points.size() << "\n";
    }
    else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void processCountCommand(const std::vector<Polygon>& polygons, const std::string& param) {
    if (param == "EVEN" || param == "ODD") {
        bool isEven = (param == "EVEN");
        auto count = std::count_if(polygons.begin(), polygons.end(),
            [isEven](const Polygon& p) {
                return (p.points.size() % 2 == 0) == isEven;
            });

        std::cout << count << "\n";
    }
    else {
        try {
            size_t num = std::stoul(param);
            auto count = std::count_if(polygons.begin(), polygons.end(),
                [num](const Polygon& p) {
                    return p.points.size() == num;
                });

            std::cout << count << "\n";
        }
        catch (...) {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

void processRmechoCommand(std::vector<Polygon>& polygons, const std::string& line) {
    Polygon target;
    if (!parsePolygon(line, target)) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    size_t removed = 0;
    auto it = polygons.begin();
    while (it != polygons.end()) {
        if (*it == target) {
            auto next = it + 1;
            while (next != polygons.end() && *next == target) {
                ++next;
                ++removed;
            }
            if (next != it + 1) {
                it = polygons.erase(it + 1, next);
            }
            else {
                ++it;
            }
        }
        else {
            ++it;
        }
    }

    std::cout << removed << "\n";
}

void processIntersectionsCommand(const std::vector<Polygon>& polygons, const std::string& line) {
    Polygon target;
    if (!parsePolygon(line, target)) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    auto count = std::count_if(polygons.begin(), polygons.end(),
        [&target](const Polygon& p) {
            return doPolygonsIntersect(target, p);
        });

    std::cout << count << "\n";
}