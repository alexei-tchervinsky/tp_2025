//
// Created by jdh99 on 01.05.2025.
//

#include "iofmtguard.hpp"
#include "commands.hpp"
#include "DataStruct.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>

namespace likhodievskii {
    namespace {
        void checkEmpty(const std::vector<Polygon> &polygons) {
            if (polygons.empty()) {
                throw std::invalid_argument("INVALID COMMAND");
            }
        }
    }

    CommandMap createCommandMap() {
        using namespace std::placeholders;
        return {
            {"AREA", std::bind(areaCommand, _1, _2, _3)},
            {"MAX", std::bind(maxCommand, _1, _2, _3)},
            {"MIN", std::bind(minCommand, _1, _2, _3)},
            {"COUNT", std::bind(countCommand, _1, _2, _3)},
            {"RECTS", std::bind(rectsCommand, _1, _2, _3)},
            {"SAME", std::bind(sameCommand, _1, _2, _3)}
        };
    }

    void executeCommand(const CommandMap &commands,
                        const std::vector<Polygon> &polygons,
                        const std::string &command,
                        std::istream &in,
                        std::ostream &out) {
        auto it = commands.find(command);
        if (it == commands.end()) {
            throw std::invalid_argument("UNKNOWN COMMAND");
        }
        it->second(polygons, in, out);
    }

    void areaCommand(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out) {
        iofmtguard guard(out);
        std::string subcmd;
        in >> subcmd;

        if (subcmd == "ODD") {
            double res = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                                         [](double sum, const Polygon &p) {
                                             return p.points.size() % 2 != 0 ? sum + p.area() : sum;
                                         });
            out << std::fixed << std::setprecision(1) << res << '\n';
        } else if (subcmd == "EVEN") {
            double res = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                                         [](double sum, const Polygon &p) {
                                             return p.points.size() % 2 == 0 ? sum + p.area() : sum;
                                         });
            out << std::fixed << std::setprecision(1) << res << '\n';
        } else if (subcmd == "MEAN") {
            checkEmpty(polygons);
            double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                                           [](double sum, const Polygon &p) { return sum + p.area(); });
            out << std::fixed << std::setprecision(1) << (total / static_cast<double>(polygons.size())) << '\n';
        } else {
            try {
                size_t num = std::stoul(subcmd);
                if (num < 3) {
                    throw std::invalid_argument("INVALID COMMAND");
                }
                double res = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                                             [num](double sum, const Polygon &p) {
                                                 return p.points.size() == num ? sum + p.area() : sum;
                                             });
                out << std::fixed << std::setprecision(1) << res << '\n';
            } catch (...) {
                throw std::invalid_argument("INVALID COMMAND");
            }
        }
    }

    void maxCommand(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out) {
        iofmtguard guard(out);

        std::string subcmd;
        in >> subcmd;
        checkEmpty(polygons);

        if (subcmd == "AREA") {
            auto it = std::max_element(polygons.begin(), polygons.end(),
                                       [](const Polygon &a, const Polygon &b) {
                                           return a.area() < b.area();
                                       });
            out << std::fixed << std::setprecision(1) << it->area() << '\n';
        } else if (subcmd == "VERTEXES") {
            auto it = std::max_element(polygons.begin(), polygons.end(),
                                       [](const Polygon &a, const Polygon &b) {
                                           return a.points.size() < b.points.size();
                                       });
            out << it->points.size() << '\n';
        } else {
            throw std::invalid_argument("INVALID COMMAND");
        }
    }

    void minCommand(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out) {
        iofmtguard guard(out);

        std::string subcmd;
        in >> subcmd;
        checkEmpty(polygons);

        if (subcmd == "AREA") {
            auto it = std::min_element(polygons.begin(), polygons.end(),
                                       [](const Polygon &a, const Polygon &b) {
                                           return a.area() < b.area();
                                       });
            out << std::fixed << std::setprecision(1) << it->area() << '\n';
        } else if (subcmd == "VERTEXES") {
            auto it = std::min_element(polygons.begin(), polygons.end(),
                                       [](const Polygon &a, const Polygon &b) {
                                           return a.points.size() < b.points.size();
                                       });
            out << it->points.size() << '\n';
        } else {
            throw std::invalid_argument("INVALID COMMAND");
        }
    }

    void countCommand(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out) {
        std::string subcmd;
        in >> subcmd;

        if (subcmd == "ODD") {
            out << std::count_if(polygons.begin(), polygons.end(),
                                 [](const Polygon &p) {
                                     return p.points.size() % 2 != 0;
                                 }) << '\n';
        } else if (subcmd == "EVEN") {
            out << std::count_if(polygons.begin(), polygons.end(),
                                 [](const Polygon &p) {
                                     return p.points.size() % 2 == 0;
                                 }) << '\n';
        } else {
            try {
                size_t num = std::stoul(subcmd);
                if (num < 3) {
                    throw std::invalid_argument("INVALID COMMAND");
                }
                out << std::count_if(polygons.begin(), polygons.end(),
                                     [num](const Polygon &p) {
                                         return p.points.size() == num;
                                     }) << '\n';
            } catch (...) {
                throw std::invalid_argument("INVALID COMMAND");
            }
        }
    }

    void rectsCommand(const std::vector<Polygon> &polygons, std::istream &, std::ostream &out) {
        out << std::count_if(polygons.begin(), polygons.end(),
                             [](const Polygon &p) {
                                 return p.isRectangle();
                             }) << '\n';
    }

    void sameCommand(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out) {
        Polygon target;
        if (!(in >> target) || target.points.size() < 3) {
            throw std::invalid_argument("INVALID COMMAND");
        }

        out << std::count_if(polygons.begin(), polygons.end(),
                             [&target](const Polygon &p) {
                                 return isSame(p, target);
                             }) << '\n';
    }
}
