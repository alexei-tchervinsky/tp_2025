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

        void calculateFrameBounds(const std::vector<Polygon>& polygons,
                                int& min_x, int& max_x,
                                int& min_y, int& max_y) {
            min_x = std::numeric_limits<int>::max();
            max_x = std::numeric_limits<int>::min();
            min_y = std::numeric_limits<int>::max();
            max_y = std::numeric_limits<int>::min();

            for (const auto& poly : polygons) {
                if (poly.points.size() < 3) continue;
                for (const auto& point : poly.points) {
                    min_x = std::min(min_x, point.x);
                    max_x = std::max(max_x, point.x);
                    min_y = std::min(min_y, point.y);
                    max_y = std::max(max_y, point.y);
                }
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
                    return p.points.size() % 2 != 0 && p.points.size() >= 3 ? sum + p.area() : sum;
                });
            out << std::fixed << std::setprecision(1) << res << '\n';
        }
        else if (subcmd == "EVEN") {
            double res = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double sum, const Polygon& p) {
                    return p.points.size() % 2 == 0 && p.points.size() >= 3 ? sum + p.area() : sum;
                });
            out << std::fixed << std::setprecision(1) << res << '\n';
        }
        else if (subcmd == "MEAN") {
            checkEmpty(polygons);
            size_t validCount = std::count_if(polygons.begin(), polygons.end(), isValidPolygon);
            if (validCount == 0) throw std::invalid_argument("<INVALID COMMAND>");
            double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double sum, const Polygon& p) {
                    return p.points.size() >= 3 ? sum + p.area() : sum;
                });
            out << std::fixed << std::setprecision(1) << (total / validCount) << '\n';
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

        auto it = std::find_if(polygons.begin(), polygons.end(), isValidPolygon);
        if (it == polygons.end()) {
            throw std::invalid_argument("<INVALID COMMAND>");
        }

        if (subcmd == "AREA") {
            auto maxIt = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    bool aValid = a.points.size() >= 3;
                    bool bValid = b.points.size() >= 3;
                    if (!aValid && !bValid) return false;
                    if (!aValid) return true;
                    if (!bValid) return false;
                    return a.area() < b.area();
                });
            if (maxIt->points.size() < 3) throw std::invalid_argument("<INVALID COMMAND>");
            out << std::fixed << std::setprecision(1) << maxIt->area() << '\n';
        }
        else if (subcmd == "VERTEXES") {
            auto maxIt = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    bool aValid = a.points.size() >= 3;
                    bool bValid = b.points.size() >= 3;
                    if (!aValid && !bValid) return false;
                    if (!aValid) return true;
                    if (!bValid) return false;
                    return a.points.size() < b.points.size();
                });
            if (maxIt->points.size() < 3) throw std::invalid_argument("<INVALID COMMAND>");
            out << maxIt->points.size() << '\n';
        }
        else {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
    }

    void minCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out) {
        iofmtguard guard(out);
        std::string subcmd;
        in >> subcmd;

        auto it = std::find_if(polygons.begin(), polygons.end(), isValidPolygon);
        if (it == polygons.end()) {
            throw std::invalid_argument("<INVALID COMMAND>");
        }

        if (subcmd == "AREA") {
            auto minIt = std::min_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    bool aValid = a.points.size() >= 3;
                    bool bValid = b.points.size() >= 3;
                    if (!aValid && !bValid) return false;
                    if (!aValid) return true;
                    if (!bValid) return false;
                    return a.area() < b.area();
                });
            if (minIt->points.size() < 3) throw std::invalid_argument("<INVALID COMMAND>");
            out << std::fixed << std::setprecision(1) << minIt->area() << '\n';
        }
        else if (subcmd == "VERTEXES") {
            auto minIt = std::min_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    bool aValid = a.points.size() >= 3;
                    bool bValid = b.points.size() >= 3;
                    if (!aValid && !bValid) return false;
                    if (!aValid) return true;
                    if (!bValid) return false;
                    return a.points.size() < b.points.size();
                });
            if (minIt->points.size() < 3) throw std::invalid_argument("<INVALID COMMAND>");
            out << minIt->points.size() << '\n';
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
                return p.points.size() % 2 != 0 && p.points.size() >= 3;
            }) << '\n';
    }
    else if (subcmd == "EVEN") {
        out << std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) {
                return p.points.size() % 2 == 0 && p.points.size() >= 3;
            }) << '\n';
    }
    else {
        try {
            size_t num = std::stoul(subcmd);
            if (num < 3) throw std::invalid_argument("<INVALID COMMAND>");
            out << std::count_if(polygons.begin(), polygons.end(),
                [num](const Polygon& p) {
                    return p.points.size() == num && p.points.size() >= 3;
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

        int frame_min_x, frame_max_x, frame_min_y, frame_max_y;
        calculateFrameBounds(polygons, frame_min_x, frame_max_x, frame_min_y, frame_max_y);

        bool allInside = true;
        for (const auto& point : target.points) {
            if (point.x < frame_min_x || point.x > frame_max_x ||
                point.y < frame_min_y || point.y > frame_max_y) {
                allInside = false;
                break;
            }
        }

        out << (allInside ? "<TRUE>" : "<FALSE>") << '\n';
    }
}

