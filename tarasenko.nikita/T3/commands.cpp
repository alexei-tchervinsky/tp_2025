#include "iofmtguard.hpp"
#include "commands.hpp"
#include "DataStruct.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>

namespace tarasenko {
    namespace {
        void checkEmpty(const std::vector<Polygon>& polygons) {
            if (polygons.empty()) {
                throw std::invalid_argument("INVALID COMMAND");
            }
        }

        bool doPolygonsIntersect(const Polygon& poly1, const Polygon& poly2) {
            auto segmentsIntersect = [](const Point& p1, const Point& p2,
                const Point& q1, const Point& q2) -> bool {
                    auto orientation = [](const Point& a, const Point& b, const Point& c) -> int {
                        int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
                        if (val == 0) return 0;
                        return (val > 0) ? 1 : 2;
                        };

                    auto onSegment = [](const Point& p, const Point& q, const Point& r) -> bool {
                        if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
                            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
                            return true;
                        return false;
                        };

                    int o1 = orientation(p1, p2, q1);
                    int o2 = orientation(p1, p2, q2);
                    int o3 = orientation(q1, q2, p1);
                    int o4 = orientation(q1, q2, p2);

                    if (o1 != o2 && o3 != o4)
                        return true;

                    if (o1 == 0 && onSegment(p1, q1, p2)) return true;
                    if (o2 == 0 && onSegment(p1, q2, p2)) return true;
                    if (o3 == 0 && onSegment(q1, p1, q2)) return true;
                    if (o4 == 0 && onSegment(q1, p2, q2)) return true;

                    return false;
                };

            for (size_t i = 0; i < poly1.points.size(); ++i) {
                size_t next_i = (i + 1) % poly1.points.size();
                for (size_t j = 0; j < poly2.points.size(); ++j) {
                    size_t next_j = (j + 1) % poly2.points.size();
                    if (segmentsIntersect(poly1.points[i], poly1.points[next_i],
                        poly2.points[j], poly2.points[next_j])) {
                        return true;
                    }
                }
            }

            auto isPointInsidePolygon = [](const Point& point, const Polygon& poly) -> bool {
                bool inside = false;
                for (size_t i = 0, j = poly.points.size() - 1; i < poly.points.size(); j = i++) {
                    const Point& p1 = poly.points[i];
                    const Point& p2 = poly.points[j];

                    if (((p1.y > point.y) != (p2.y > point.y))) {
                        double intersectX = (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x;
                        if (point.x <= intersectX) {
                            inside = !inside;
                        }
                    }
                }
                return inside;
                        };

                        for (const auto& point : poly1.points) {
                            if (isPointInsidePolygon(point, poly2)) {
                                return true;
                            }
                        }

                for (const auto& point : poly2.points) {
                    if (isPointInsidePolygon(point, poly1)) {
                        return true;
                    }
                }

                return false;
        }
    }

    CommandMap createCommandMap() {
        using namespace std::placeholders;
        return {
            {"AREA", std::bind(areaCommand, _1, _2, _3)},
            {"MAX", std::bind(maxCommand, _1, _2, _3)},
            {"MIN", std::bind(minCommand, _1, _2, _3)},
            {"COUNT", std::bind(countCommand, _1, _2, _3)},
            {"INTERSECTIONS", std::bind(intersectionsCommand, _1, _2, _3)},
            {"RMECHO", std::bind(rmechoCommand, _1, _2, _3)}
        };
    }

    void executeCommand(const CommandMap& commands,
        const std::vector<Polygon>& polygons,
        const std::string& command,
        std::istream& in,
        std::ostream& out) {
        auto it = commands.find(command);
        if (it == commands.end()) {
            throw std::invalid_argument("UNKNOWN COMMAND");
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
                [](double sum, const Polygon& p) { return sum + p.area(); });
            out << std::fixed << std::setprecision(1) << (total / static_cast<double>(polygons.size())) << '\n';
        }
        else {
            try {
                size_t num = std::stoul(subcmd);
                if (num < 3) {
                    throw std::invalid_argument("INVALID COMMAND");
                }
                double res = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                    [num](double sum, const Polygon& p) {
                        return p.points.size() == num ? sum + p.area() : sum;
                    });
                out << std::fixed << std::setprecision(1) << res << '\n';
            }
            catch (...) {
                throw std::invalid_argument("INVALID COMMAND");
            }
        }
    }

    void maxCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out) {
        iofmtguard guard(out);

        std::string subcmd;
        in >> subcmd;
        checkEmpty(polygons);

        if (subcmd == "AREA") {
            auto it = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.area() < b.area();
                });
            out << std::fixed << std::setprecision(1) << it->area() << '\n';
        }
        else if (subcmd == "VERTEXES") {
            auto it = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
                });
            out << it->points.size() << '\n';
        }
        else {
            throw std::invalid_argument("INVALID COMMAND");
        }
    }

    void minCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out) {
        iofmtguard guard(out);

        std::string subcmd;
        in >> subcmd;
        checkEmpty(polygons);

        if (subcmd == "AREA") {
            auto it = std::min_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.area() < b.area();
                });
            out << std::fixed << std::setprecision(1) << it->area() << '\n';
        }
        else if (subcmd == "VERTEXES") {
            auto it = std::min_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
                });
            out << it->points.size() << '\n';
        }
        else {
            throw std::invalid_argument("INVALID COMMAND");
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
                    throw std::invalid_argument("INVALID COMMAND");
                }
                out << std::count_if(polygons.begin(), polygons.end(),
                    [num](const Polygon& p) {
                        return p.points.size() == num;
                    }) << '\n';
            }
            catch (...) {
                throw std::invalid_argument("INVALID COMMAND");
            }
        }
    }

    void intersectionsCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out) {
        Polygon inputPolygon;
        in >> inputPolygon;

        if (inputPolygon.points.size() < 3) {
            throw std::invalid_argument("INVALID COMMAND");
        }

        size_t count = std::count_if(polygons.begin(), polygons.end(),
            [&inputPolygon](const Polygon& poly) {
                return doPolygonsIntersect(inputPolygon, poly);
            });

        out << count << '\n';
    }

    void rmechoCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out) {
        Polygon target;
        in >> target;

        if (target.points.size() < 3) {
            throw std::invalid_argument("INVALID COMMAND");
        }

        std::vector<Polygon> modified = polygons;
        size_t count = 0;
        bool found = false;

        auto it = modified.begin();
        while (it != modified.end()) {
            if (*it == target) {
                if (found) {
                    it = modified.erase(it);
                    count++;
                }
                else {
                    found = true;
                    ++it;
                }
            }
            else {
                found = false;
                ++it;
            }
        }

        out << count << '\n';

        for (const auto& poly : modified) {
            out << poly.points.size() << " ";
            for (const auto& p : poly.points) {
                out << "(" << p.x << ";" << p.y << ") ";
            }
            out << '\n';
        }
    }
}
