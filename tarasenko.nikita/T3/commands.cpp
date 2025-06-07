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
            bool edgesIntersect = std::any_of(poly1.points.begin(), poly1.points.end(),
                [&poly1, &poly2](const Point& p1) {
                    size_t i = &p1 - &poly1.points[0];
                    const Point& p2 = poly1.points[(i + 1) % poly1.points.size()];

                    return std::any_of(poly2.points.begin(), poly2.points.end(),
                        [&p1, &p2, &poly2](const Point& p3) {
                            size_t j = &p3 - &poly2.points[0];
                            const Point& p4 = poly2.points[(j + 1) % poly2.points.size()];

                            int orient1 = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
                            int orient2 = (p2.x - p1.x) * (p4.y - p1.y) - (p2.y - p1.y) * (p4.x - p1.x);

                            if (orient1 * orient2 < 0) {
                                int orient3 = (p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x);
                                int orient4 = (p4.x - p3.x) * (p2.y - p3.y) - (p4.y - p3.y) * (p2.x - p3.x);
                                return orient3 * orient4 < 0;
                            }
                            return false;
                        });
                });

            if (edgesIntersect) return true;

            auto isPointInside = [](const Point& p, const Polygon& poly) -> bool {
                struct State {
                    bool inside = false;
                    Point prev;
                };

                if (poly.points.empty()) return false;

                State initial;
                initial.prev = poly.points.back();

                State result = std::accumulate(poly.points.begin(), poly.points.end(), initial,
                    [&p](State state, const Point& curr) {
                        if (((curr.y > p.y) != (state.prev.y > p.y))) {
                            int intersectX = (state.prev.x - curr.x) * (p.y - curr.y) / (state.prev.y - curr.y) + curr.x;
                            if (p.x < intersectX) {
                                state.inside = !state.inside;
                            }
                        }
                        state.prev = curr;
                        return state;
                    });

                return result.inside;
                };

            bool allInside1 = std::all_of(poly1.points.begin(), poly1.points.end(),
                [&poly2, &isPointInside](const Point& p) {
                    return isPointInside(p, poly2);
                });

            bool allInside2 = std::all_of(poly2.points.begin(), poly2.points.end(),
                [&poly1, &isPointInside](const Point& p) {
                    return isPointInside(p, poly1);
                });

            return allInside1 || allInside2;
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
