#include "commands.h"
#include "iofmtguard.h"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
    void printArea(double val) {
        koshelev::iofmtguard g(std::cout);
        std::cout << std::fixed << std::setprecision(1) << val << '\n';
    }

    template<class P>
    double accumulateArea(const std::vector<Polygon>& v, P pred) {
        return std::accumulate(
            v.begin(), v.end(), 0.0,
            [&](double s, const Polygon& p){ return s + (pred(p)? p.area(): 0.0); }
        );
    }

    template<class P>
    size_t countIf(const std::vector<Polygon>& v, P pred) {
        return std::count_if(v.begin(), v.end(), pred);
    }

    void areaCmd(const std::vector<Polygon>& v, const std::string& arg) {
        if (arg=="EVEN")      printArea(accumulateArea(v, [](auto& p){ return p.vertexCount()%2==0; }));
        else if (arg=="ODD")  printArea(accumulateArea(v, [](auto& p){ return p.vertexCount()%2==1; }));
        else if (arg=="MEAN"){
            if (v.empty()) throw std::invalid_argument("");
            printArea(accumulateArea(v, [](auto&){return true; })/v.size());
        }
        else {
            size_t num = std::stoul(arg);
            if (num<3) throw std::invalid_argument("");
            printArea(accumulateArea(v,[&](auto& p){return p.vertexCount()==num;}));
        }
    }

    void maxMinCmd(const std::vector<Polygon>& v, const std::string& cmd, const std::string& arg) {
        if (v.empty()) throw std::invalid_argument("");
        auto cmp = [&](auto& a, auto& b){
            return arg=="AREA" ? a.area()<b.area() : a.vertexCount()<b.vertexCount();
        };
        auto it = cmd=="MAX"
                  ? std::max_element(v.begin(), v.end(), cmp)
                  : std::min_element(v.begin(), v.end(), cmp);

        koshelev::iofmtguard g(std::cout);
        if (arg=="AREA")
            std::cout << std::fixed << std::setprecision(1) << it->area() << '\n';
        else
            std::cout << it->vertexCount() << '\n';
    }

    void countCmd(const std::vector<Polygon>& v, const std::string& arg) {
        if (arg=="EVEN")       std::cout << countIf(v,[](auto& p){return p.vertexCount()%2==0;}) << '\n';
        else if (arg=="ODD")   std::cout << countIf(v,[](auto& p){return p.vertexCount()%2==1;}) << '\n';
        else {
            size_t num = std::stoul(arg);
            if (num<3) throw std::invalid_argument("");
            std::cout << countIf(v,[&](auto& p){return p.vertexCount()==num;}) << '\n';
        }
    }
}

void processCommands(const std::vector<Polygon>& polygons) {
    std::string cmd;
    while (std::cin >> cmd) {
        try {
            if (cmd=="AREA") {
                std::string arg; std::cin>>arg;
                areaCmd(polygons,arg);
            }
            else if (cmd=="MAX"||cmd=="MIN") {
                std::string arg; std::cin>>arg;
                maxMinCmd(polygons,cmd,arg);
            }
            else if (cmd=="COUNT") {
                std::string arg; std::cin>>arg;
                countCmd(polygons,arg);
            }
            else if (cmd=="PERMS") {
                Polygon pat;
                if (!(std::cin>>pat)) throw std::invalid_argument("");
                std::cout << std::count_if(
                    polygons.begin(), polygons.end(),
                    [&](auto& p){ return p.isPermutation(pat); }
                ) << '\n';
            }
            else if (cmd=="RIGHTSHAPES") {
                std::cout << std::count_if(
                    polygons.begin(), polygons.end(),
                    [](auto& p){ return p.hasRightAngle(); }
                ) << '\n';
            }
            else throw std::invalid_argument("");
        }
        catch(...) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}
