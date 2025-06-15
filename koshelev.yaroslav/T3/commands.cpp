#include <iostream>
#include <string>
#include <limits>
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
    double accumulateArea(const std::vector<Polygon>& v, Pred pred) {
        return std::accumulate(v.begin(), v.end(), 0.0,
            [&pred](double acc, const Polygon& p) {
                return acc + (pred(p) ? p.area() : 0.0);
            });
    }

    template <typename Pred>
    size_t countIf(const std::vector<Polygon>& v, Pred pred) {
        return std::count_if(v.begin(), v.end(), pred);
    }

    void areaCommand(const std::vector<Polygon>& v, const std::string& arg) {
        if (arg == "EVEN") {
            printArea(accumulateArea(v, [](auto& p){ return p.vertexCount()%2==0; }));
        }
        else if (arg == "ODD") {
            printArea(accumulateArea(v, [](auto& p){ return p.vertexCount()%2==1; }));
        }
        else if (arg == "MEAN") {
            if (v.empty()) throw std::invalid_argument("");
            printArea(accumulateArea(v, [](auto&){ return true; }) / v.size());
        }
        else {
            size_t num = std::stoul(arg);
            if (num < 3) throw std::invalid_argument("");
            printArea(accumulateArea(v, [num](auto& p){ return p.vertexCount()==num; }));
        }
    }

    void maxMinCommand(const std::vector<Polygon>& v,
                       const std::string& cmd, const std::string& arg) {
        if (v.empty()) throw std::invalid_argument("");
        auto cmp = [&arg](auto& a, auto& b) {
            return arg=="AREA" ? a.area()<b.area() : a.vertexCount()<b.vertexCount();
        };
        auto it = cmd=="MAX"
              ? std::max_element(v.begin(), v.end(), cmp)
              : std::min_element(v.begin(), v.end(), cmp);

        koshelev::iofmtguard guard(std::cout);
        if (arg=="AREA") {
            std::cout << std::fixed << std::setprecision(1) << it->area() << '\n';
        } else {
            std::cout << it->vertexCount() << '\n';
        }
    }

    void countCommand(const std::vector<Polygon>& v, const std::string& arg) {
        if (arg == "EVEN") {
            std::cout << countIf(v, [](auto& p){ return p.vertexCount()%2==0; }) << '\n';
        }
        else if (arg == "ODD") {
            std::cout << countIf(v, [](auto& p){ return p.vertexCount()%2==1; }) << '\n';
        }
        else {
            size_t num = std::stoul(arg);
            if (num < 3) throw std::invalid_argument("");
            std::cout << countIf(v, [num](auto& p){ return p.vertexCount()==num; }) << '\n';
        }
    }
}

void processCommands(const std::vector<Polygon>& v) {
    std::string cmd;
    while (std::cin >> cmd) {
        try {
            if (cmd == "AREA") {
                std::string arg; std::cin >> arg;
                areaCommand(v, arg);
            }
            else if (cmd == "MAX" || cmd == "MIN") {
                std::string arg; std::cin >> arg;
                maxMinCommand(v, cmd, arg);
            }
            else if (cmd == "COUNT") {
                std::string arg; std::cin >> arg;
                countCommand(v, arg);
            }
            else if (cmd == "PERMS") {
                Polygon pat;
                if (!(std::cin >> pat)) throw std::invalid_argument("");
                std::cout << countIf(v, [&pat](auto& p){ return p.isPermutation(pat); }) << '\n';
            }
            else if (cmd == "RIGHTSHAPES") {
                std::cout << countIf(v, [](auto& p){ return p.hasRightAngle(); }) << '\n';
            }
            else {
                throw std::invalid_argument("");
            }
        }
        catch (...) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}
