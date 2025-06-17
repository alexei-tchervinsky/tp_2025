#include "iofmtguard.h"
#include "commands.h"
#include "DataStruct.h"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <limits>

namespace shubina {
    namespace {
        void checkEmpty(const std::vector<Polygon>& polygons) {
            if (polygons.empty()) {
                throw std::invalid_argument("<INVALID COMMAND>");
            }
        }

        bool isValidPolygon(const Polygon& poly) {
            return poly.points.size() >= 3;
        }
    }

    CommandMap createCommandMap() {
        using namespace std::placeholders;
        return {
            {"AREA", std::bind(areaCommand, _1, _2, _3)},
            {"MAX", std::bind(maxCommand, _1, _2, _3)},
            {"MIN", std::bind(minCommand, _1, _2, _3)},
            {"COUNT", std::bind(countCommand, _1, _2, _3)},
            {"PERMS", std::bind(permsCommand, _1, _2, _3)},
            {"INFRAME", std::bind(inframeCommand, _1, _2, _3)}
        };
    }

    void executeCommand(const CommandMap& commands,
                       const std::vector<Polygon>& polygons,
                       const std::string& command,
                       std::istream& in,
                       std::ostream& out) {
        auto it = commands.find(command);
        if (it == commands.end()) {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
        it->second(polygons, in, out);
    }

    void areaCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out) {
        iofmtguard guard(out);
        std::string subcmd;
        in >> subcmd;

        std::vector<Polygon> validPolygons;
        std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(validPolygons), isValidPolygon);

