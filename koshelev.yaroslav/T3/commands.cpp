#include "commands.h"
#include "iofmtguard.h"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <functional>

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

    void areaCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
        if (arg == "EVEN") {
            printArea(accumulateArea(polygons,
                [](const Polygon& p) { return p.vertexCount() % 2 == 0; }));
        }
        else if (arg == "ODD") {
            printArea(accumulateArea(polygons,
                [](const Polygon& p) { return p.vertexCount() % 2 == 1; }));
        }
        else if (arg == "MEAN") {
            if (polygons.empty()) throw std::invalid_argument("");
            printArea(accumulateArea(polygons,
                [](const Polygon&) { return true; }) / polygons.size());
        }
        else {
            size_t num = std::stoul(arg);
            if (num < 3) throw std::invalid_argument("");
            printArea(accumulateArea(polygons,
                [num](const Polygon& p) { return p.vertexCount() == num; }));
        }
    }

    void maxMinCommand(const std::vector<Polygon>& polygons,
                      const std::string& cmd, const std::string& arg) {
        if (polygons.empty()) throw std::invalid_argument("");

        auto compare = [&arg](const Polygon& a, const Polygon& b) {
            return arg == "AREA" ? a.area() < b.area()
                                : a.vertexCount() < b.vertexCount();
        };

        auto it = cmd == "MAX" ? std::max_element(polygons.begin(), polygons.end(), compare)
                               : std::min_element(polygons.begin(), polygons.end(), compare);

        koshelev::iofmtguard guard(std::cout);
        if (arg == "AREA") {
            std::cout << std::fixed << std::setprecision(1) << it->area() << '\n';
        } else {
            std::cout << it->vertexCount() << '\n';
        }
    }

    void countCommand(const std::vector<Polygon>& polygons, const std::string& arg) {
        if (arg == "EVEN") {
            std::cout << countIf(polygons,
                [](const Polygon& p) { return p.vertexCount() % 2 == 0; }) << '\n';
        }
        else if (arg == "ODD") {
            std::cout << countIf(polygons,
                [](const Polygon& p) { return p.vertexCount() % 2 == 1; }) << '\n';
        }
        else {
            size_t num = std::stoul(arg);
            if (num < 3) throw std::invalid_argument("");
            std::cout << countIf(polygons,
                [num](const Polygon& p) { return p.vertexCount() == num; }) << '\n';
        }
    }
}

void processCommands(const std::vector<Polygon>& polygons) {
    std::string cmd;
    while (std::cin >> cmd) {
        try {
            if (cmd == "AREA") {
                std::string arg;
                std::cin >> arg;
                areaCommand(polygons, arg);
            }
            else if (cmd == "MAX" || cmd == "MIN") {
                std::string arg;
                std::cin >> arg;
                maxMinCommand(polygons, cmd, arg);
            }
            else if (cmd == "COUNT") {
                std::string arg;
                std::cin >> arg;
                countCommand(polygons, arg);
            }
            else if (cmd == "PERMS") {
                Polygon pattern;
                if (!(std::cin >> pattern)) throw std::invalid_argument("");
                std::cout << countIf(polygons,
                    [&pattern](const Polygon& p) { return p.isPermutation(pattern); }) << '\n';
            }
            else if (cmd == "RIGHTSHAPES") {
                std::cout << countIf(polygons,
                    [](const Polygon& p) { return p.hasRightAngle(); }) << '\n';
            }
            else {
                throw std::invalid_argument("");
            }
        } catch (...) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

