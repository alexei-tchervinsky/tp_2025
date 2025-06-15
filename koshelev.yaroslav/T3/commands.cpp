#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iomanip>

#include "commands.h"
#include "polygon.h"
#include "iofmtguard.h"

namespace {
    using VC = std::vector<Polygon>;

    void cmdAREA(const VC &v) {
        std::string a; std::cin >> a;
        if      (a == "EVEN" || a == "ODD") {
            bool wantEven = (a == "EVEN");
            double sum = std::accumulate(v.begin(), v.end(), 0.0,
                [wantEven](double s, auto &p){
                    return s + ((p.vertexCount() % 2 == 0) == wantEven ? p.area() : 0);
                });
            koshelev::iofmtguard g(std::cout);
            std::cout << std::fixed << std::setprecision(1) << sum << "\n";
        }
        else if (a == "MEAN") {
            if (v.empty()) throw std::invalid_argument("");
            double sum = std::accumulate(v.begin(), v.end(), 0.0,
                [](double s, auto &p){ return s + p.area(); });
            koshelev::iofmtguard g(std::cout);
            std::cout << std::fixed << std::setprecision(1) << sum / v.size() << "\n";
        }
        else {
            size_t n = std::stoul(a);
            if (n < 3) throw std::invalid_argument("");
            double sum = std::accumulate(v.begin(), v.end(), 0.0,
                [n](double s, auto &p){ return s + (p.vertexCount() == n ? p.area() : 0); });
            koshelev::iofmtguard g(std::cout);
            std::cout << std::fixed << std::setprecision(1) << sum << "\n";
        }
    }

    void cmdMAX(const VC &v) {
        std::string a; std::cin >> a;
        if (v.empty()) throw std::invalid_argument("");
        if (a == "AREA") {
            auto it = std::max_element(v.begin(), v.end(),
                [](auto &x, auto &y){ return x.area() < y.area(); });
            koshelev::iofmtguard g(std::cout);
            std::cout << std::fixed << std::setprecision(1) << it->area() << "\n";
        }
        else if (a == "VERTEXES") {
            auto it = std::max_element(v.begin(), v.end(),
                [](auto &x, auto &y){ return x.vertexCount() < y.vertexCount(); });
            std::cout << it->vertexCount() << "\n";
        }
        else throw std::invalid_argument("");
    }

    void cmdMIN(const VC &v) {
        std::string a; std::cin >> a;
        if (v.empty()) throw std::invalid_argument("");
        if (a == "AREA") {
            auto it = std::min_element(v.begin(), v.end(),
                [](auto &x, auto &y){ return x.area() < y.area(); });
            koshelev::iofmtguard g(std::cout);
            std::cout << std::fixed << std::setprecision(1) << it->area() << "\n";
        }
        else if (a == "VERTEXES") {
            auto it = std::min_element(v.begin(), v.end(),
                [](auto &x, auto &y){ return x.vertexCount() < y.vertexCount(); });
            std::cout << it->vertexCount() << "\n";
        }
        else throw std::invalid_argument("");
    }

    void cmdCOUNT(const VC &v) {
        std::string a; std::cin >> a;
        if      (a == "EVEN" || a == "ODD") {
            bool wantEven = (a == "EVEN");
            size_t cnt = std::count_if(v.begin(), v.end(),
                [wantEven](auto &p){ return (p.vertexCount() % 2 == 0) == wantEven; });
            std::cout << cnt << "\n";
        }
        else {
            size_t n = std::stoul(a);
            if (n < 3) throw std::invalid_argument("");
            size_t cnt = std::count_if(v.begin(), v.end(),
                [n](auto &p){ return p.vertexCount() == n; });
            std::cout << cnt << "\n";
        }
    }

    void cmdPERMS(const VC &v) {
        Polygon pat;
        if (!(std::cin >> pat)) throw std::invalid_argument("");
        size_t cnt = std::count_if(v.begin(), v.end(),
            [&pat](auto &p){ return p.isPermutation(pat); });
        std::cout << cnt << "\n";
    }

    void cmdRIGHTSHAPES(const VC &v) {
        size_t cnt = std::count_if(v.begin(), v.end(),
            [](auto &p){ return p.hasRightAngle(); });
        std::cout << cnt << "\n";
    }

    using Func = std::function<void(const VC&)>;
    const std::map<std::string, Func> handlers = {
        {"AREA",        cmdAREA},
        {"MAX",         cmdMAX},
        {"MIN",         cmdMIN},
        {"COUNT",       cmdCOUNT},
        {"PERMS",       cmdPERMS},
        {"RIGHTSHAPES", cmdRIGHTSHAPES},
    };
}

void processCommands(const std::vector<Polygon>& polygons) {
    std::string cmd;
    while (std::cin >> cmd) {
        auto it = handlers.find(cmd);
        if (it == handlers.end()) {
            std::cout << "<INVALID COMMAND>\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        try {
            it->second(polygons);
        }
        catch (...) {
            std::cout << "<INVALID COMMAND>\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