        if (subcmd == "ODD") {
            double res = std::accumulate(validPolygons.begin(), validPolygons.end(), 0.0,
                [](double sum, const Polygon& p) {
                    return p.points.size() % 2 != 0 ? sum + p.area() : sum;
                });
            out << std::fixed << std::setprecision(1) << res << '\n';
        }
        else if (subcmd == "EVEN") {
            double res = std::accumulate(validPolygons.begin(), validPolygons.end(), 0.0,
                [](double sum, const Polygon& p) {
                    return p.points.size() % 2 == 0 ? sum + p.area() : sum;
                });
            out << std::fixed << std::setprecision(1) << res << '\n';
        }
        else if (subcmd == "MEAN") {
            checkEmpty(validPolygons);
            double total = std::accumulate(validPolygons.begin(), validPolygons.end(), 0.0,
                [](double sum, const Polygon& p) { return sum + p.area(); });
            out << std::fixed << std::setprecision(1) << (total / validPolygons.size()) << '\n';
        }
        else {
            try {
                size_t num = std::stoul(subcmd);
                if (num < 3) throw std::invalid_argument("<INVALID COMMAND>");

                double res = std::accumulate(validPolygons.begin(), validPolygons.end(), 0.0,
                    [num](double sum, const Polygon& p) {
                        return p.points.size() == num ? sum + p.area() : sum;
                    });
                out << std::fixed << std::setprecision(1) << res << '\n';
            }
            catch (...) {
                throw std::invalid_argument("<INVALID COMMAND>");
            }
        }
    }

    void maxCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out) {
        iofmtguard guard(out);
        std::string subcmd;
        in >> subcmd;

        std::vector<Polygon> validPolygons;
        std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(validPolygons), isValidPolygon);
        checkEmpty(validPolygons);

        if (subcmd == "AREA") {
            auto it = std::max_element(validPolygons.begin(), validPolygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.area() < b.area();
                });
            out << std::fixed << std::setprecision(1) << it->area() << '\n';
        }
        else if (subcmd == "VERTEXES") {
            auto it = std::max_element(validPolygons.begin(), validPolygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
                });
            out << it->points.size() << '\n';
        }
        else {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
    }

    void minCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out) {
        iofmtguard guard(out);
        std::string subcmd;
        in >> subcmd;

        std::vector<Polygon> validPolygons;
        std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(validPolygons), isValidPolygon);
        checkEmpty(validPolygons);

        if (subcmd == "AREA") {
            auto it = std::min_element(validPolygons.begin(), validPolygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.area() < b.area();
                });
            out << std::fixed << std::setprecision(1) << it->area() << '\n';
        }
        else if (subcmd == "VERTEXES") {
            auto it = std::min_element(validPolygons.begin(), validPolygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
                });
            out << it->points.size() << '\n';
        }
        else {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
    }

    void countCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out) {
        std::string subcmd;
        in >> subcmd;

        std::vector<Polygon> validPolygons;
        std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(validPolygons), isValidPolygon);

        if (subcmd == "ODD") {
            out << std::count_if(validPolygons.begin(), validPolygons.end(),
                [](const Polygon& p) {
                    return p.points.size() % 2 != 0;
                }) << '\n';
        }
        else if (subcmd == "EVEN") {
            out << std::count_if(validPolygons.begin(), validPolygons.end(),
                [](const Polygon& p) {
                    return p.points.size() % 2 == 0;
                }) << '\n';
        }
        else {
            try {
                size_t num = std::stoul(subcmd);
                if (num < 3) throw std::invalid_argument("<INVALID COMMAND>");

                out << std::count_if(validPolygons.begin(), validPolygons.end(),
                    [num](const Polygon& p) {
                        return p.points.size() == num;
                    }) << '\n';
            }
            catch (...) {
                throw std::invalid_argument("<INVALID COMMAND>");
            }
        }
    }

    void permsCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out) {
        Polygon target;
        if (!(in >> target) || target.points.size() < 3) {
            throw std::invalid_argument("<INVALID COMMAND>");
        }

        std::vector<Polygon> validPolygons;
        std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(validPolygons), isValidPolygon);

        out << std::count_if(validPolygons.begin(), validPolygons.end(),
            [&target](const Polygon& p) {
                if (p.points.size() != target.points.size()) return false;

                return std::is_permutation(
                    p.points.begin(), p.points.end(),
                    target.points.begin(),
                    [](const Point& a, const Point& b) {
                        return a.x == b.x && a.y == b.y;
                    });
            }) << '\n';
    }

    void inframeCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out) {
        Polygon target;
        if (!(in >> target) || target.points.size() < 3) {
            throw std::invalid_argument("<INVALID COMMAND>");
        }

        std::vector<Polygon> validPolygons;
        std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(validPolygons), isValidPolygon);

        if (validPolygons.empty()) {
            out << "<FALSE>\n";
            return;
        }

        auto minmax_x = std::minmax_element(validPolygons.begin(), validPolygons.end(),
            [](const Polygon& a, const Polygon& b) {
                auto min_a = std::min_element(a.points.begin(), a.points.end(),
                    [](const Point& p1, const Point& p2) { return p1.x < p2.x; });
                auto min_b = std::min_element(b.points.begin(), b.points.end(),
                    [](const Point& p1, const Point& p2) { return p1.x < p2.x; });
                return min_a->x < min_b->x;
            });

        auto minmax_y = std::minmax_element(validPolygons.begin(), validPolygons.end(),
            [](const Polygon& a, const Polygon& b) {
                auto min_a = std::min_element(a.points.begin(), a.points.end(),
                    [](const Point& p1, const Point& p2) { return p1.y < p2.y; });
                auto min_b = std::min_element(b.points.begin(), b.points.end(),
                    [](const Point& p1, const Point& p2) { return p1.y < p2.y; });
                return min_a->y < min_b->y;
            });

        int frame_min_x = std::min_element((*minmax_x.first).points.begin(), (*minmax_x.first).points.end(),
            [](const Point& p1, const Point& p2) { return p1.x < p2.x; })->x;
        int frame_max_x = std::max_element((*minmax_x.second).points.begin(), (*minmax_x.second).points.end(),
            [](const Point& p1, const Point& p2) { return p1.x < p2.x; })->x;
        int frame_min_y = std::min_element((*minmax_y.first).points.begin(), (*minmax_y.first).points.end(),
            [](const Point& p1, const Point& p2) { return p1.y < p2.y; })->y;
        int frame_max_y = std::max_element((*minmax_y.second).points.begin(), (*minmax_y.second).points.end(),
            [](const Point& p1, const Point& p2) { return p1.y < p2.y; })->y;

        bool isInside = std::all_of(target.points.begin(), target.points.end(),
            [=](const Point& p) {
                return p.x >= frame_min_x && p.x <= frame_max_x &&
                       p.y >= frame_min_y && p.y <= frame_max_y;
            });

        out << (isInside ? "<TRUE>" : "<FALSE>") << '\n';
    }
}

