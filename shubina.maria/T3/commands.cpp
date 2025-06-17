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

    if (subcmd == "ODD") {
        double res = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, const Polygon& p) {
                return p.points.size() % 2 != 0 ? sum + p.area() : sum;
            });
        out << std::fixed << std::setprecision(1) << res << '\n';
    }
    else if (subcmd == "EVEN") {
        double res = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, const Polygon& p) {
                return p.points.size() % 2 == 0 ? sum + p.area() : sum;
            });
        out << std::fixed << std::setprecision(1) << res << '\n';
    }
    else if (subcmd == "MEAN") {
        checkEmpty(polygons);
        double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, const Polygon& p) {
                return sum + p.area();
            });
        out << std::fixed << std::setprecision(1) << (total / polygons.size()) << '\n';
    }
    else {
        try {
            size_t num = std::stoul(subcmd);
            if (num < 3) throw std::invalid_argument("<INVALID COMMAND>");

            double res = std::accumulate(polygons.begin(), polygons.end(), 0.0,
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
        checkEmpty(polygons);

        auto validPolygons = polygons;
        validPolygons.erase(std::remove_if(validPolygons.begin(), validPolygons.end(),
            [](const Polygon& p) { return p.points.size() < 3; }), validPolygons.end());

        if (validPolygons.empty()) {
            throw std::invalid_argument("<INVALID COMMAND>");
        }

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
        checkEmpty(polygons);

        auto validPolygons = polygons;
        validPolygons.erase(std::remove_if(validPolygons.begin(), validPolygons.end(),
            [](const Polygon& p) { return p.points.size() < 3; }), validPolygons.end());

        if (validPolygons.empty()) {
            throw std::invalid_argument("<INVALID COMMAND>");
        }

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

    if (subcmd == "ODD") {
        out << std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) {
                return p.points.size() % 2 != 0;
            }) << '\n';
    }
    else if (subcmd == "EVEN") {
        out << std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) {
                return p.points.size() % 2 == 0;
            }) << '\n';
    }
    else {
        try {
            size_t num = std::stoul(subcmd);
            if (num < 3) {
                // Для случаев с 1 или 2 точками тоже считаем
                out << std::count_if(polygons.begin(), polygons.end(),
                    [num](const Polygon& p) {
                        return p.points.size() == num;
                    }) << '\n';
            }
            else {
                out << std::count_if(polygons.begin(), polygons.end(),
                    [num](const Polygon& p) {
                        return p.points.size() == num;
                    }) << '\n';
            }
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

        out << std::count_if(polygons.begin(), polygons.end(),
            [&target](const Polygon& p) {
                if (p.points.size() != target.points.size() || p.points.size() < 3) return false;

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

        if (polygons.empty()) {
            out << "<FALSE>\n";
            return;
        }

        // Find bounding rectangle of all valid polygons
        auto firstValid = std::find_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) { return p.points.size() >= 3; });

        if (firstValid == polygons.end()) {
            out << "<FALSE>\n";
            return;
        }

        int minX = firstValid->points[0].x;
        int maxX = firstValid->points[0].x;
        int minY = firstValid->points[0].y;
        int maxY = firstValid->points[0].y;

        for (const auto& poly : polygons) {
            if (poly.points.size() < 3) continue;
            for (const auto& point : poly.points) {
                minX = std::min(minX, point.x);
                maxX = std::max(maxX, point.x);
                minY = std::min(minY, point.y);
                maxY = std::max(maxY, point.y);
            }
        }

        // Check if all points of target are inside the bounding rectangle
        bool inside = std::all_of(target.points.begin(), target.points.end(),
                                [minX, maxX, minY, maxY](const Point& p) {
                                    return p.x >= minX && p.x <= maxX && p.y >= minY && p.y <= maxY;
                                });

        out << (inside ? "<TRUE>" : "<FALSE>") << '\n';
    }
}

